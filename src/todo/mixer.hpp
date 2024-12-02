#pragma once
#include <iostream>
#include <vector>
#include <cstring>

namespace muslib:mixer {

    using real_signal = std::vector<double>;

     signal mix(const Signal& signal1, const Signal& signal2);
     signal normalize(const Signal& signal);
     signal get_spectrum(const Signal& signal);
     signal dft(const Signal& signal)
}
