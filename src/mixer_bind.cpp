#include "mixer.hpp"
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(mixer, m) {
  m.doc() = "Signal convertions";

  m.def(
      "chirp",
      [](double fmin, double fmax, double sr, int length, double duration,
         double phi) {
        auto res = muslib::mixer::chirp(fmin, fmax, sr, length, duration, phi);
        py::array_t<double> result(res.size(), res.data());

        return result;
      },
      "generate chirp signal", py::arg("fmin"), py::arg("fmax"),
      py::arg("sr") = 22050, py::arg("length") = 0, py::arg("duration") = -1,
      py::arg("phi") = default_phi);

  m.def(
      "tone",
      [](double frequency, double sr, unsigned length, double duration,
         double phi) {
        auto res = muslib::mixer::tone(frequency, sr, length, duration, phi);
        py::array_t<double> result(res.size(), res.data());
        return result;
      },
      "generate tone signal", py::arg("frequency"), py::arg("sr") = 22050,
      py::arg("length") = 0, py::arg("duration") = -1,
      py::arg("phi") = default_phi);

  m.def(
      "zero_crossings",
      [](py::array_t<double> sig, bool pad) {
        py::buffer_info buf = sig.request();
        std::vector<double> vec(static_cast<double *>(buf.ptr),
                                static_cast<double *>(buf.ptr) + buf.size);
        auto output_vec = muslib::mixer::zero_crossings(vec, pad);

        py::array_t<bool> result(output_vec.size());
        auto result_buf = result.request();
        bool *result_ptr = static_cast<bool *>(result_buf.ptr);

        std::copy(output_vec.begin(), output_vec.end(), result_ptr);

        return result;
      },
      "zero crossing rat", py::arg("signal"), py::arg("pad") = true);
  m.def(
      "zero_crossing_rate",
      [](py::array_t<double> sig, unsigned frame_length, unsigned hop_length) {
        py::buffer_info buf = sig.request();
        std::vector<double> vec(static_cast<double *>(buf.ptr),
                                static_cast<double *>(buf.ptr) + buf.size);
        std::vector<double> output_vec =
            muslib::mixer::zero_crossing_rate(vec, frame_length, hop_length);

        py::array_t<double> result(output_vec.size());
        auto result_buf = result.request();
        double *result_ptr = static_cast<double *>(result_buf.ptr);

        std::copy(output_vec.begin(), output_vec.end(), result_ptr);

        return result;
      },
      "zero_crossing_rate", py::arg("sig"), py::arg("frame_length") = 2048,
      py::arg("hop_length") = 512);
  m.def(
      "frame",
      [](const muslib::Signal1 &sig, unsigned frame_length,
         unsigned hop_length) {
        muslib::Signal2 frames =
            muslib::mixer::frame(sig, frame_length, hop_length);

        size_t n_frames = frames.size();
        size_t n_bins = frames[0].size();

        py::array_t<double> result({n_bins, n_frames});

        auto result_mutable = result.mutable_unchecked<2>();
        for (size_t i = 0; i < n_frames; ++i) {
          for (size_t j = 0; j < n_bins; ++j) {
            result_mutable(j, i) = frames[i][j];
          }
        }

        return result;
      },
      "frames", py::arg("sig"), py::arg("frame_length"), py::arg("hop_length"));
}
