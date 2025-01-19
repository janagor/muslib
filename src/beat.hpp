#pragma once

#include "common.hpp"

#include "transform.hpp"
#include <fftw3.h>

/**
 *  @brief Operations regarding beat.
 *  @author Jan Górski.
 *  @author Konrad Pióro.
 */


namespace muslib::beat {

Signal2 tempogram(const Signal1 &signal, int sr = 22050, int hop_length = 512,
                  int win_length = 384);

/**
 * @brief detects beats of given Signal.
 *
 * @param signal An input signal.
 * @return Estimated beat value as a Time Vector.
 */
std::vector<Time> detect_beats(const Signal1 &signal);
Signal1 beat_track(const Signal1 &y, double sr);

/**
 * @brief Estimate the tempo.
 * 
 * @param y An input signal.
 * @param sr sampling rate of input signal.
 * 
 * @return Estimated tempo (beats per minute)
 */
double tempo(const Signal1 &y, double sr);

/**
 * @brief Compute a spectral flux onset strength envelope.
 * 
 * @param y An input signal.
 * @param sr sampling rate of input signal.
 * 
 * @return vector containing the onset strength envelope. If the input contains multiple channels, then onset envelope is computed for each channel.
 */
Signal1 onset_strength(const Signal1 &y, double sr);

/**
 * @brief Compute a spectral flux onset strength envelope across multiple channels.
 * 
 * @param y An input signal.
 * @param sr sampling rate of input signal.
 * 
 * @return array containing the onset strength envelope for each specified channel
 */
Signal1 onset_strength_multi(const Signal1 &y, double sr);

} // namespace muslib::beat
