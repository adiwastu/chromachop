cmake_minimum_required(VERSION 3.10)
project(Chromachop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB SOURCES "source/*.cpp")

add_executable(chromachop ${SOURCES} "include/WebpConverter.h" "source/WebpConverter.cpp")
