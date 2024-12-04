#pragma once
#include "common.hpp"
#include <cmath>
#include <fftw3.h>

namespace muslib::transform {

Signal1 hann_window(int size);
Signal2Complex stft(const Signal1 &signal, int n_fft, int hop_length);
Signal2Complex stft(const Signal1 &signal, int n_fft, int hop_length,
                    const Signal1 &window);

Signal2 compute_magnitude_spectrum(const Signal2Complex &stft_result);

} // namespace muslib::transform
