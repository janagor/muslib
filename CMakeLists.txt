cmake_minimum_required(VERSION 3.10.0)
project(muslib VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (PYTHON_EXECUTABLE "/home/janagorski/.pyenv/shims/python")
set(Python3_VERSION 3.12)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wextra -Wall -pedantic -fsanitize=undefined")
elseif (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
endif()

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)
find_package(SndFile REQUIRED)
find_package(FFTW3 REQUIRED)
find_package(GTest REQUIRED)

include_directories(src)
add_subdirectory(src)

enable_testing()
add_subdirectory(tests)


