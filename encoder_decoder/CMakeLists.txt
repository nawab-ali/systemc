cmake_minimum_required(VERSION 3.10.2)

project(encoder_decoder)

set (CMAKE_PREFIX_PATH /usr/local)
set (CMAKE_CXX_STANDARD ${SystemC_CXX_STANDARD})

include_directories(${CMAKE_PREFIX_PATH}/include)
find_library(systemc systemc ${CMAKE_PREFIX_PATH}/lib)
link_directories(${CMAKE_PREFIX_PATH}/lib)

# Executables
include_directories(include)
add_executable(four_two_encoder src/four_two_encoder_sim.cpp)
add_executable(two_four_decoder src/two_four_decoder_sim.cpp)
add_executable(three_eight_decoder src/three_eight_decoder_sim.cpp)

target_link_libraries(four_two_encoder systemc)
target_link_libraries(two_four_decoder systemc)
target_link_libraries(three_eight_decoder systemc)

