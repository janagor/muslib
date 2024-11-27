#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include "io.hpp"

namespace py = pybind11;

PYBIND11_MODULE(musio, m) {
    m.doc() = "Python bindings for the musio library";

    // Bind the load function, converting std::vector<double> to numpy array
    m.def("load", [](const char* filename) -> py::array_t<double> {
        std::vector<double> data = musio::load(filename);

        // Create a numpy array from the std::vector
        py::array_t<double> numpy_array(data.size(), data.data());

        // Return the numpy array
        return numpy_array;
    }, "Load data from a file and return as a numpy array of float64");
}

