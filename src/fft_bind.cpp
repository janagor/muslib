#include "fft.hpp"

#include <pybind11/complex.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(fft, m) {
  m.doc() = "fft";

  m.def(
      "irfft",
      [](py::array_t<double> sig, unsigned n_fft) {
        py::buffer_info buf = sig.request();
        muslib::Signal1 vec(static_cast<double *>(buf.ptr),
                            static_cast<double *>(buf.ptr) + buf.size);
        auto output_vec = muslib::fft::irfft(vec, n_fft);

        py::array_t<double> result(output_vec.size());
        auto result_buf = result.request();
        double *result_ptr = static_cast<double *>(result_buf.ptr);

        std::copy(output_vec.begin(), output_vec.end(), result_ptr);

        return result;
      },
      "irfft", py::arg("signal"), py::arg("n_fft") = 22050);
}
