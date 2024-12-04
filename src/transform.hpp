#pragma once
#include <cmath>
#include <complex>
#include <fftw3.h>
#include <vector>

namespace muslib::transform {

using complex_coefs = std::vector<std::vector<std::complex<double>>>;
using real_coefs = std::vector<std::vector<double>>;
using real_signal = std::vector<double>;
using complex_signal = std::vector<std::complex<double>>;

real_signal hann_window(int size);

complex_coefs stft(const real_signal &signal, int n_fft, int hop_length);
complex_coefs stft(const real_signal &signal, int n_fft, int hop_length,
                   const real_signal &window);

real_coefs compute_magnitude_spectrum(const complex_coefs &stft_result);

} // namespace muslib::transform
