#include "beat.hpp"

namespace muslib::beat{
    Tempo estimate_tempo(const Signal& signal){
        int N = signal.size();
        std::vector<double> autocorrelation(N);
        for(int tau=0; tau < N; ++tau)
            for(int t=0; t < N-tau; ++t)
                autocorrelation[tau] += signal[t] * signal[t + tau];

        int max_index = std::max_element(autocorrelation.begin() + 10, autocorrelation.end()) - autocorrelation.begin();

        double sampling_rate = 44100;
        double tempo = 60.0 * sampling_rate / max_index;

        return tempo;
    }

}