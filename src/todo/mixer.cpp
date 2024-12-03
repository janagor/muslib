#include <mixer.hpp>

namespace muslib:mixer{
    Signal mix(const Signal& signal1, const Signal& signal2) {
        if (signal1.size() != signal2.size()) {
            throw std::invalid_argument("Signals must have the same length");
        }

        Signal mixed_signal(signal1.size());
        for (size_t i = 0; i < signal1.size(); ++i) 
            mixed_signal[i] = (signal1[i] + signal2[i]) / 2.0;
        
        return mixed_signal;
    }

    Signal normalize(const Signal& signal) {
        double max_value = *std::max_element(signal.begin(), signal.end());
        double min_value = *std::min_element(signal.begin(), signal.end());
        double range = max_value - min_value;

        Signal normalized_signal(signal.size());
        for (size_t i = 0; i < signal.size(); ++i) {
            normalized_signal[i] = (signal[i] - min_value) / range;
        }

        return normalized_signal;
    }

std::vector<std::complex<double>> dft(const Signal& signal) {
        int N = signal.size();
        std::vector<std::complex<double>> X(N);

        for (int k = 0; k < N; ++k) {
            for (int n = 0; n < N; ++n) {
                double angle = -2 * M_PI * k * n / N;
                X[k] += signal[n] * std::complex<double>(std::cos(angle), std::sin(angle));
            }
        }

        return X;
    }

Signal get_spectrum(const Signal& signal) {
        auto X = dft(signal);
        Signal spectrum(X.size());
        for (size_t i = 0; i < X.size(); ++i) {
            spectrum[i] = std::abs(X[i]);
        }
        return spectrum;
    }
}