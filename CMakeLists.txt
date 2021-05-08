cmake_minimum_required(VERSION 3.19)
project(RobocupPy)

set(CMAKE_CXX_STANDARD 14)

include_directories(HelloClass)

add_executable(RobocupPy
        HelloClass/test.cc
        HelloClass/worldmodelWrap.cpp
        HelloClass/worldmodelWrap.h)
