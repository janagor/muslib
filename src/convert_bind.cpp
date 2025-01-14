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
      "mel_to_hz",
      [](py::array_t<double> mels) {
        py::buffer_info buf = mels.request();
        std::vector<double> vec(static_cast<double *>(buf.ptr),
                                static_cast<double *>(buf.ptr) + buf.size);
        std::vector<double> output_vec = muslib::convert::mel_to_hz(vec);

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

  m.def(
      "frames_to_samples",
      [](py::array_t<int> frames, int hop_length, int n_fft) {
        py::buffer_info buf = frames.request();
        std::vector<int> vec(static_cast<int *>(buf.ptr),
                             static_cast<int *>(buf.ptr) + buf.size);
        std::vector<int> output_vec =
            muslib::convert::frames_to_samples(vec, hop_length, n_fft);

        py::array_t<int> result(buf);
        auto result_buf = result.request();
        int *result_ptr = static_cast<int *>(result_buf.ptr);

        std::copy(output_vec.begin(), output_vec.end(), result_ptr);

        return result;
      },
      "frames to samples", py::arg("frames"), py::arg("hop_length") = 512,
      py::arg("n_fft") = 0);

  m.def(
      "time_to_samples",
      [](py::array_t<double> times, double sr) {
        py::buffer_info buf = times.request();
        muslib::Signal1 vec(static_cast<double *>(buf.ptr),
                            static_cast<double *>(buf.ptr) + buf.size);
        std::vector<int> output_vec = muslib::convert::time_to_samples(vec, sr);

        py::array_t<int> result(buf.shape);
        auto result_buf = result.request();

        int *result_ptr = static_cast<int *>(result_buf.ptr);

        std::copy(output_vec.begin(), output_vec.end(), result_ptr);

        return result;
      },
      "time to samples", py::arg("times"), py::arg("sr") = 22050);

  m.def(
      "time_to_frames",
      [](py::array_t<double> times, double sr, unsigned hop_length) {
        py::buffer_info buf = times.request();
        std::vector<double> vec(static_cast<double *>(buf.ptr),
                                static_cast<double *>(buf.ptr) + buf.size);
        std::vector<int> output_vec =
            muslib::convert::time_to_frames(vec, sr, hop_length);

        py::array_t<int> result(buf.shape);
        auto result_buf = result.request();
        int *result_ptr = static_cast<int *>(result_buf.ptr);

        std::copy(output_vec.begin(), output_vec.end(), result_ptr);

        return result;
      },
      "time to samples", py::arg("times"), py::arg("sr") = 22050,
      py::arg("hop_length") = 512);
}
