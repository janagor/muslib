#pragma once
#include "common.hpp"

namespace muslib::convert {

/**
 * @brief Converts frequency in hertzs to mels.
 *
 * @param freqs The frequency in hertzs to be converted.
 * @return Frequency in mels.
 */
double hz_to_mel(double freqs);
// <<<<<<< HEAD

/**
 * @brief Converts frequencies in hertzs to mels.
 *
 * @param freqs The vector of frequencies in hertzs to be converted.
 * @return Vector of frequencies in mels.
 */
std::vector<double> hz_to_mel(const std::vector<double> &freqs);

/**
 * @brief Converts frequency in Mels to Hertzs.
 *
 * @param freqs The frequency in mels to be converted.
 * @return Frequency in hertzs.
 */
double mel_to_hz(double mel);

/**
 * @brief Converts frequencies in mels to hertzs.
 *
 * @param freqs The vector of frequencies in mels to be converted.
 * @return Vector of frequencies in hertzs.
 */
std::vector<double> mel_to_hz(const std::vector<double> &mels);

/**
 * @brief Converts dB value to a power value.
 *
 * @param signal A reference to the signal.
 * @return Power values.
 */
std::vector<double> db_to_power(const std::vector<double> &signal);

/**
 * @brief Converts power value to a dB value.
 *
 * @param signal A reference to the signal.
 * @return dB values.
 */
std::vector<double> power_to_db(const std::vector<double> &signal);

/**
 * @brief Converts Amplitude to dB.
 *
 * @param signal A reference to the signal.
 * @return dB values.
 */
std::vector<double> amplitude_to_db(const std::vector<double> &signal);

/**
 * @brief Converts samples to frames.
 *
 * @param samples
 * @param hop_length
 * @param n_fft
 * @return
 */
// =======
// Signal1 hz_to_mel(const Signal1 &freqs);
// double mel_to_hz(double mel);
// Signal1 mel_to_hz(const Signal1 &mels);
// Signal1 db_to_power(const Signal1 &signal);
// Signal1 power_to_db(const Signal1 &signal);
// Signal1 amplitude_to_db(const Signal1 &signal);
// >>>>>>> f952791 (added tempgram, ffts and others)
std::vector<int> samples_to_frames(const std::vector<int> &samples,
                                   int hop_length = 512, int n_fft = 0);

/**
 * @brief Converts frames to samples.
 *
 * @param frames
 * @param hop_length
 * @param n_ftt
 * @return
 */
std::vector<int> frames_to_samples(const std::vector<int> &frames,
                                   int hop_length = 512, int n_fft = 0);

} // namespace muslib::convert
// signal A reference to the signal.
