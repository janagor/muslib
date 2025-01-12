#pragma once
#include "common.hpp"

namespace muslib::convert {

double hz_to_mel(double freqs);
std::vector<double> hz_to_mel(const std::vector<double> &freqs);
double mel_to_hz(double mel);
std::vector<double> mel_to_hz(const std::vector<double> &mels);
std::vector<double> db_to_power(const std::vector<double> &signal);

/**
 * @brief 
 * 
 * @param signal A reference to the signal.
 * @return 
 */
std::vector<double> power_to_db(const std::vector<double> &signal);
std::vector<double> amplitude_to_db(const std::vector<double> &signal);
std::vector<int> samples_to_frames(const std::vector<int> &samples,
                                   int hop_length = 512, int n_fft = 0);
std::vector<int> frames_to_samples(const std::vector<int> &frames,
                                   int hop_length = 512, int n_fft = 0);

} // namespace muslib::convert
