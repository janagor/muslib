#pragma once
#include "common.hpp"

namespace muslib::convert {
std::vector<double> hz_to_mel(const std::vector<double> &freqs);
std::vector<double> db_to_power(const std::vector<double> &signal);
std::vector<double> power_to_db(const std::vector<double> &signal);
std::vector<double> amplitude_to_db(const std::vector<double> &signal);
} // namespace muslib::convert
