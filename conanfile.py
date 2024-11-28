from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout

class MyProjectConan(ConanFile):
    name = "muslib"
    version = "0.1.0"
    settings = "os", "compiler", "build_type", "arch"
    requires = "pybind11/2.13.6", "gtest/1.15.0", "libsndfile/1.2.2"
    generators = "CMakeDeps", "CMakeToolchain"
    exports_sources = "CMakeLists.txt", "src/*", "tests/*"

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

