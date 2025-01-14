#pragma once

#include "common.hpp"

#include "transform.hpp"
#include <fftw3.h>

namespace muslib::beat {

Signal2 tempogram(const Signal1 &signal, int sr = 22050, int hop_length = 512,
                  int win_length = 384);

/**
 * @brief detects beats of given Signal.
 *
 * @param signal A reference to the signal.
 * @return Estimated beat value as a Time Vector.
 */
std::vector<Time> detect_beats(const Signal1 &signal);
Signal1 beat_track(const Signal1 &y, double sr);
double tempo(const Signal1 &y, double sr);
Signal1 onset_strength(const Signal1 &y, double sr);
Signal1 onset_strength_multi(const Signal1 &y, double sr);

} // namespace muslib::beat
