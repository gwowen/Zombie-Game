cmake_minimum_required(VERSION 2.8)
file(GLOB Engine_SRC "*.cpp")
add_library(Engine ${Engine_SRC})
