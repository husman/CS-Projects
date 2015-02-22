cmake_policy(PUSH)

##############################################################
# Multiples of a and b for all numbers less than upper-bound #
##############################################################
set(
    BFS_PROJECT_SOURCE_FILES
    algorithms/bfs/graph.cpp
    algorithms/bfs/vertex.cpp
)

add_executable(
    bfs-project-executable
    ${BFS_PROJECT_SOURCE_FILES}
)

#########################################################################
# Multiples of a and b for all numbers less than upper-bound Unit Tests #
#########################################################################
set(
    BFS_PROJECT_TEST_SOURCES
    algorithms/bfs/test/vertex.cpp
    algorithms/bfs/test/graph.cpp
)

add_executable(
    bfs-project-executable-test
    ${BFS_PROJECT_SOURCE_FILES}
    ${BFS_PROJECT_TEST_SOURCES}
)

target_link_libraries(
    bfs-project-executable-test
    gtest
    gtest_main
    gmock
    gmock_main
)
add_test(
    bfs-project-executable-test
    bfs-project-executable-test
)

cmake_policy(POP)
