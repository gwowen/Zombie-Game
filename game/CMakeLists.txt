cmake_minimum_required(VERSION 2.8)
include_directories(${ENGINE_SOURCE_DIR}/Engine)

file(GLOB zombie_SRC "*.cpp")

add_executable(zombie ${zombie_SRC})

target_link_libraries(zombie Engine -lSDL2 -lGLEW -lGL)
