#include <pybind11/pybind11.h>
#include "cpp_module.h"

namespace py = pybind11;

PYBIND11_MODULE(python_bindings, m) {
    m.def("add", &add, "A function that adds two numbers");
}

