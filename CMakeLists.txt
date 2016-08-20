cmake_minimum_required(VERSION 3.6)
project(OpenOrd)

add_definitions("--bind -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --bind -O3 -std=c++11")
INCLUDE_DIRECTORIES(
        /Users/andy/Downloads/emsdk_portable/emscripten/1.35.0/system/include
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCE_FILES
    src/DensityGrid.cpp
    src/DensityGrid.h
    src/emprintf.h
    src/graph.cpp
    src/graph.h
    src/layout.h
    src/Node.h)


add_executable(OpenOrd ${SOURCE_FILES})
