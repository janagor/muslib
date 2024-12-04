#include <beat.hpp>

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

    std::vector<Time> detect_beats(const Signal& signal){
        std::vector<Time> onsets = detect_onsets(signal); // Założenie, że funkcja detect_onsets już istnieje
        Tempo tempo = estimate_tempo(signal);
        double beat_period = 60.0 / tempo;
        double tolerance = 0.1 * beat_period; // Tolerancja na odchylenia od idealnego rytmu
        std::vector<Time> beats;
        double current_beat = onsets[0];
        for (size_t i = 1; i < onsets.size(); ++i) {
            if (std::abs(onsets[i] - current_beat) > beat_period - tolerance) {
                beats.push_back(current_beat);
                current_beat += beat_period;
            }
        }

        return beats; 
    }
}