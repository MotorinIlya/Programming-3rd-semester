cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

project(lab0)

set(exe_name ${PROJECT_NAME})

add_library(corelib OBJECT word_reader.cpp word_writer.cpp)

add_executable(${exe_name} main.cpp)

target_link_libraries(${exe_name} corelib)
