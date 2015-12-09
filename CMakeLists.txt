cmake_minimum_required(VERSION 3.3)
project(Atomas)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Atom.h AtomRing.h)
add_executable(Atomas ${SOURCE_FILES})