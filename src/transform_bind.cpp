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
      "istft",
      [](const py::array_t<std::complex<double>> &coefs, int n_fft,
         int hop_length) {
        py::buffer_info buf_info = coefs.request();

        if (buf_info.ndim != 2)
          throw std::runtime_error("Number of dimensions must be two");

        auto r = coefs.unchecked<2>();

        int num_frames = r.shape(0);
        // std::cout << "num_frames: " << num_frames << std::endl;
        int num_bins = r.shape(1);
        // std::cout << "num_bins: " << num_bins << std::endl;

        std::vector<std::vector<std::complex<double>>> coefs_vec(
            num_bins, muslib::Signal1Complex(num_frames));

        for (py::ssize_t i = 0; i < r.shape(0); ++i) {
          for (py::ssize_t j = 0; j < r.shape(1); ++j) {
            coefs_vec.at(j).at(i) = r(i, j);
          }
        }

        muslib::Signal1 signal =
            muslib::transform::istft(coefs_vec, n_fft, hop_length);

        py::array_t<double> result(signal.size());
        std::copy(signal.begin(), signal.end(), result.mutable_data());

        return result;
      },
      "Compute the Inverse Short-Time Fourier Transform (STFT)",
      py::arg("signal"), py::arg("n_fft") = 2048, py::arg("hop_length") = 512);

  m.def(
      "melspectrogram",
      [](const py::array_t<double> &input, double sr) -> py::array_t<double> {
        py::buffer_info buf = input.request();
        std::vector<double> vec(static_cast<double *>(buf.ptr),
                                static_cast<double *>(buf.ptr) + buf.size);

        muslib::Signal2 coefs = muslib::transform::melspectrogram(vec, sr);

        size_t n_frames = coefs.size();
        size_t n_bins = coefs[0].size();

        py::array_t<double> result({n_frames, n_bins});

        auto result_mutable = result.mutable_unchecked<2>();
        for (size_t i = 0; i < n_frames; ++i) {
          for (size_t j = 0; j < n_bins; ++j) {
            result_mutable(i, j) = coefs[i][j];
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

        size_t rows = res.size();
        size_t cols = res.empty() ? 0 : res[0].size();

        std::vector<double> flat_data;
        flat_data.reserve(rows * cols);
        for (const auto &row : res) {
          flat_data.insert(flat_data.end(), row.begin(), row.end());
        }

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

  m.def(
      "mfcc",
      [](const py::array_t<double> &input, double sr) -> py::array_t<double> {
        py::buffer_info buf = input.request();
        std::vector<double> vec(static_cast<double *>(buf.ptr),
                                static_cast<double *>(buf.ptr) + buf.size);

        muslib::Signal2 coefs = muslib::transform::mfcc(vec, sr);

        size_t n_frames = coefs.size();
        size_t n_bins = coefs[0].size();

        py::array_t<double> result({n_frames, n_bins});

        auto result_mutable = result.mutable_unchecked<2>();
        for (size_t i = 0; i < n_frames; ++i) {
          for (size_t j = 0; j < n_bins; ++j) {
            result_mutable(i, j) = coefs[i][j];
          }
        }

        return result;
      },
      "mfcc", py::arg("signal"), py::arg("sr") = 22050);

  m.def(
      "autocorrelate",
      [](py::array_t<double> sig) {
        py::buffer_info buf = sig.request();
        muslib::Signal1 vec(static_cast<double *>(buf.ptr),
                            static_cast<double *>(buf.ptr) + buf.size);
        auto output_vec = muslib::transform::autocorrelate(vec);

        py::array_t<double> result(output_vec.size());
        auto result_buf = result.request();
        double *result_ptr = static_cast<double *>(result_buf.ptr);

        std::copy(output_vec.begin(), output_vec.end(), result_ptr);

        return result;
      },
      "autocorrelate", py::arg("signal"));
}
