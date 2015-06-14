cmake_minimum_required(VERSION 2.8)

project(SkiMountain)

# Sources
file(GLOB CHEADERS *.hpp)
file(GLOB CSOURCES *.cpp)

# Flags
set(CMAKE_BUILD_TYPE "DEBUG")

## C++11 flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

## Optimizations
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Werror")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s")

# Executable
add_executable(ski ${CHEADERS} ${CSOURCES})
target_link_libraries(ski)