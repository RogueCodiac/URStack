cmake_minimum_required(VERSION 3.20)
project(URStack)

set(CMAKE_CXX_STANDARD 17)

add_executable(URStack main.cpp URStack.cpp URStack.h CommonIO.cpp CommonIO.h GenericIO.cpp)
