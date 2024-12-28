#include "io.hpp"
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(io, m) {
  m.doc() = "File operations";

  m.def(
      "load",
      [](const char *filename) -> py::array_t<double> {
        std::vector<double> data = muslib::io::load(filename);

        py::array_t<double> numpy_array(data.size(), data.data());

        return numpy_array;
      },
      "Load data from a file and return as a numpy array of float64");
}
