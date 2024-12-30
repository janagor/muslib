#include "transform.hpp"

#include <fftw3.h>

namespace muslib::transform {

Signal1 _diff(const Signal1 &vals) {
  if (vals.size()) {
    Signal1 diffs(vals.size() - 1);
    std::transform(vals.begin(), vals.end() - 1, vals.begin() + 1,
                   diffs.begin(),
                   [&](double lhs, double rhs) { return rhs - lhs; });
    return diffs;
  }
  return {};
}

Signal2 _spectogram(const Signal1 &y, int n_fft = 2048, int hop_length = 512) {
  auto res = stft(y, n_fft, hop_length);
  auto res2 = compute_magnitude_spectrum(res);
  for (auto &i : res2)
    for (auto &j : i)
      j = j * j; // TODO: make a power a parameter
  return res2;
}

Signal1 _linspace(double min, double max, unsigned n) {
  Signal1 res(n);
  if (n == 1) {
    res.at(0) = min;
    return res;
  }
  auto diff = (max - min) / (n - 1);
  std::iota(res.begin(), res.end(), 0);
  std::for_each(res.begin(), res.end(),
                [&](double &value) { value = min + value * diff; });
  return res;
}

Signal1 _maximum(double lhs, const Signal1 &rhs) {
  auto res(rhs);
  std::for_each(res.begin(), res.end(),
                [&](double &x) { x = (x > lhs ? x : lhs); });
  return res;
}

Signal1 _minimum(const Signal1 &lhs, const Signal1 &rhs) {
  if (lhs.size() != rhs.size())
    throw std::runtime_error("different sizes of arguments.");
  Signal1 res(lhs.size());
  std::transform(lhs.begin(), lhs.end(), rhs.begin(), res.begin(),
                 [&](double l, double r) { return (l < r ? l : r); });
  return res;
}

Signal1 hann_window(int size) {
  Signal1 window(size);
  for (int i = 0; i < size; ++i) {
    window.at(i) = 0.5 * (1 - cos(2 * std::numbers::pi * i / (size - 1)));
  }
  return window;
}

Signal2Complex stft(const Signal1 &signal, int n_fft, int hop_length) {
  auto window = hann_window(n_fft);
  return stft(signal, n_fft, hop_length, window);
}

Signal2Complex stft(const Signal1 &signal, int n_fft, int hop_length,
                    const Signal1 &window) {

  int num_frames = static_cast<int>((signal.size() - n_fft) / hop_length + 1);
  Signal2Complex result(num_frames, Signal1Complex(n_fft / 2 + 1));

  // Allocate memory for a single FFTW complex buffer
  fftw_complex *fft_buffer = new fftw_complex[n_fft];

  // Plan the FFT using fftw_plan_dft_1d
  fftw_plan plan = fftw_plan_dft_1d(n_fft, fft_buffer, fft_buffer, FFTW_FORWARD,
                                    FFTW_ESTIMATE);

  for (int frame = 0; frame < num_frames; ++frame) {
    int start_idx = frame * hop_length;

    // Window the signal and copy into the fft_buffer (real part only)
    for (int i = 0; i < n_fft; ++i) {
      if (static_cast<size_t>(start_idx + i) < signal.size()) {
        fft_buffer[i][0] = signal[start_idx + i] * window[i]; // Real part
        fft_buffer[i][1] = 0.0; // Imaginary part is zero for the real signal
      } else {
        fft_buffer[i][0] = 0.0; // Zero padding
        fft_buffer[i][1] = 0.0;
      }
    }

    // Perform the FFT (in-place)
    fftw_execute(plan);

    // Store the FFT result (only the positive frequencies)
    for (int i = 0; i < n_fft / 2 + 1; ++i) {
      result[frame][i] =
          std::complex<double>(fft_buffer[i][0], fft_buffer[i][1]);
    }
  }

  // Clean up FFTW plan and allocated memory
  fftw_destroy_plan(plan);
  delete[] fft_buffer;

  return result;
}

Signal1 istft(const Signal2Complex &stft_matrix, int n_fft, int hop_length) {
  Signal1 window = hann_window(n_fft);
  return istft(stft_matrix, n_fft, hop_length, window);
}

Signal1 istft(const Signal2Complex &stft_frames, int fft_size, int hop_size,
              const Signal1 &window) {

  int n_frames = stft_frames.size();
  int n_samples = (n_frames - 1) * hop_size + fft_size;

  std::vector<double> signal(n_samples, 0.0);

  fftw_plan p = fftw_plan_dft_1d(fft_size, nullptr, nullptr, FFTW_BACKWARD,
                                 FFTW_ESTIMATE);

  for (int t = 0; t < n_frames; ++t) {
    fftw_complex *frame_in = new fftw_complex[fft_size];

    for (int i = 0; i < fft_size; ++i) {
      frame_in[i][0] = real(stft_frames[t][i]);
      frame_in[i][1] = imag(stft_frames[t][i]);
    }

    fftw_execute_dft(p, frame_in, frame_in);

    for (int i = 0; i < fft_size; ++i) {
      int index = t * hop_size + i;
      if (index < n_samples) {
        signal[index] += frame_in[i][0] * window[i];
      }
    }

    delete[] frame_in;
  }

  fftw_destroy_plan(p);

  return signal;
}

Signal2 compute_magnitude_spectrum(const Signal2Complex &stft_result) {
  Signal2 magnitude_spectrum(stft_result.size(),
                             Signal1(stft_result.at(0).size(), 0));

  for (size_t i = 0; i < stft_result.size(); ++i) {
    for (size_t j = 0; j < stft_result.at(i).size(); ++j) {
      magnitude_spectrum.at(i).at(j) = std::abs(stft_result.at(i).at(j));
    }
  }

  return magnitude_spectrum;
}

Signal1 rfftfreq(int n, double d = 1.0) {
  auto val = 1.0 / (n * d);
  int N = n / 2 + 1;
  Signal1 result(N);
  std::iota(result.begin(), result.end(), 0);
  std::for_each(result.begin(), result.end(),
                [&](double &value) { value *= val; });
  return result;
}

Signal1 fft_frequencies(double sr, unsigned n_fft) {
  return rfftfreq(n_fft, 1.0 / sr);
}

Signal1 mel_frequencies(unsigned n_mels, double fmin, double fmax) {
  auto min_mel = convert::hz_to_mel(fmin);
  auto max_mel = convert::hz_to_mel(fmax);
  auto mels = _linspace(min_mel, max_mel, n_mels);
  auto res = convert::mel_to_hz(mels);
  return convert::mel_to_hz(mels);
}

Signal2 mel(double sr, int n_fft, int n_mels) {
  auto fmax = sr / 2;
  Signal2 weights(n_mels, Signal1((1 + n_fft / 2), 0));
  Signal1 fftfreqs = fft_frequencies(sr, n_fft);
  Signal1 mel_f = mel_frequencies(n_mels + 2, 0., fmax);
  Signal1 fdiff = _diff(mel_f);
  Signal2 ramps(mel_f.size(), Signal1(fftfreqs.size(), 0));

  for (size_t i = 0; i < ramps.size(); ++i)
    for (size_t j = 0; j < ramps.at(i).size(); ++j)
      ramps.at(i).at(j) = mel_f.at(i) - fftfreqs.at(j);

  for (int i = 0; i < n_mels; ++i) {
    Signal1 lower(ramps.at(i));
    std::for_each(lower.begin(), lower.end(),
                  [&](double &x) { x = -x / fdiff.at(i); });

    Signal1 upper(ramps.at(i + 2));
    std::for_each(upper.begin(), upper.end(),
                  [&](double &x) { x /= fdiff.at(i + 1); });

    weights.at(i) = _maximum(0.0, _minimum(lower, upper));
  }
  Signal1 enorm(n_mels);
  for (int i = 0; i < n_mels; ++i) {
    enorm.at(i) = 2.0 / (mel_f.at(i + 2) - mel_f.at(i));
  }
  for (size_t i = 0; i < weights.size(); ++i) {
    for (size_t j = 0; j < weights.at(i).size(); ++j) {
      weights.at(i).at(j) *= enorm.at(i);
    }
  }
  return weights;
}

Signal2 _melspectrogram(const Signal2 &S, const Signal2 &mel_basis) {
  // Zmienna przechowująca wynik (num_time, num_mels)
  int num_time = S.size();               // Liczba próbek czasowych
  int num_freq = mel_basis.at(0).size(); // Liczba częstotliwości
  int num_mels = mel_basis.size();       // Liczba filtrów Mel

  // Inicjalizacja wynikowej macierzy melspec (num_time, num_mels)
  Signal2 melspec(num_time, Signal1(num_mels, 0.0));

  // Iteracja po próbkach czasowych (t) i filtrach Mel (m)
  for (int t = 0; t < num_time; ++t) {
    for (int m = 0; m < num_mels; ++m) {
      double sum = 0.0;
      // Suma iloczynów odpowiadających częstotliwości z S[t] i filtrów Mel
      // mel_basis[m]
      for (int f = 0; f < num_freq; ++f) {
        sum += S.at(t).at(f) * mel_basis.at(m).at(f);
      }
      melspec.at(t).at(m) = sum;
    }
  }

  return melspec;
}
Signal2 melspectrogram(const Signal1 &y, double sr) {
  auto S = _spectogram(y);
  auto mel_basis = mel(sr, 512);
  return _melspectrogram(S, mel_basis);
}

} // namespace muslib::transform
