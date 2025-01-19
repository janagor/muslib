#pragma once

/**
 *  @brief Operations that can be applied to signal.
 *  @author Jan Górski
 */

#include "common.hpp"
#include "convert.hpp"
#include "fft.hpp"
#include <fftw3.h>

namespace muslib::transform {


Signal1 _diff(const Signal1 &vals);

Signal1 _maximum(double lhs, const Signal1 &rhs);

Signal1 _minimum(const Signal1 &lhs, const Signal1 &rhs);

/**
 * @brief Return a Hann window.
 *
 * @param size Number of points in the output window.
 * @return The window, with the maximum value normalized to 1
 */
Signal1 hann_window(int size, bool fftbins = true);

/**
 * @brief Short-time Fourier transform (STFT).
 *
 * @param signal Input signal.
 * @param n_fft Length of the windowed signal after padding with zeros.
 * @param hop_length number of audio samples between adjacent STFT columns.
 * @return Complex-valued matrix of short-term Fourier transform coefficients.
 */
Signal2Complex stft(const Signal1 &signal, int n_fft = 2048,
                    int hop_length = 512);

/**
 * @brief Short-time Fourier transform (STFT).
 *
 * @param signal Input signal.
 * @param hop_length number of audio samples between adjacent STFT columns.
 * @param window //TODO
 * @return Complex-valued matrix of short-term Fourier transform coefficients.
 */
Signal2Complex stft(const Signal1 &signal, int n_fft, int hop_length,
                    const Signal1 &window);

/**
 * @brief Inverse short-time Fourier transform (ISTFT).
 *
 * @param stft_matrix STFT matrix from stft
 * @param n_fft The number of samples per frame in the input spectrogram.
 * @param hop_length Number of frames between STFT columns.
 * @return Time domain signal reconstructed from stft_matrix
 */
Signal1 istft(const Signal2Complex &stft_matrix, int n_fft = 2048,
              int hop_length = 512);

/**
 * @brief Inverse short-time Fourier transform (ISTFT).
 *
 * @param stft_frames STFT frames from stft
 * @param fft_size Size of fft
 * @param hop_size Number of frames between STFT columns
 * @param windows A window specification
 * @return Time domain signal reconstructed from stft_matrix
 */
Signal1 istft(const Signal2Complex &stft_frames, int fft_size, int hop_size,
              const Signal1 &window);

/**
 * @brief
 * //todo
 * @param
 * @return
 */
Signal2 compute_magnitude_spectrum(const Signal2Complex &stft_result);

/**
 * @brief Compute an array of acoustic frequencies tuned to the mel scale.
 *
 * @param n_mels Number of mel bins.
 * @param fmin Minimum frequency in Hertzs.
 * @param fmax Maximum frequency in Hertzs.
 * @return Vector of n_mels frequencies in Hz which are uniformly spaced on the
 * Mel axis.
 */
Signal1 mel_frequencies(unsigned n_mels = 128, double fmin = 0.0,
                        double fmax = 11025.0);
/**
 * @brief Create a Mel filter-bank.
 *
 * @param sr Sampling rate of the incoming signal.
 * @param n_fft number of FFT components.
 * @param n_mels number of Mel bands to generate
 * @return Mel transform matrix
 */
Signal2 mel(double sr, int n_fft, int n_mels = 128);
Signal1 tempo_frequencies(unsigned n_bins, double sr = 22050,
                          unsigned hop_length = 512);

/**
 * @brief Compute a mel-scaled spectrogram.
 *
 * @param y Audio time-series.
 * @param sr  Sampling rate of `y`
 * @return Mel spectrogram
 */
Signal2 melspectrogram(const Signal1 &y, double sr = 22050);

/**
 * @brief Alternative implementation of `np.fft.fftfreq`
 *
 * @param sr Audio sampling rate
 * @param n_fft FFT window size
 * @return Frequencies (0, sr/n_fft, 2*sr/n_fft, ..., sr/2)
 */
Signal1 fft_frequencies(double sr = 22050, unsigned n_fft = 2048);

/**
 * @brief Mel-frequency cepstral coefficients
 *
 * @param y Audio time series.
 * @param sr  sampling rate of `y`
 * @return MFCC sequence
 */
Signal2 mfcc(const Signal1 &y, double sr);

/**
 * @brief Discrete Cosine Transform.
 *
 * @param input Input signal.
 * @return The transformed input Signal.
 */ 
Signal2 dct(const Signal2 &input);

/**
 * @brief Bounded-lag auto-correlation
 *
 * @param y Audio time series.
 * @return truncated autocorrelation y*y
 */
Signal1 autocorrelate(const Signal1 &signal);

/**
 * @brief Bounded-lag auto-correlation
 *
 * @param y Audio time series.
 * @return truncated autocorrelation y*y
 */
Signal2 autocorrelate(const Signal2 &signal);

} // namespace muslib::transform
