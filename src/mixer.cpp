#include "mixer.hpp"
#include <cmath>
#include <numeric>

namespace muslib::mixer {

// TODO: to be implemented
// Signal sin(double duration, unsigned sample_rate, double freq);
// Signal cos(double duration, unsigned sample_rate, double freq);
// Signal zero_crossing_rate(const Signal& sig);
// Signal zero_crossings(const Signal& sig);

Signal2d frame(const Signal &sig, unsigned frame_length, unsigned hop_length) {
  Signal2d frames;

  for (size_t start = 0; start + frame_length <= sig.size();
       start += hop_length) {
    frames.emplace_back(sig.begin() + start,
                        sig.begin() + start + frame_length);
  }

  return frames;
}

Signal normalized(const Signal &sig) {
  double eps = 0.00001;
  if (sig.size() == 0)
    return sig;

  Signal normalized;
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

double avg(const Signal &sig) {
  if (sig.size() == 0)
    return 0.0;
  return std::accumulate(sig.begin(), sig.end(), 0.0) / sig.size();
}

double variance(const Signal &sig) {
  if (sig.size() == 0)
    return 0.0;
  double average = avg(sig);
  double sum = 0;
  for (const auto &val : sig) {
    sum += (val - average) * (val - average);
  }
  return sum / sig.size();
}

double std_dev(const Signal &sig) { return std::sqrt(variance(sig)); }

} // namespace muslib::mixer
