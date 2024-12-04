#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

namespace muslib::beat {
    using Signal = std::vector<double>;
    using Time = int;
    using Tempo = double;

    Tempo estimate_tempo(const Signal& signal);
    std::vector<Time> detect_beats(const Signal& signal);

}