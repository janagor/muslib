#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/complex.h>
#include <pybind11/stl.h>
#include "transform.hpp"

namespace py = pybind11;

void ensure_numpy() {
    try {
        py::module sys = py::module_::import("sys");
        py::object modules = sys.attr("modules");

        if (!modules.contains("numpy")) {
        throw std::runtime_error("'numpy' is required but not imported");
        }
    } catch (const py::error_already_set&) {
        throw std::runtime_error("an error occured while checking if 'numpy' is imported");
    }
}

PYBIND11_MODULE(m_transform, m) {
    ensure_numpy();
    m.doc() = "Signal processing";

    m.def("stft", [](const muslib::transform::real_signal& signal, int n_fft, int hop_length) {
        muslib::transform::complex_coefs coefs = muslib::transform::stft(signal, n_fft, hop_length);

        size_t n_frames = coefs.size();
        size_t n_bins = coefs[0].size();

        py::array_t<std::complex<double>> result({n_frames, n_bins});

        auto result_mutable = result.mutable_unchecked<2>();
        for (size_t i = 0; i < n_frames; ++i) {
            for (size_t j = 0; j < n_bins; ++j) {
                result_mutable(i, j) = coefs[i][j];
            }
        }

        return result;
    }, "Compute the Short-Time Fourier Transform (STFT)",
       py::arg("signal"), py::arg("n_fft"), py::arg("hop_length"));
}

