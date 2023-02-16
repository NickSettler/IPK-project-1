cmake_minimum_required(VERSION 3.23)
project(ipkcpc)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)

add_executable(ipkcpc src/client.cpp src/client.h)