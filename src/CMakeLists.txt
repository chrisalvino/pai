
cmake_minimum_required(VERSION 3.3)
project(pai)

set(CMAKE_CXX_FLAGS "-g -Wall -pedantic -Werror -std=c++1z")

add_subdirectory(poker-core)
# add_library(cards cards.cpp)
# add_executable(coupai cards)
# target_link_libraries(coupai cards)