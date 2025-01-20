#pragma once

/**
 *  @brief Fourier tranformats.
 *  @author Jan Górski
 *  @author Konrad Pióro
 */

#include "common.hpp"
#include <fftw3.h>

namespace muslib::fft {

Signal1Complex rfft(const Signal1 &y, unsigned n_fft = 0);
Signal1Complex fft(const Signal1Complex &y, unsigned n_fft = 0);
Signal1 irfft(const Signal1 &y, unsigned n_fft = 0);
Signal1 ifft(const Signal1Complex &y, unsigned n_fft = 0);

} // namespace muslib::fft
