cmake_policy(PUSH)

##############################################################
# Multiples of a and b for all numbers less than upper-bound #
##############################################################
set(
    QUEUE_PROJECT_SOURCE_FILES
    algorithms/queue/queue.h
)

add_executable(
    queue-project
    ${QUEUE_PROJECT_SOURCE_FILES}
)

#########################################################################
# Multiples of a and b for all numbers less than upper-bound Unit Tests #
#########################################################################
set(
    QUEUE_PROJECT_TEST_SOURCES
    algorithms/queue/test/queue.cpp
)

add_executable(
    queue-project-test
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
