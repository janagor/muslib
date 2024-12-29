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
}
