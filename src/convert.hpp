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
 * @brief Convert dB value to a power value.
 * 
 * @param signal A reference to the signal.
 * @return Power values.
 */
std::vector<double> db_to_power(const std::vector<double> &signal);

/**
 * @brief Convert power value to a dB value.
 * 
 * @param signal A reference to the signal.
 * @return dB values.
 */
std::vector<double> power_to_db(const std::vector<double> &signal);

/**
 * @brief 
 * 
 * @param 
 * @return 
 */
std::vector<double> amplitude_to_db(const std::vector<double> &signal);

/**
 * @brief 
 * 
 * @param 
 * @return 
 */
std::vector<int> samples_to_frames(const std::vector<int> &samples,
                                   int hop_length = 512, int n_fft = 0);
 
 /** 
  * @brief Converts samples to frames. 
  * 
  * @param frames
  * @param hop_length 
  * @param n_ftt
  * @return
  */
std::vector<int> frames_to_samples(const std::vector<int> &frames,
                                   int hop_length = 512, int n_fft = 0);

} // namespace muslib::convert
//signal A reference to the signal.