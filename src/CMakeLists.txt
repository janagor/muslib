set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto=4")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)

add_library(cpp_module STATIC cpp_module.cpp)

add_library(io STATIC io.cpp)
add_library(transform STATIC transform.cpp)

target_link_libraries(io PUBLIC SndFile::sndfile)
target_link_libraries(transform PUBLIC FFTW3::fftw3)

pybind11_add_module(python_bindings bindings.cpp)
pybind11_add_module(m_io io_bind.cpp)
pybind11_add_module(m_transform transform_bind.cpp)

target_link_libraries(python_bindings PUBLIC cpp_module)
target_link_libraries(m_io PUBLIC io)
target_link_libraries(m_transform PUBLIC transform)

add_executable(transform_exe transform_app.cpp)
target_link_libraries(transform_exe PUBLIC transform)
