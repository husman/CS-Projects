cmake_minimum_required(VERSION 2.6)

# For MS Visual Studio
project(Computer_Science_Projects)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

IF(WIN32)
    add_definitions(-DWIN32)
ENDIF(WIN32)

set(BIGINTEGER_SOURCE_FILES
    BigInteger/source/BigInteger.cpp
    BigInteger/source/main.cpp
)


add_executable(biginteger ${BIGINTEGER_SOURCE_FILES})