cmake_minimum_required(VERSION 3.27)
project(tap)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*")
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "include/*")
file(GLOB_RECURSE IMPORTED RELATIVE ${CMAKE_SOURCE_DIR} "imported/*")

include_directories(include)
include_directories(src)
include_directories(imported)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        tap
        main.cpp
        ${SOURCES}
        ${HEADERS}
        ${IMPORTED}
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