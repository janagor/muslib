#pragma once
#include "common.hpp"
#include <sndfile.hh>

namespace muslib::io {
/**
 * @brief Convert to mono
 *
 * @param input Signal to be converted
 * @return Converted signal
 */
Signal1 to_mono(const Signal1 &input, int chnum);

/**
 * @brief Load signal to variable from given file
 * 
 * @param file_name Filename of audio file.
 * @return Loaded signal.
 */
Signal1 load(const std::string &file_name);

/**
 * @brief Resamples signal from given sample rate to specific sample rate.
 * 
 * @param original Signal to be modified.
 * @param from_srate original sample rate.
 * @param to_srate new sample rate to be set.
 * @return Resampled signal.
 */
Signal1 resample(const Signal1 &original, int from_srate, int to_srate);
/**
 * @brief Calculates sample rate of signal.
 * 
 * @param path Path to audio file.
 * @return Sample rate of given file.
 */
double get_samplerate(const std::string &path);


/**
 * @brief Calculate duration of audio file.
 * 
 * @param path Path to audio file.
 * @return Duration in miliseconds. 
 */
double get_duration(const std::string &path);

} // namespace muslib::io
