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

double estimate_tempo(const Signal1 &signal) {
  const double SAMPLING_RATE = 44100; // TODO: make it an argument

  int N = signal.size();
  std::vector<double> autocorrelation(N);
  for (int tau = 0; tau < N; ++tau)
    for (int t = 0; t < N - tau; ++t)
      autocorrelation.at(tau) += signal.at(t) * signal.at(t + tau);

  int max_index =
      std::max_element(autocorrelation.begin() + 10, autocorrelation.end()) -
      autocorrelation.begin();

  double tempo = 60.0 * SAMPLING_RATE / max_index;

  return tempo;
}

Signal2 tempogram(const Signal1 &signal, int sr,
                  [[maybe_unused]] int hop_length) {
  int win_length = 384;
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

Signal1 tempo([[maybe_unused]] const Signal1 &y, [[maybe_unused]] double sr) {
  auto onset_envelope = onset_strength(y, sr);

  return {};
}

Signal1 beat_track([[maybe_unused]] const Signal1 &y,
                   [[maybe_unused]] double sr) {
  auto onset_envelope = onset_strength(y, sr);

  return {};
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
