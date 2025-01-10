#pragma once
#include "common.hpp"
#include "convert.hpp"
#include <fftw3.h>

namespace muslib::transform {

Signal1 _diff(const Signal1 &vals);
Signal1 _linspace(double min, double max, unsigned n);
Signal1 _maximum(double lhs, const Signal1 &rhs);
Signal1 _minimum(const Signal1 &lhs, const Signal1 &rhs);
Signal1 hann_window(int size);

Signal2Complex stft(const Signal1 &signal, int n_fft = 2048,
                    int hop_length = 512);
Signal2Complex stft(const Signal1 &signal, int n_fft, int hop_length,
                    const Signal1 &window);
Signal1 istft(const Signal2Complex &stft_matrix, int n_fft = 2048,
              int hop_length = 512);
Signal1 istft(const Signal2Complex &stft_frames, int fft_size, int hop_size,
              const Signal1 &window);

Signal2 compute_magnitude_spectrum(const Signal2Complex &stft_result);
Signal1 mel_frequencies(unsigned n_mels = 128, double fmin = 0.0,
                        double fmax = 11025.0);
Signal2 mel(double sr, int n_fft, int n_mels = 128);
Signal2 melspectrogram(const Signal1 &y, double sr = 22050);
Signal1 fft_frequencies(double sr = 22050, unsigned n_fft = 2048);
Signal2 mfcc(const Signal1 &y, double sr);
Signal2 dct(const Signal2 &input);

} // namespace muslib::transform
