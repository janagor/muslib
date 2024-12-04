#pragma once
#include <cstring>
#include <sndfile.hh>
#include <vector>

namespace muslib::io {

std::vector<double> load(const std::string &file_name);
std::vector<double> resample(const std::vector<double> &original,
                             int from_srate, int to_srate, int num_channels);

} // namespace muslib::io
