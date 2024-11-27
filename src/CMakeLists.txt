add_library(cpp_module cpp_module.cpp)
# add_library(io io.cpp io.hpp)

pybind11_add_module(python_bindings bindings.cpp)

target_link_libraries(python_bindings PRIVATE cpp_module)

