#pragma once
#include <iostream>
#include <vector>
#include <sndfile.hh>

// namespace muslib::io {

namespace musio {
std::vector<double> load(const std::string& file_name);
}
// } // namespace muslib::io

