cmake_minimum_required(VERSION 3.10.2)

project(adder)

set (CMAKE_PREFIX_PATH /usr/local)
set (CMAKE_CXX_STANDARD ${SystemC_CXX_STANDARD})

include_directories(${CMAKE_PREFIX_PATH}/include)
find_library(systemc systemc ${CMAKE_PREFIX_PATH}/lib)
link_directories(${CMAKE_PREFIX_PATH}/lib)

# Main executable
include_directories(include)
add_executable(adder src/main.cpp)
target_link_libraries(adder systemc)