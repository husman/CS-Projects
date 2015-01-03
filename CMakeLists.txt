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

INCLUDE_DIRECTORIES(
    /usr/local/include
)

link_directories(
    /usr/local/lib
)

add_executable(wave-project ${WAVE_AUDIO_SOURCE_FILES})
target_link_libraries(wave-project SDL2 SDL2main SDL2_mixer)
