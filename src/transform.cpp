#include "transform.hpp"

namespace muslib::transform {

real_signal hann_window(int size) {
    real_signal window(size);
    for (int i = 0; i < size; ++i) {
        window[i] = 0.5 * (1 - cos(2 * M_PI * i / (size - 1)));
    }
    return window;
}

complex_coefs stft(const real_signal& signal, int n_fft, int hop_length) {
    auto window = hann_window(n_fft);
    return stft(signal, n_fft, hop_length, window);
}

complex_coefs stft(const real_signal& signal, int n_fft, int hop_length, const real_signal& window) {
    // real_signal window = hann_window
    int num_frames = (signal.size() - n_fft) / hop_length + 1;

    complex_coefs result(num_frames, complex_signal(n_fft / 2 + 1));

    fftw_plan plan = fftw_plan_dft_r2c_1d(n_fft, nullptr, nullptr, FFTW_ESTIMATE);

    for (int frame = 0; frame < num_frames; ++frame) {
        int start_idx = frame * hop_length;
        real_signal windowed_signal(n_fft, 0.0);

        for (int i = 0; i < n_fft; ++i) {
            if (start_idx + i < signal.size()) {
                windowed_signal[i] = signal[start_idx + i] * window[i];
            }
        }

        fftw_complex* fft_result = reinterpret_cast<fftw_complex*>(result[frame].data());
        fftw_execute_dft_r2c(plan, windowed_signal.data(), fft_result);
    }

    fftw_destroy_plan(plan);

    return result;
}

real_coefs compute_magnitude_spectrum(const complex_coefs& stft_result) {
    real_coefs magnitude_spectrum(stft_result.size(), real_signal(stft_result[0].size()));

    for (size_t i = 0; i < stft_result.size(); ++i) {
        for (size_t j = 0; j < stft_result[i].size(); ++j) {
            magnitude_spectrum[i][j] = std::abs(stft_result[i][j]);
        }
    }

    return magnitude_spectrum;
}

}
