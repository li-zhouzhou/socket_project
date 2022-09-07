cmake_minimum_required(VERSION 3.16)
project(project)

set(CMAKE_CXX_STANDARD 14)

add_executable(project main.cpp server/Server.cpp server/Server.h led/Led.cpp led/Led.h)

target_link_libraries(project wiringPi)
