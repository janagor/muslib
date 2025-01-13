add_library(muslib_io STATIC io.cpp io.hpp)
add_library(muslib_transform STATIC transform.cpp)
add_library(muslib_mixer STATIC mixer.cpp)
add_library(muslib_convert STATIC convert.cpp)
add_library(muslib_beat STATIC beat.cpp)
add_library(muslib_fft STATIC fft.cpp)

target_link_libraries(muslib_io PUBLIC SndFile::sndfile)
target_link_libraries(muslib_fft PUBLIC FFTW3::fftw3 muslib_convert)
target_link_libraries(muslib_transform PUBLIC FFTW3::fftw3 muslib_convert muslib_fft)
target_link_libraries(muslib_beat PUBLIC muslib_transform muslib_mixer)

pybind11_add_module(io io_bind.cpp)
pybind11_add_module(transform transform_bind.cpp)
pybind11_add_module(convert convert_bind.cpp)
pybind11_add_module(mixer mixer_bind.cpp)
pybind11_add_module(beat beat_bind.cpp)
pybind11_add_module(fft fft_bind.cpp)

target_link_libraries(io PUBLIC muslib_io)
target_link_libraries(transform PUBLIC muslib_transform)
target_link_libraries(convert PUBLIC muslib_convert)
target_link_libraries(mixer PUBLIC muslib_mixer)
target_link_libraries(beat PUBLIC muslib_beat)
target_link_libraries(fft PUBLIC muslib_fft)

add_executable(transform_exe transform_app.cpp)
target_link_libraries(transform_exe PUBLIC FFTW3::fftw3 muslib_transform)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/muslib_python_config)
set(DEST_DIR ${CMAKE_SOURCE_DIR}/muslib_lib/)

if(EXISTS ${DEST_DIR})
    message(STATUS "Removing existing directory: ${DEST_DIR}")
    file(REMOVE_RECURSE ${DEST_DIR})
endif()
file(COPY ${SOURCE_DIR}/ DESTINATION ${DEST_DIR})

install(TARGETS io transform convert mixer beat fft
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/muslib_lib)
