#include "convert.hpp"
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(convert, m) {
  m.doc() = "Signal convertions";

  m.def(
      "hz_to_mel",
      [](py::array_t<double> freqs) {
        py::buffer_info buf = freqs.request();
        std::vector<double> vec(static_cast<double *>(buf.ptr),
                                static_cast<double *>(buf.ptr) + buf.size);
        std::vector<double> output_vec = muslib::convert::hz_to_mel(vec);

        py::array_t<double> result(buf);
        auto result_buf = result.request();
        double *result_ptr = static_cast<double *>(result_buf.ptr);

        std::copy(output_vec.begin(), output_vec.end(), result_ptr);

        return result;
      },
      "Compute the Short-Time Fourier Transform (STFT)");

  m.def(
      "db_to_power",
      [](py::array_t<double> freqs) {
        py::buffer_info buf = freqs.request();
        std::vector<double> vec(static_cast<double *>(buf.ptr),
                                static_cast<double *>(buf.ptr) + buf.size);
        std::vector<double> output_vec = muslib::convert::db_to_power(vec);

        py::array_t<double> result(buf);
        auto result_buf = result.request();
        double *result_ptr = static_cast<double *>(result_buf.ptr);

        std::copy(output_vec.begin(), output_vec.end(), result_ptr);

        return result;
      },
      "Compute the Short-Time Fourier Transform (STFT)");
  m.def(
      "power_to_db",
      [](py::array_t<double> freqs) {
        py::buffer_info buf = freqs.request();
        std::vector<double> vec(static_cast<double *>(buf.ptr),
                                static_cast<double *>(buf.ptr) + buf.size);
        std::vector<double> output_vec = muslib::convert::power_to_db(vec);

        py::array_t<double> result(buf);
        auto result_buf = result.request();
        double *result_ptr = static_cast<double *>(result_buf.ptr);

        std::copy(output_vec.begin(), output_vec.end(), result_ptr);

        return result;
      },
      "Compute the Short-Time Fourier Transform (STFT)");
  m.def(
      "amplitude_to_db",
      [](py::array_t<double> freqs) {
        py::buffer_info buf = freqs.request();
        std::vector<double> vec(static_cast<double *>(buf.ptr),
                                static_cast<double *>(buf.ptr) + buf.size);
        std::vector<double> output_vec = muslib::convert::amplitude_to_db(vec);

        py::array_t<double> result(buf);
        auto result_buf = result.request();
        double *result_ptr = static_cast<double *>(result_buf.ptr);

        std::copy(output_vec.begin(), output_vec.end(), result_ptr);

        return result;
      },
      "Compute the Short-Time Fourier Transform (STFT)");

  m.def(
      "samples_to_frames",
      [](py::array_t<int> samples, int hop_length, int n_fft) {
        py::buffer_info buf = samples.request();
        std::vector<int> vec(static_cast<int *>(buf.ptr),
                             static_cast<int *>(buf.ptr) + buf.size);
        std::vector<int> output_vec =
            muslib::convert::samples_to_frames(vec, hop_length, n_fft);

        py::array_t<int> result(buf);
        auto result_buf = result.request();
        int *result_ptr = static_cast<int *>(result_buf.ptr);

        std::copy(output_vec.begin(), output_vec.end(), result_ptr);

        return result;
      },
      "samples to frames", py::arg("samples"), py::arg("hop_length") = 512,
      py::arg("n_fft") = 0);
}
