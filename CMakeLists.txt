cmake_minimum_required(VERSION 3.6)
project(OpenOrd)

add_definitions(-DEMSCRIPTEN)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s TOTAL_MEMORY=1073741824 --bind -O2 -g3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s TOTAL_MEMORY=1073741824 --bind -O2 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s TOTAL_MEMORY=1073741824 --bind -O2 -g3")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s TOTAL_MEMORY=1073741824 --bind -O2 -g3")

INCLUDE_DIRECTORIES(
        /Users/andy/Downloads/emsdk_portable/emscripten/1.35.0/system/include
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s TOTAL_MEMORY=1073741824")

set(SOURCE_FILES
    src/DensityGrid.cpp
    src/DensityGrid.h
    src/emprintf.h
    src/graph.h
    src/layout.h
    src/Node.h
    src/graph.cpp)


add_executable(OpenOrd ${SOURCE_FILES})
