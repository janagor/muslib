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
  int F = S.size();
  int T = S.at(0).size();
  int M = mel_basis.size();

  Signal2 melspec(M, Signal1(F, 0.0));

  for (int f = 0; f < F; ++f) {
    for (int m = 0; m < M; ++m) {
      for (int t = 0; t < T; ++t) {
        melspec.at(m).at(f) += S.at(f).at(t) * mel_basis.at(m).at(t);
      }
    }
  }

  return melspec;
}
Signal2 melspectrogram(const Signal1 &y, double sr) {
  auto n_fft = 2048;
  auto S = _spectogram(y);
  auto mel_basis = mel(sr, n_fft);
  return _melspectrogram(S, mel_basis);
}
namespace {
[[maybe_unused]] Signal2 transpose(const Signal2 &sig) {
  size_t num_frames = sig.size();
  size_t frame_length = sig[0].size();

  Signal2 transposed(frame_length, Signal1(num_frames));

  for (size_t i = 0; i < frame_length; ++i) {
    for (size_t j = 0; j < num_frames; ++j) {
      transposed.at(i).at(j) = sig.at(j).at(i);
    }
  }
  return transposed;
}

} // namespace

namespace {
[[maybe_unused]] Signal2 _dct_coef(size_t N) {
  Signal2 dct_coef(N, Signal1(N));

  for (size_t k = 0; k < N; ++k) {
    for (size_t n = 0; n < N; ++n) {
      if (k == 0) {
        dct_coef.at(k).at(n) = std::sqrt(1.0 / N);
      } else {
        dct_coef.at(k).at(n) =
            std::sqrt(2.0 / N) * std::cos(M_PI * k * (2 * n + 1) / (2.0 * N));
      }
    }
  }

  return dct_coef;
}

} // namespace

Signal2 dct(const Signal2 &input) {
  size_t N = input.size();
  size_t M = input.at(0).size();

  Signal2 output1(N, Signal1(M));
  auto dct_matrix = _dct_coef(M);

  for (size_t i = 0; i < N; ++i) {
    Signal1 output(N);

    for (size_t k = 0; k < M; ++k) {
      double sum = 0.0;
      for (size_t n = 1; n < M; ++n) {
        sum += input.at(i).at(n) * dct_matrix.at(k).at(n);
      }
      output[k] = sum;
    }
    output1.at(i) = output;
  }

  return output1;
}

Signal2 mfcc(const Signal1 &y, double sr) {
  [[maybe_unused]] size_t n_mfcc = 20;
  auto S = melspectrogram(y, sr);

  for (size_t i = 0; i < S.size(); ++i) {
    S.at(i) = convert::power_to_db(S.at(i));
  }

  S = transpose(S);
  S = dct(S);

  for (size_t i = 0; i < S.size(); ++i) {
    S.at(i) = Signal1(S.at(i).begin(), S.at(i).begin() + n_mfcc);
  }

  return transpose(S);
}
/*
Signal1 dct(const Signal1 &input) {
  size_t N = input.size();
  Signal1 output(N);

  auto dct_matrix = _dct_coef(N);

  for (size_t k = 0; k < N; ++k) {
    double sum = 0.0;
    double norm_factor = (std::sqrt(1.0 / N));
    for (size_t n = 1; n < N; ++n) {
      sum += input[n] * dct_matrix.at(k).at(n);
    }
    output[k] = sum * norm_factor;
  }

  return output;
}
*/

} // namespace muslib::transform
