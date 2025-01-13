#include "fft.hpp"

namespace muslib::fft {

// Signal1Complex rfft(const std::vector<double>& signal, unsigned n_fft) {
//     // Convert std::vector<double> to Signal1Complex with imaginary part = 0
//     Signal1Complex complex_signal(signal.size());
//     for (size_t i = 0; i < signal.size(); ++i) {
//         complex_signal[i] = std::complex<double>(signal[i], 0.0);
//     }
//
//     // Call the existing fft function
//     return fft(complex_signal, n_fft);
// }

Signal1Complex rfft(const Signal1 &signal, unsigned n_fft) {
  fftw_complex *fft_result =
      (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * (n_fft / 2 + 1));
  double *in = (double *)fftw_malloc(sizeof(double) * n_fft);

  for (size_t i = 0; i < signal.size(); ++i) {
    in[i] = signal[i];
  }
  for (size_t i = signal.size(); i < n_fft; ++i) {
    in[i] = 0.0;
  }

  fftw_plan forward_plan =
      fftw_plan_dft_r2c_1d(n_fft, in, fft_result, FFTW_ESTIMATE);

  fftw_execute(forward_plan);

  Signal1Complex result(n_fft / 2 + 1);
  for (size_t i = 0; i < n_fft / 2 + 1; ++i) {
    result[i] = std::complex<double>(fft_result[i][0], fft_result[i][1]);
  }

  fftw_destroy_plan(forward_plan);
  fftw_free(in);
  fftw_free(fft_result);

  return result;
}

Signal1Complex fft(const Signal1Complex &signal, unsigned n_fft) {
  fftw_complex *in = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * n_fft);
  fftw_complex *out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * n_fft);

  for (size_t i = 0; i < signal.size(); ++i) {
    in[i][0] = signal[i].real();
    in[i][1] = signal[i].imag();
  }
  for (size_t i = signal.size(); i < n_fft; ++i) {
    in[i][0] = 0.0;
    in[i][1] = 0.0;
  }

  fftw_plan forward_plan =
      fftw_plan_dft_1d(n_fft, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

  fftw_execute(forward_plan);

  std::vector<std::complex<double>> result(n_fft);
  for (size_t i = 0; i < n_fft; ++i) {
    result[i] = std::complex<double>(out[i][0], out[i][1]);
  }

  fftw_destroy_plan(forward_plan);
  fftw_free(in);
  fftw_free(out);

  return result;
}

Signal1 ifft(const Signal1Complex &spectrum, unsigned n_fft) {
  fftw_complex *in =
      (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * (n_fft / 2 + 1));
  double *out = (double *)fftw_malloc(sizeof(double) * n_fft);

  for (size_t i = 0; i < spectrum.size(); ++i) {
    in[i][0] = spectrum[i].real();
    in[i][1] = spectrum[i].imag();
  }

  fftw_plan backward_plan = fftw_plan_dft_c2r_1d(n_fft, in, out, FFTW_ESTIMATE);

  fftw_execute(backward_plan);

  Signal1 result(n_fft);
  for (size_t i = 0; i < n_fft; ++i) {
    result[i] = out[i] / n_fft;
  }

  fftw_destroy_plan(backward_plan);
  fftw_free(in);
  fftw_free(out);

  return result;
}

Signal1 irfft(const Signal1 &spectrum, unsigned n_fft) {
  fftw_complex *in =
      (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * (n_fft / 2 + 1));
  double *out = (double *)fftw_malloc(sizeof(double) * n_fft);

  for (size_t i = 0; i < spectrum.size(); ++i) {
    in[i][0] = spectrum[i];
    in[i][1] = 0.0;
  }

  fftw_plan backward_plan = fftw_plan_dft_c2r_1d(n_fft, in, out, FFTW_ESTIMATE);

  fftw_execute(backward_plan);

  Signal1 result(n_fft);
  for (unsigned i = 0; i < n_fft; ++i) {
    result[i] = out[i] / n_fft;
  }

  fftw_destroy_plan(backward_plan);
  fftw_free(in);
  fftw_free(out);

  return result;
}

} // namespace muslib::fft
