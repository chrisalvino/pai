
cmake_minimum_required(VERSION 3.3)
project(PAI)

set(CMAKE_CXX_FLAGS "-g -Wall -pedantic -Werror -std=c++1z")

set(CORELIBS m)

add_subdirectory(poker-core)
include_directories(${PAI_SOURCE_DIR}/poker-core)
link_directories(${PAI_BINARY_DIR}/poker-core)

add_executable(pai pai.cpp)
target_link_libraries(pai poker-core ${CORELIBS}) 
