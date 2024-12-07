add_library(io STATIC io.cpp)
add_library(transform STATIC transform.cpp)
add_library(mixer STATIC mixer.cpp)
add_library(beat STATIC beat.cpp)
add_library(convert STATIC convert.cpp)

target_link_libraries(io PUBLIC SndFile::sndfile)
target_link_libraries(transform PUBLIC FFTW3::fftw3)

pybind11_add_module(m_io io_bind.cpp)
pybind11_add_module(m_transform transform_bind.cpp)

target_link_libraries(m_io PUBLIC io)
target_link_libraries(m_transform PUBLIC transform)

add_executable(transform_exe transform_app.cpp)
target_link_libraries(transform_exe PUBLIC transform)

install(TARGETS m_io m_transform
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/muslib_python_config)
