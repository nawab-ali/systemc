cmake_minimum_required(VERSION 3.10.2)

project(systolic_array)

set (CMAKE_PREFIX_PATH /usr/local)
set (CMAKE_CXX_STANDARD ${SystemC_CXX_STANDARD})

include_directories(${CMAKE_PREFIX_PATH}/include)
find_library(systemc systemc ${CMAKE_PREFIX_PATH}/lib)
link_directories(${CMAKE_PREFIX_PATH}/lib)

# Executables
include_directories(include)
add_executable(systolic_array src/main.cpp)
target_link_libraries(systolic_array systemc)
