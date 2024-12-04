#pragma once
#include <cstring>
#include <sndfile.hh>
#include <vector>

namespace muslib::io {

std::vector<double> load(const std::string &file_name);

} // namespace muslib::io
