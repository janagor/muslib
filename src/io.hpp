#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <cstring>
#include <stdexcept>
#include <sndfile.hh>

namespace muslib::io {

std::vector<double> load(const std::string& file_name);

} // namespace muslib::io

