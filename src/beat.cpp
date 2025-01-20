#include "beat.hpp"
#include "mixer.hpp"
#include "transform.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

namespace muslib::beat {

namespace {

void _abs(Signal2 &S) {
  for (auto &s : S)
    std::for_each(s.begin(), s.end(), [](double x) { std::abs(x); });
}

Signal1 _lagged_difference(const Signal1 &input, size_t lag = 1) {
  lag = 1;
  if (lag == 0 || input.size() <= lag) {
    throw std::invalid_argument("Lag must be greater than 0 and less than the "
                                "size of the input vector.");
  }

  Signal1 result(input.size() - lag);

  std::transform(
      input.begin() + lag, input.end(), input.begin(), result.begin(),
      [](double current, double previous) { return current - previous; });

  return result;
}

Signal1 _sync(const Signal2 &S) {
  std::size_t size = S.at(0).size();

  std::vector<double> averages(size, 0.0);

  for (std::size_t i = 0; i < size; ++i) {
    for (const auto &subvector : S) {
      averages.at(i) += subvector.at(i);
    }
    averages.at(i) /= S.size();
  }

  return averages;
}

} // namespace

Signal2 tempogram(const Signal1 &signal, int sr,
                  [[maybe_unused]] int hop_length, int win_length) {
  auto window = transform::hann_window(win_length, true);
  auto onset_envelop = onset_strength(signal, sr);
  auto pad = win_length / 2;
  _pad_linear_ramp(onset_envelop, pad, pad);
  auto odf_frame = mixer::frame(onset_envelop, win_length, 1);
  Signal2 temp(odf_frame);
  for (size_t i = 0; i < temp.size(); ++i) {
    for (size_t j = 0; j < temp.at(0).size(); ++j) {
      temp.at(i).at(j) = odf_frame.at(i).at(j) * window.at(j);
    }
  }
  temp = transform::autocorrelate(temp);
  return _norm_max(temp);
}

double tempo(const Signal1 &y, double sr) {
  auto ac_size = 8.0;
  auto hop_length = 512;
  auto start_bpm = 120.0;
  auto std_bpm = 1.0;
  auto max_tempo = 320.0;

  auto onset_envelope = onset_strength(y, sr);
  auto win_length = convert::time_to_frames({ac_size}, sr).at(0);
  auto tg = tempogram(y, sr, 512, win_length);
  Signal1 tg_avgs(tg.at(0).size(), 0);
  for (size_t i = 0; i < tg.at(0).size(); ++i) {
    for (size_t j = 0; j < tg.size(); ++j)
      tg_avgs.at(i) += tg.at(j).at(i);
    tg_avgs.at(i) /= tg.size();
  }
  auto bpms = transform::tempo_frequencies(win_length, sr, hop_length);

  auto logprior(bpms);
  std::for_each(logprior.begin(), logprior.end(), [&](double &bpm) {
    bpm = -0.5 * ((std::log2(bpm) - log2(start_bpm)) / std_bpm) *
          ((std::log2(bpm) - log2(start_bpm)) / std_bpm);
  });

  auto it = std::find_if(bpms.begin(), bpms.end(),
                         [max_tempo](int bpm) { return bpm < max_tempo; });
  size_t x = std::distance(bpms.begin(), it);
  if (x == bpms.size())
    x = 0;
  std::for_each(logprior.begin(), logprior.begin() + x, [&](double &bpm) {
    bpm = -std::numeric_limits<double>::infinity();
  });

  auto max_indx =
      tg_avgs.size() < logprior.size() ? tg_avgs.size() : logprior.size();

  Signal1 periods(max_indx, 0);
  std::transform(tg_avgs.begin(), tg_avgs.begin() + max_indx, logprior.begin(),
                 periods.begin(),
                 [&](auto tg, auto logp) { return log1p(1e6 * tg) + logp; });
  auto max_it = std::max_element(periods.begin(), periods.end());
  auto best_period = std::distance(periods.begin(), max_it);
  return bpms.at(best_period);
}

namespace {

Signal1 _beat_local_score(const Signal1 &onset_envelope,
                          unsigned frames_per_beat) {
  auto N = onset_envelope.size();
  Signal1 localscore(N, 0);
  size_t K = 2 * frames_per_beat + 1;
  Signal1 window(K, 0);
  std::iota(window.begin(), window.end(),
            -static_cast<double>(frames_per_beat));
  std::for_each(window.begin(), window.end(), [frames_per_beat](double &x) {
    x = std::exp(-0.5 *
                 std::pow(x * 32.0 / static_cast<double>(frames_per_beat), 2));
  });

  for (size_t i = 0; i < onset_envelope.size(); ++i) {

    int start_k = std::max(0, static_cast<int>(i) + static_cast<int>(K) / 2 -
                                  static_cast<int>(N) + 1);
    int end_k = std::min(static_cast<int>(i) + K / 2, K);

    for (int k = start_k; k < end_k; ++k)
      localscore.at(i) += window.at(k) * onset_envelope.at(i + K / 2 - k);
  }
  return localscore;
}

void _beat_track_dp(const Signal1 &localscore, double frames_per_beat,
                    double tightness, std::vector<int> &backlink,
                    Signal1 &cumscore) {
  auto score_thresh =
      0.01 * (*std::max_element(localscore.begin(), localscore.end()));
  auto first_beat = true;
  backlink.at(0) = -1;
  cumscore.at(0) = localscore.at(0);

  for (int i = 0; i < static_cast<int>(localscore.size()); ++i) {
    auto best_score = -std::numeric_limits<double>::infinity();
    auto beat_location = -1;

    for (int loc = i - static_cast<int>(frames_per_beat) / 2;
         loc > i - 2 * static_cast<int>(frames_per_beat) - 1; --loc) {
      if (loc < 0)
        break;
      auto score = cumscore.at(loc) -
                   tightness * pow(log(i - loc) - log(frames_per_beat), 2);
      if (score > best_score) {
        best_score = score;
        beat_location = loc;
      }
      if (beat_location >= 0)
        cumscore.at(i) = localscore.at(i) + best_score;
      else
        cumscore.at(i) = localscore.at(i);
      if (first_beat && localscore.at(i) < score_thresh)
        backlink.at(i) = -1;
      else {
        backlink.at(i) = beat_location;
        first_beat = false;
      }
    }
  }
  return;
}

std::vector<bool> _local_max(const std::vector<double> &data) {
  std::vector<bool> mask(data.size(), true);
  for (size_t i = 1; i < data.size() - 1; ++i) {
    if (data[i] <= data[i - 1] || data[i] <= data[i + 1]) {
      mask[i] = false;
    }
  }
  mask.front() = false;
  mask.back() = false;
  return mask;
}

double _median_masked(const std::vector<double> &data,
                      const std::vector<bool> &mask) {
  std::vector<double> filtered;
  for (size_t i = 0; i < data.size(); ++i) {
    if (!mask[i]) {
      filtered.push_back(data[i]);
    }
  }

  if (filtered.empty()) {
    return 0.0; // Jeśli wszystkie wartości są zamaskowane
  }

  std::sort(filtered.begin(), filtered.end());
  size_t mid = filtered.size() / 2;
  return filtered.size() % 2 == 0 ? (filtered[mid - 1] + filtered[mid]) / 2.0
                                  : filtered[mid];
}

void _last_beat_selector(const std::vector<double> &data,
                         const std::vector<bool> &mask, double threshold,
                         int &lastBeatPos) {
  lastBeatPos = -1;
  for (int i = static_cast<int>(data.size()) - 1; i >= 0; --i) {
    if (!mask[i] && data[i] > threshold) {
      lastBeatPos = i;
      break;
    }
  }
}
int _last_beat(const std::vector<double> &cumscore) {
  std::vector<bool> mask = _local_max(cumscore);
  double median = _median_masked(cumscore, mask);
  double threshold = 0.5 * median;
  int tail = -1;
  _last_beat_selector(cumscore, mask, threshold, tail);
  return tail;
}

void _dp_backtrack(const std::vector<int> &backlinks, int tail,
                   std::vector<bool> &beats) {
  while (tail >= 0) {
    beats.at(static_cast<unsigned>(tail)) = 1;
    tail = backlinks.at(tail);
  }
}
std::vector<bool> _trim_beats(const Signal1 &localscore,
                              const std::vector<bool> &beats, int trim) {

  auto beats_trimmed(beats);

  std::vector<double> w = {0.0, 0.5 * (1 - cos(2 * M_PI / 4 * 1)), 1.0,
                           0.5 * (1 - cos(2 * M_PI / 4 * 3)), 0.0};

  // Perform same-mode convolution for the smooth beat envelope
  std::vector<double> smooth_boe(localscore.size(), 0.0);
  int half_window = w.size() / 2;
  for (size_t i = 0; i < localscore.size(); ++i) {
    double sum = 0.0;
    for (size_t j = 0; j < w.size(); ++j) {
      int idx = i + j - half_window;
      if (idx >= 0 && idx < static_cast<int>(localscore.size())) {
        sum += localscore[idx] * w[j];
      }
    }
    smooth_boe[i] = sum;
  }

  // Compute threshold: 1/2 RMS of the smoothed beat envelope
  double threshold = 0.0;
  if (trim) {
    double rms = 0.0;
    for (double val : smooth_boe) {
      rms += val * val;
    }
    rms = std::sqrt(rms / smooth_boe.size());
    threshold = 0.5 * rms;
  }

  // Suppress bad beats at the beginning
  size_t n = 0;
  while (n < localscore.size() && localscore[n] <= threshold) {
    beats_trimmed[n] = false;
    ++n;
  }

  // Suppress bad beats at the end
  n = localscore.size() - 1;
  while (n < localscore.size() && localscore[n] <= threshold) {
    beats_trimmed[n] = false;
    if (n == 0)
      break; // Prevent underflow
    --n;
  }
  return beats_trimmed;
}

std::vector<bool> _beat_tracker(const Signal1 &onset_envelope, double bpm,
                                double frame_rate, double tightness,
                                [[maybe_unused]] bool trim) {
  auto frames_per_beat = frame_rate * 60.0 / bpm;
  auto localscore = _beat_local_score(onset_envelope, frames_per_beat);

  Signal1 cumscore(localscore.size(), 0);
  std::vector<int> backlink(localscore.size(), 0);
  _beat_track_dp(localscore, frames_per_beat, tightness, backlink, cumscore);
  auto tail = _last_beat(cumscore);
  std::vector<bool> beats(onset_envelope.size(), 0);
  _dp_backtrack(backlink, tail, beats);
  return _trim_beats(localscore, beats, trim);
}

std::vector<double> get_true_indices(const std::vector<bool> &vec) {
  std::vector<double> indices;

  for (size_t i = 0; i < vec.size(); ++i) {
    if (vec[i]) {
      indices.push_back(i);
    }
  }

  return indices;
}

} // namespace

Signal1 beat_track(const Signal1 &y, double sr) {
  auto hop_length = 512;
  auto tightness = 100.;
  auto trim = true;

  auto onset_envelope = onset_strength(y, sr);
  auto bpm = tempo(y, sr);
  auto beats =
      _beat_tracker(onset_envelope, bpm, sr / hop_length, tightness, trim);
  auto res = get_true_indices(beats);

  return res;
}

Signal1 onset_strength(const Signal1 &y, double sr) {
  return onset_strength_multi(y, sr);
}

Signal1 onset_strength_multi(const Signal1 &y, double sr) {
  // NOTE: for now does not support multi - so it is just onset_strength
  auto S = transform::melspectrogram(y, sr);
  _abs(S);
  for (auto &s : S)
    s = convert::power_to_db(s);

  auto onset_env = S;
  for (auto &s : onset_env) {
    s = _lagged_difference(s);
    s = transform::_maximum(0., s);
  }
  auto pad_with = 1 + 2048 / (2 * 512);

  auto _onset_env = _sync(onset_env);
  _pad_constant(_onset_env, pad_with, 0);
  return _onset_env;
}

} // namespace muslib::beat
