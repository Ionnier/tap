cmake_minimum_required(VERSION 3.27)
set(ENV{CC} "/opt/homebrew/bin/gcc-13")
set(ENV{CXX} "/opt/homebrew/bin/g++-13")
project(tap)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*")
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "include/*")
file(GLOB_RECURSE IMPORTED RELATIVE ${CMAKE_SOURCE_DIR} "imported/*")
file(GLOB_RECURSE UTILS RELATIVE ${CMAKE_SOURCE_DIR} "utils/*")

include_directories(include)
include_directories(src)
include_directories(imported)
include_directories(utils)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        tap
        main.cpp
)

add_executable(
    test_a_star
    include/a_star.h
    src/a_star.cpp
    ${IMPORTED}
    test/testAStar.cpp
)

add_executable(
    test_dfs_bfs
    ${IMPORTED}
    src/dfs_bfs.cpp
    test/testDfsBfs.cpp
)

add_executable(
    test_openmp unused/setup_openmp.cpp
)

add_executable(
    test_compareDfsBfs
    ${SOURCES}
    ${HEADERS}
    ${IMPORTED}
    ${UTILS}
    test/testCompareDfsBfs.cpp
)

add_executable(
        test_pennantTree
        ${SOURCES}
        ${HEADERS}
        ${IMPORTED}
        ${UTILS}
        test/testPennantTree.cpp
)

add_executable(
        testPartitionRefinement
        ${SOURCES}
        ${HEADERS}
        ${IMPORTED}
        ${UTILS}
        test/testPartitionRefinement.cpp
)

find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    target_link_libraries(tap PUBLIC OpenMP::OpenMP_CXX)
    target_link_libraries(test_openmp PUBLIC OpenMP::OpenMP_CXX)
    target_link_libraries(test_compareDfsBfs PUBLIC OpenMP::OpenMP_CXX)
endif()