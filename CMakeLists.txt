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
    BigInteger/source/BigInteger.cpp
    BigInteger/source/main.cpp
)

add_executable(biginteger ${BIGINTEGER_SOURCE_FILES})

####################################
# Wave Audio Project
####################################
set(WAVE_AUDIO_SOURCE_FILES
    wave-project/wave_dec.cpp
    wave-project/waveplayer.cpp
)

INCLUDE_DIRECTORIES(
    /usr/local/include
)

link_directories(
    /usr/local/lib
)


add_executable(wave_project ${WAVE_AUDIO_SOURCE_FILES})
target_link_libraries(wave_project SDL2 SDL2main SDL2_mixer)
