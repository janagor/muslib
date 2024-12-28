#include "transform.hpp"
#include <pybind11/complex.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(transform, m) {
  m.doc() = "Signal processing";

  m.def(
      "stft",
      [](const muslib::Signal1 &signal, int n_fft, int hop_length) {
        muslib::Signal2Complex coefs =
            muslib::transform::stft(signal, n_fft, hop_length);

        size_t n_frames = coefs.size();
        size_t n_bins = coefs[0].size();

        py::array_t<std::complex<double>> result({n_frames, n_bins});

        auto result_mutable = result.mutable_unchecked<2>();
        for (size_t i = 0; i < n_frames; ++i) {
          for (size_t j = 0; j < n_bins; ++j) {
            result_mutable(i, j) = coefs[i][j];
          }
        }

        return result;
      },
      "Compute the Short-Time Fourier Transform (STFT)", py::arg("signal"),
      py::arg("n_fft"), py::arg("hop_length"));
}
