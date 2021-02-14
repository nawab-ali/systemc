cmake_minimum_required(VERSION 3.10.2)

project(shift_reg)

set (CMAKE_PREFIX_PATH /usr/local)
set (CMAKE_CXX_STANDARD ${SystemC_CXX_STANDARD})

include_directories(${CMAKE_PREFIX_PATH}/include)
find_library(systemc systemc ${CMAKE_PREFIX_PATH}/lib)
link_directories(${CMAKE_PREFIX_PATH}/lib)

# Main executable
include_directories(include)
add_executable(d_ff src/d_ff_sim.cpp)
add_executable(shift_reg src/shift_reg_sim.cpp)
target_link_libraries(d_ff systemc)
target_link_libraries(shift_reg systemc)