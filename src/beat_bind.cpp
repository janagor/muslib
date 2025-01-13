#include "beat.hpp"

#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(beat, m) {
  m.doc() = "Beat";

  m.def(
      "onset_strength",
      [](py::array_t<double> sig, double sr) {
        py::buffer_info buf = sig.request();
        muslib::Signal1 vec(static_cast<double *>(buf.ptr),
                            static_cast<double *>(buf.ptr) + buf.size);
        auto output_vec = muslib::beat::onset_strength(vec, sr);

        py::array_t<double> result(output_vec.size());
        auto result_buf = result.request();
        double *result_ptr = static_cast<double *>(result_buf.ptr);

        std::copy(output_vec.begin(), output_vec.end(), result_ptr);

        return result;
      },
      "onset_strength", py::arg("signal"), py::arg("sr") = 22050);

  m.def(
      "tempogram",
      [](const py::array_t<double> &input, double sr,
         double hop_length) -> py::array_t<double> {
        py::buffer_info buf = input.request();
        std::vector<double> vec(static_cast<double *>(buf.ptr),
                                static_cast<double *>(buf.ptr) + buf.size);

        muslib::Signal2 coefs = muslib::beat::tempogram(vec, sr, hop_length);

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
      "Tempogram", py::arg("input"), py::arg("sr") = 22050,
      py::arg("hop_length") = 512);
}
