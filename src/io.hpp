#pragma once
#include "common.hpp"
#include <sndfile.hh>

namespace muslib::io {

Signal1 load(const std::string &file_name);
Signal1 resample(const Signal1 &original, int from_srate, int to_srate);

} // namespace muslib::io
