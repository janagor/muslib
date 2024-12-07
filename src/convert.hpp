#pragma once
#include "common.hpp"

namespace muslib::convert {
int convert_to_format(const std::string &input_file,
                      const std::string &output_file,
                      const std::string &format);
}
