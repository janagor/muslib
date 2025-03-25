#include "mixer.hpp"

#include <numeric>
namespace {

void _cos(muslib::Signal1 &sig) {
  for (auto &val : sig)
    val = std::cos(val);
}

void _chirp_phase(muslib::Signal1 &t, double f0, double t1, double f1) {
  double beta = (f1 - f0) / t1;
  for (auto &phase : t) {
    phase = 2 * std::numbers::pi * (f0 * phase + 0.5 * beta * phase * phase);
  }
}

} // namespace

namespace muslib::mixer {

// TODO: to be implemented
// Signal1 sin(double duration, unsigned sample_rate, double freq);
// Signal1 cos(double duration, unsigned sample_rate, double freq);
std::vector<bool> zero_crossings(const Signal1 &sig, bool pad) {
  auto zero_pos = true;
  std::vector<bool> res(sig.size());
  if (!sig.size())
    return res;
  res.at(0) = pad;
  if (sig.size() == 1) {
    return res;
  }
  if (zero_pos) {
    std::transform(sig.begin(), sig.end() - 1, sig.begin() + 1, res.begin() + 1,
                   [&](double l, double r) {
                     if (std::abs(l) < 1e-10)
                       l = 0;
                     if (std::abs(r) < 1e-10)
                       r = 0;
                     return std::signbit(r) != std::signbit(l);
                   });
    return res;
  }
  std::transform(sig.begin(), sig.end() - 1, sig.begin() + 1, res.begin() + 1,
                 [&](double l, double r) {
                   if (std::abs(l) < 1e-10)
                     l = 0;
                   if (std::abs(r) < 1e-10)
                     r = 0;
                   return r * l <= 0;
                 });
  return res;
}

namespace {} // namespace

Signal1 zero_crossing_rate(const Signal1 &sig, unsigned frame_length,
                           unsigned hop_length) {
  Signal1 sigc(sig);

  size_t pad_size = frame_length / 2;
  _pad_edge(sigc, pad_size, pad_size);

  Signal2 frames = frame(sigc, frame_length, hop_length);
  Signal1 res(frames.size());
  for (size_t i = 0; i < res.size(); ++i) {
    auto zcs = zero_crossings(frames.at(i), false);
    auto count =
        static_cast<double>(std::accumulate(zcs.begin(), zcs.end(), 0));
    auto zcr = count / static_cast<double>(zcs.size());
    res.at(i) = zcr;
  }
  return res;
}

Signal1 tone(double frequency, double sr, unsigned length, double duration,
             double phi) {
  if (!length) {
    if (duration <= 0) {
      throw std::runtime_error(
          "either 'length' or 'duration' must be provided");
    }
    length = int(duration * sr);
  }

  Signal1 res(length);

  std::iota(res.begin(), res.end(), 0);
  std::for_each(res.begin(), res.end(), [&](double &val) {
    val = std::cos(2 * std::numbers::pi * frequency * val / sr + phi);
  });
  return res;
}

Signal1 chirp(double fmin, double fmax, double sr, int length, double duration,
              double phi) {
  // NOTE: phi in radians
  double period = 1.0 / sr;
  if (!length) {
    if (duration < 0)
      throw std::runtime_error(
          "either 'length' or 'duration' must be provided");
  } else
    duration = period * length;

  Signal1 res(duration * sr);
  std::iota(res.begin(), res.end(), 0);
  for (auto &val : res)
    val = val / sr;

  _chirp_phase(res, fmin, duration, fmax);
  for (auto &val : res) {
    val += phi;
  }
  _cos(res);
  return res;
}

double avg(const Signal1 &sig) {
  if (sig.size() == 0)
    return 0.0;
  return std::accumulate(sig.begin(), sig.end(), 0.0) / sig.size();
}

Signal2 transpose(const Signal2 &sig) {
  size_t num_frames = sig.size();
  size_t frame_length = sig[0].size();

  Signal2 transposed(frame_length, Signal1(num_frames));

  for (size_t i = 0; i < frame_length; ++i) {
    for (size_t j = 0; j < num_frames; ++j) {
      transposed.at(i).at(j) = sig.at(j).at(i);
    }
  }
  return transposed;
}
// TODO: frame1 differs from frame with the axis of result. It would be nice to
// make implementation irrelevant to this fact
Signal2 frame(const Signal1 &sig, unsigned frame_length, unsigned hop_length) {
  Signal2 frames;

  for (size_t start = 0; start + frame_length <= sig.size();
       start += hop_length) {
    frames.emplace_back(sig.begin() + start,
                        sig.begin() + start + frame_length);
  }

  return frames;
}
/*
Signal2 frame(const Signal1 &sig, unsigned frame_length, unsigned hop_length) {
  size_t num_frames = (sig.size() - 1) / hop_length + 1;

  Signal2 frames(frame_length, Signal1(num_frames));

  for (size_t i = 0; i < frame_length; ++i) {
    for (size_t j = 0; j < num_frames; ++j) {
      size_t index = j * hop_length + i;
      if (index < sig.size()) {
        frames.at(i).at(j) = sig.at(index);
      }
    }
  }
  return transpose(frames);
}
*/

Signal1 normalized(const Signal1 &sig) {
  double eps = 0.00001;
  if (sig.size() == 0)
    return sig;

  Signal1 normalized;
  normalized.reserve(sig.size());
  double norm = 0.0;

  for (const auto &val : sig) {
    norm += val * val;
  }
  if (std::abs(norm) < eps)
    return sig;

  for (const auto &val : sig) {
    normalized.emplace_back(val / norm);
  }
  return normalized;
}

double variance(const Signal1 &sig) {
  if (sig.size() == 0)
    return 0.0;
  double average = avg(sig);
  double sum = 0;
  for (const auto &val : sig) {
    sum += (val - average) * (val - average);
  }
  return sum / sig.size();
}

double std_dev(const Signal1 &sig) { return std::sqrt(variance(sig)); }

} // namespace muslib::mixer
