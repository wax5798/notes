cmake_minimum_required(VERSION 3.10)

project(HELLO)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(LIBRARY_DIR ${PROJECT_BINARY_DIR}/output/libs)
set(BIN_DIR ${PROJECT_BINARY_DIR}/output/bin)

include_directories(${INCLUDE_DIR})
link_directories(${LIBRARY_DIR})

MESSAGE(STATUS "##PROJECT_SOURCE_DIR is " ${PROJECT_SOURCE_DIR})
MESSAGE(STATUS "##PROJECT_BINARY_DIR is " ${PROJECT_BINARY_DIR})

set(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})
set(LIBRARY_OUTPUT_PATH ${LIBRARY_DIR})

add_subdirectory(src)
