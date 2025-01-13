#pragma once

#include "common.hpp"

#include "transform.hpp"
#include <fftw3.h>

namespace muslib::beat {

/**
 * @brief estimates tempo of given Signal.
 *
 * @param signal A reference to the signal.
 * @return Estimated tempo value as a double.
 */
double estimate_tempo(const Signal1 &signal);
Signal2 tempogram(const Signal1 &signal, int sr = 22050, int hop_length = 512);

/**
 * @brief detects beats of given Signal.
 *
 * @param signal A reference to the signal.
 * @return Estimated beat value as a Time Vector.
 */
std::vector<Time> detect_beats(const Signal1 &signal);
Signal1 beat_track(const Signal1 &y, double sr);
Signal1 onset_strength(const Signal1 &y, double sr);
Signal1 onset_strength_multi(const Signal1 &y, double sr);

} // namespace muslib::beat
