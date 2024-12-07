#include "beat.hpp"

namespace muslib::beat {
double estimate_tempo(const Signal1 &signal) {
  const double SAMPLING_RATE = 44100; // TODO: make it an argument

  int N = signal.size();
  std::vector<double> autocorrelation(N);
  for (int tau = 0; tau < N; ++tau)
    for (int t = 0; t < N - tau; ++t)
      autocorrelation[tau] += signal[t] * signal[t + tau];

  int max_index =
      std::max_element(autocorrelation.begin() + 10, autocorrelation.end()) -
      autocorrelation.begin();

  double tempo = 60.0 * SAMPLING_RATE / max_index;

  return tempo;
}

} // namespace muslib::beat
