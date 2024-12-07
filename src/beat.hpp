#pragma once
#include "common.hpp"

namespace muslib::beat {

double estimate_tempo(const Signal1 &signal);
std::vector<Time> detect_beats(const Signal1 &signal);

} // namespace muslib::beat
