#pragma once
#include <iostream>
#include <vector>

namespace muslib:beat {
    using real_signal = std::vector<double>;
    using time = int;
    using tempo = std::dobule;

    Tempo estimate_tempo(const Signal& signal);
    std::vector<Time> detect_beats(const Signal& signal);

}