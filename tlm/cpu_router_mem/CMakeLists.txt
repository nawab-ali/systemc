cmake_minimum_required(VERSION 3.10.2)

project(cpu_router_mem)

set (CMAKE_PREFIX_PATH /usr/local)
set (CMAKE_CXX_STANDARD ${SystemC_CXX_STANDARD})

include_directories(${CMAKE_PREFIX_PATH}/include)
find_library(systemc systemc ${CMAKE_PREFIX_PATH}/lib)
link_directories(${CMAKE_PREFIX_PATH}/lib)

# Executables
include_directories(include)
add_executable(cpu_router_mem src/main.cpp)
target_link_libraries(cpu_router_mem systemc)
