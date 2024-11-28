cmake_minimum_required(VERSION 3.10.0)
project(muslib VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)
find_package(SndFile REQUIRED)

include_directories(src)
add_subdirectory(src)

enable_testing()
add_subdirectory(tests)
