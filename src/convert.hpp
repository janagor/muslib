#pragma once
#include "common.hpp"

/**
 *  @brief Conversion perations.
 *  @author Konrad Pióro.
 */

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
 * @param samples sample index or vector of sample indices
 * @param hop_length number of samples between successive frames
 * @param n_fft length of the FFT window. 
 * @return Frame numbers corresponding to the given times.
 */
std::vector<int> samples_to_frames(const std::vector<int> &samples,
                                   int hop_length = 512, int n_fft = 0);

/**
 * @brief Converts frames to samples.
 *
 * @param frames frame index or vector of frame indices
 * @param hop_length number of samples between successive frames
 * @param n_ftt length of the FFT window.
 * @return time (in samples) of each given frame number.
 */
std::vector<int> frames_to_samples(const std::vector<int> &frames,
                                   int hop_length = 512, int n_fft = 0);
/**
 * @brief Converts time to samples.
 *
 * @param times Time value or array of time values (in seconds)
 * @param sr Sampling rate
 * @return Sample indices corresponding to values in times
 */                                   
std::vector<int> time_to_samples(const Signal1 &times, double sr = 22050);
/**
 * @brief Converts time to frames.
 *
 * @param times time (in seconds) or vector of time values
 * @param sr Sampling rate
 * @param hop_length number of samples between successive frames
 * @return Frame numbers corresponding to the given times.
 */
std::vector<int> time_to_frames(const Signal1 &times, double sr = 22050,
                                unsigned hop_length = 512);
} // namespace muslib::convert
