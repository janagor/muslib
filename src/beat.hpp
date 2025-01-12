#pragma once
#include "common.hpp"

namespace muslib::beat {

/**
 * @brief estimates tempo of given Signal.
 * 
 * @param signal A reference to the signal.
 * @return Estimated tempo value as a double.
 */
double estimate_tempo(const Signal1 &signal);

/**
 * @brief detects beats of given Signal.
 * 
 * @param signal A reference to the signal.
 * @return Beats value as a Time Vector.
 */
std::vector<Time> detect_beats(const Signal1 &signal);

} // namespace muslib::beat
