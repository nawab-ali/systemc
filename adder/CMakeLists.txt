cmake_minimum_required(VERSION 3.10.2)

project(adder)

set (CMAKE_PREFIX_PATH /usr/local)
set (CMAKE_CXX_STANDARD ${SystemC_CXX_STANDARD})

include_directories(${CMAKE_PREFIX_PATH}/include)
find_library(systemc systemc ${CMAKE_PREFIX_PATH}/lib)
link_directories(${CMAKE_PREFIX_PATH}/lib)

# Executables
include_directories(include)
add_executable(half_adder src/half_adder_sim.cpp)
add_executable(full_adder src/full_adder_sim.cpp)
target_link_libraries(half_adder systemc)
target_link_libraries(full_adder systemc)