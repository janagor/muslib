#include "io.hpp"
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

void ensure_numpy() {
  try {
    py::module sys = py::module_::import("sys");
    py::object modules = sys.attr("modules");

    if (!modules.contains("numpy")) {
      throw std::runtime_error("'numpy' is required but not imported");
    }
  } catch (const py::error_already_set &) {
    throw std::runtime_error(
        "an error occured while checking if 'numpy' is imported");
  }
}

PYBIND11_MODULE(io, m) {
  ensure_numpy();
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
