#include "transform.hpp"

namespace muslib::transform {

Signal1 hann_window(int size) {
  Signal1 window(size);
  for (int i = 0; i < size; ++i) {
    window[i] = 0.5 * (1 - cos(2 * M_PI * i / (size - 1)));
  }
  return window;
}

Signal2Complex stft(const Signal1 &signal, int n_fft, int hop_length) {
  auto window = hann_window(n_fft);
  return stft(signal, n_fft, hop_length, window);
}

Signal2Complex stft(const Signal1 &signal, int n_fft, int hop_length,
                    const Signal1 &window) {
  int num_frames = (signal.size() - n_fft) / hop_length + 1;

  Signal2Complex result(num_frames, Signal1Complex(n_fft / 2 + 1));

  fftw_plan plan = fftw_plan_dft_r2c_1d(n_fft, nullptr, nullptr, FFTW_ESTIMATE);

  for (int frame = 0; frame < num_frames; ++frame) {
    int start_idx = frame * hop_length;
    Signal1 windowed_signal(n_fft, 0.0);

    for (int i = 0; i < n_fft; ++i) {
      if (static_cast<size_t>(start_idx + i) < signal.size()) {
        windowed_signal[i] = signal[start_idx + i] * window[i];
      }
    }

    fftw_complex *fft_result =
        reinterpret_cast<fftw_complex *>(result[frame].data());
    fftw_execute_dft_r2c(plan, windowed_signal.data(), fft_result);
  }

  fftw_destroy_plan(plan);

  return result;
}

Signal2 compute_magnitude_spectrum(const Signal2Complex &stft_result) {
  Signal2 magnitude_spectrum(stft_result.size(),
                             Signal1(stft_result[0].size()));

  for (size_t i = 0; i < stft_result.size(); ++i) {
    for (size_t j = 0; j < stft_result[i].size(); ++j) {
      magnitude_spectrum[i][j] = std::abs(stft_result[i][j]);
    }
  }

  return magnitude_spectrum;
}

} // namespace muslib::transform
