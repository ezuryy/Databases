cmake_minimum_required(VERSION 3.16)
project(HW1_2)

set(CMAKE_CXX_STANDARD 17)

link_libraries(stdc++fs)

add_executable(HW1_2 main.cpp Warehouse.cpp Warehouse.h Shoes.cpp Shoes.h Clothes.cpp Clothes.h func.cpp func.h)