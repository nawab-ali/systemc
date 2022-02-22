cmake_minimum_required(VERSION 3.10.2)

project(systolic_array)

set (CMAKE_PREFIX_PATH /usr/local)
set (CMAKE_CXX_STANDARD ${SystemC_CXX_STANDARD})

include_directories(${CMAKE_PREFIX_PATH}/include)
find_library(systemc systemc ${CMAKE_PREFIX_PATH}/lib)
link_directories(${CMAKE_PREFIX_PATH}/lib)

# Executables
include_directories(include)
add_executable(sim_pe src/sim_pe.cpp)
add_executable(sim_systolic_array src/sim_systolic_array.cpp)
target_link_libraries(sim_pe systemc)
target_link_libraries(sim_systolic_array systemc)
