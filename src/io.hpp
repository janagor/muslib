#pragma once
#include "common.hpp"
#include <sndfile.hh>

namespace muslib::io {

Signal1 to_mono(const Signal1 &input, int chnum);
Signal1 load(const std::string &file_name);
Signal1 resample(const Signal1 &original, int from_srate, int to_srate);
double get_samplerate(const std::string &path);
double get_duration(const std::string &path);

} // namespace muslib::io
