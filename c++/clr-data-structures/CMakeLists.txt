cmake_minimum_required(VERSION 2.8)

################################
# Includes and Libraries Dir.
################################
include_directories(
    /Users/haleeq/dev/cpp/test/include
)

link_directories(
    /Users/haleeq/dev/cpp/test/libs
)

################################
# Stack
################################
set(
    stack_sources
    stack/stack.cpp
)

add_executable(stack
    ${stack_sources}
    stack/main.cpp
)

################################
# Stack Unit Tests
################################
set(
    stack_test_sources
    stack/test/stack.cpp
)

add_executable(
    test-stack
    ${stack_sources}
    ${stack_test_sources}
)

target_link_libraries(test-stack gtest gtest_main gmock gmock_main)
add_test(test-stack test-stack)


################################
# One-Dimension Peak Finding
################################
set(
    1d_peak_finding_sources
    peak-finding/one-dimension/peak.cpp
)

add_executable(1d_peak-finding
    ${1d_peak_finding_sources}
    peak-finding/one-dimension/main.cpp
)

########################################
# One-Dimension Peak Finding Unit Tests
########################################
set(
    1d_peak_finding_test_sources
    peak-finding/one-dimension/test/peak.cpp
)

add_executable(
    1d_test-peak-finding
    ${1d_peak_finding_sources}
    ${1d_peak_finding_test_sources}
)

target_link_libraries(1d_test-peak-finding gtest gtest_main gmock gmock_main)
add_test(1d_test-peak-finding 1d_test-peak-finding)
