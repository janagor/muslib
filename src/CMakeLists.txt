set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(cpp_module STATIC cpp_module.cpp)
add_library(io_cpp STATIC io.cpp)

pybind11_add_module(python_bindings bindings.cpp)
pybind11_add_module(musio bind_io.cpp)

target_link_libraries(python_bindings PRIVATE cpp_module)
target_link_libraries(musio PUBLIC io_cpp SndFile::sndfile)
