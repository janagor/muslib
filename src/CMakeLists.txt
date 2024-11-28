set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto=4")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)

add_library(cpp_module STATIC cpp_module.cpp)

add_library(io STATIC io.cpp)

target_link_libraries(io PUBLIC SndFile::sndfile)

pybind11_add_module(python_bindings bindings.cpp)
pybind11_add_module(m_io io_bind.cpp)

target_link_libraries(python_bindings PUBLIC cpp_module)
target_link_libraries(m_io PUBLIC io)

