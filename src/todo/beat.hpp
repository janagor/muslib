#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

namespace muslib:beat {
    using Signal = std::vector<double>;
    using time = int;
    using tempo = std::dobule;

    Tempo estimate_tempo(const Signal& signal);
    std::vector<Time> detect_beats(const Signal& signal);

}