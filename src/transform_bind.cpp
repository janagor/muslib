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

        py::array_t<std::complex<double>> result({n_bins, n_frames});

        auto result_mutable = result.mutable_unchecked<2>();
        for (size_t i = 0; i < n_frames; ++i) {
          for (size_t j = 0; j < n_bins; ++j) {
            result_mutable(j, i) = coefs[i][j];
          }
        }

        return result;
      },
      "Compute the Short-Time Fourier Transform (STFT)", py::arg("signal"),
      py::arg("n_fft") = 2048, py::arg("hop_length") = 512);

  m.def(
      "melspectrogram",
      [](const py::array_t<double> &input, double sr) -> py::array_t<double> {
        py::buffer_info buf = input.request();
        std::vector<double> vec(static_cast<double *>(buf.ptr),
                                static_cast<double *>(buf.ptr) + buf.size);

        muslib::Signal2 coefs = muslib::transform::melspectrogram(vec, sr);

        size_t n_frames = coefs.size();
        size_t n_bins = coefs[0].size();

        py::array_t<double> result({n_bins, n_frames});

        auto result_mutable = result.mutable_unchecked<2>();
        for (size_t i = 0; i < n_frames; ++i) {
          for (size_t j = 0; j < n_bins; ++j) {
            result_mutable(j, i) = coefs[i][j];
          }
        }

        return result;
      },
      "Compute the Short-Time Fourier Transform (STFT)", py::arg("signal"),
      py::arg("sr") = 22050);

  m.def(
      "mel_frequencies",
      [](unsigned n_mels, double fmin, double fmax) -> py::array_t<double> {
        muslib::Signal1 res =
            muslib::transform::mel_frequencies(n_mels, fmin, fmax);
        py::array_t<double> result(res.size(), res.data());

        return result;
      },
      "mel frequencies", py::arg("n_mels") = 128, py::arg("fmin") = 0.0,
      py::arg("fmax") = 11025.0);

  m.def(
      "mel",
      [](double sr, int n_fft, int n_mels) -> py::array_t<double> {
        muslib::Signal2 res = muslib::transform::mel(sr, n_fft, n_mels);

        // Oblicz wymiary tablicy
        size_t rows = res.size();
        size_t cols = res.empty() ? 0 : res[0].size();

        // Skopiuj dane do płaskiego wektora
        std::vector<double> flat_data;
        flat_data.reserve(rows * cols);
        for (const auto &row : res) {
          flat_data.insert(flat_data.end(), row.begin(), row.end());
        }

        // Utwórz NumPy array
        py::array_t<double> result({rows, cols}, flat_data.data());

        return result;
      },
      "mel", py::arg("sr"), py::arg("n_fft"), py::arg("n_mels") = 128);

  m.def(
      "fft_frequencies",
      [](double sr, unsigned n_fft) -> py::array_t<double> {
        muslib::Signal1 res = muslib::transform::fft_frequencies(sr, n_fft);
        py::array_t<double> result(res.size(), res.data());
        return result;
      },
      "fft_frequencies", py::arg("sr") = 22050, py::arg("n_fft") = 2048);
}
