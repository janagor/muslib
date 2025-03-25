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
      "Load signal to variable from given file");

  m.def(
      "to_mono",
      [](const py::array_t<double> &input, int chnum) -> py::array_t<double> {
        muslib::Signal1 data(input.data(), input.data() + input.size());

        muslib::Signal1 result = muslib::io::to_mono(data, chnum);

        py::array_t<double> numpy_array(result.size(), result.data());

        return numpy_array;
      },
      "Convert to mono");

  m.def(
      "get_samplerate",
      [](const char *filename) -> double {
        return muslib::io::get_samplerate(filename);
      },
      "Calculates sample rate of signal.");

  m.def(
      "get_duration",
      [](const char *filename) -> double {
        return muslib::io::get_duration(filename);
      },
      "Calculate duration of audio file.");
}
