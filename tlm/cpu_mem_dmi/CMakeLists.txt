cmake_minimum_required(VERSION 3.10.2)

project(cpu_mem_dmi)

set (CMAKE_PREFIX_PATH /usr/local)
set (CMAKE_CXX_STANDARD ${SystemC_CXX_STANDARD})

include_directories(${CMAKE_PREFIX_PATH}/include)
find_library(systemc systemc ${CMAKE_PREFIX_PATH}/lib)
link_directories(${CMAKE_PREFIX_PATH}/lib)

# Executables
include_directories(include)
add_executable(cpu_mem_dmi src/main.cpp)
target_link_libraries(cpu_mem_dmi systemc)
