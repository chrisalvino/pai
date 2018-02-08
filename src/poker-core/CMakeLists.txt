
cmake_minimum_required(VERSION 3.3)
project(poker-core)

include_directories(${PAI_SOURCE_DIR}/poker-core)
link_directories(${PAI_SOURCE_DIR}/poker-core)

add_library(poker-core board.cpp card.cpp deck.cpp holding.cpp holecards.cpp player.cpp table.cpp RandNumMT.cpp)