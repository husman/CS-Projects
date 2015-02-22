cmake_policy(PUSH)

##############################################################
# Multiples of a and b for all numbers less than upper-bound #
##############################################################
set(
    EULER_PROJECT_SOURCE_FILES
    euler-project/multiples-of-a-and-b.cpp
    euler-project/find-largest-prime-factor.cpp
    euler-project/sum-of-even-fibonacci-less-than-n.cpp
    euler-project/euler-project.cpp
)

add_executable(
    euler-project-executable
    ${EULER_PROJECT_SOURCE_FILES}
)

#########################################################################
# Multiples of a and b for all numbers less than upper-bound Unit Tests #
#########################################################################
set(
    EULER_PROJECT_TEST_SOURCES
    euler-project/test/multiples-of-a-and-b.cpp
    euler-project/test/find-largest-prime-factor.cpp
    euler-project/test/sum-of-even-fibonacci-less-than-n.cpp
    euler-project/test/euler-project.cpp
)

add_executable(
    euler-project-executable-test
    ${EULER_PROJECT_SOURCE_FILES}
    ${EULER_PROJECT_TEST_SOURCES}
)

target_link_libraries(
    euler-project-executable-test
    gtest
    gtest_main
    gmock
    gmock_main
)
add_test(
    euler-project-executable-test
    euler-project-executable-test
)

cmake_policy(POP)
