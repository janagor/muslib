add_library(muslib_io STATIC io.cpp)
add_library(muslib_transform STATIC transform.cpp)
add_library(muslib_mixer STATIC mixer.cpp)
add_library(muslib_beat STATIC beat.cpp)
add_library(muslib_convert STATIC convert.cpp)

target_link_libraries(muslib_io PUBLIC SndFile::sndfile)
target_link_libraries(muslib_transform PUBLIC FFTW3::fftw3)

pybind11_add_module(io io_bind.cpp)
pybind11_add_module(transform transform_bind.cpp)

target_link_libraries(io PUBLIC muslib_io)
target_link_libraries(transform PUBLIC muslib_transform)

add_executable(transform_exe transform_app.cpp)
target_link_libraries(transform_exe PUBLIC muslib_transform)

install(TARGETS io transform
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/binaries)
