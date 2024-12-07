#include "transform.hpp"
#include <iostream>

using namespace muslib::transform;

int main() {
  int signal_size = 44100;
  std::vector<double> signal(signal_size, 0.0);

  for (int i = 0; i < signal_size; ++i) {
    signal[i] = sin(2 * std::numbers::pi * 440 * i / 44100);
  }

  int n_fft = 2048;
  int hop_length = 512;
  auto window = hann_window(n_fft);

  auto stft_result = stft(signal, n_fft, hop_length, window);

  auto magnitude_spectrum = compute_magnitude_spectrum(stft_result);

  for (size_t i = 0; i < magnitude_spectrum.size(); ++i) {
    for (size_t j = 0; j < magnitude_spectrum[i].size(); ++j) {
      std::cout << magnitude_spectrum[i][j] << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
