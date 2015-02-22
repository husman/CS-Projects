cmake_minimum_required(VERSION 2.6)

# For MS Visual Studio
project(Computer_Science_Projects)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

IF(WIN32)
    add_definitions(-DWIN32)
ENDIF(WIN32)

####################################
# Unbounded Integer Implementation #
####################################
set(BIGINTEGER_SOURCE_FILES
    big-integer-project/source/BigInteger.cpp
    big-integer-project/source/main.cpp
)

add_executable(big-integer-project ${BIGINTEGER_SOURCE_FILES})

####################################
# Wave Audio Project
####################################
set(WAVE_AUDIO_SOURCE_FILES
    wave-project/source/main.cpp
    wave-project/source/byte_reader.cpp
    wave-project/source/wave_player.cpp
    wave-project/source/wave_decoder.cpp
)

################################
# Includes and Libraries Dir.
################################
INCLUDE_DIRECTORIES(
    /usr/local/include
    /Users/haleeq/dev/cpp/test/include
)

link_directories(
    /usr/local/lib
    /Users/haleeq/dev/cpp/test/libs
)

add_executable(wave-project ${WAVE_AUDIO_SOURCE_FILES})
target_link_libraries(wave-project SDL2 SDL2main SDL2_mixer)

####################################
# Jpeg Decoder Project
####################################
set(JPEG_DECODER_PROJECT_SOURCE_FILES
    jpeg-decoder-project/source/main.cpp
    jpeg-decoder-project/source/byte_reader.cpp
    jpeg-decoder-project/source/jpeg_decoder.cpp
)
add_executable(jpeg-decoder-project ${JPEG_DECODER_PROJECT_SOURCE_FILES})

include(euler-project/euler-project.cmake)
include(algorithms/bfs/bfs-project.cmake)
# include(algorithms/queue/queue-project.cmake)

set(RANDOM_SOURCE_FILES
    algorithms/random/main.cpp
)

add_executable(random-project ${RANDOM_SOURCE_FILES})
