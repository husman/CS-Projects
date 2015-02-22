cmake_policy(PUSH)

##############################################################
# Multiples of a and b for all numbers less than upper-bound #
##############################################################
set(
    STRING_OCCURRENCE_SOURCE_FILES
    algorithms/string_occurrence/source/include/string_occurrence.h
)

add_executable(
    string-occurrence-project
    ${STRING_OCCURRENCE_SOURCE_FILES}
)

#########################################################################
# Multiples of a and b for all numbers less than upper-bound Unit Tests #
#########################################################################
set(
    STRING_OCCURRENCE_TEST_SOURCES
    algorithms/string_occurrence/test/test_string_occurrence.cpp
)

add_executable(
    string-occurrence-project-test
    ${QUEUE_PROJECT_SOURCE_FILES}
    ${QUEUE_PROJECT_TEST_SOURCES}
)

target_link_libraries(
    queue-project-test
    gtest
    gtest_main
    gmock
    gmock_main
)
add_test(
    queue-project-test
    queue-project-test
)

set_target_properties(queue-project-test PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(queue-project PROPERTIES LINKER_LANGUAGE CXX)

cmake_policy(POP)
