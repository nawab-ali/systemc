cmake_minimum_required(VERSION 3.10.2)

project(cpu)

set (CMAKE_PREFIX_PATH /Users/nawabali/Work/systemc-2.3.3)
set (CMAKE_CXX_STANDARD ${SystemC_CXX_STANDARD})

include_directories(${CMAKE_PREFIX_PATH}/include)
find_library(systemc systemc ${CMAKE_PREFIX_PATH}/lib)
link_directories(${CMAKE_PREFIX_PATH}/lib)

# Executables
include_directories(include)
add_executable(sim_cpu src/sim_cpu.cpp)
add_executable(sim_instr_decoder src/sim_instr_decoder.cpp)
add_executable(sim_memory src/sim_memory.cpp)
add_executable(sim_alu src/sim_alu.cpp)

target_link_libraries(sim_cpu systemc)
target_link_libraries(sim_instr_decoder systemc)
target_link_libraries(sim_memory systemc)
target_link_libraries(sim_alu systemc)