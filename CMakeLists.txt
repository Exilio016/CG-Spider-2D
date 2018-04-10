cmake_minimum_required(VERSION 3.10)
project(Aranha2D)

set(CMAKE_CXX_STANDARD 11)

include_directories(includes)
add_executable(Aranha2D src/main.cpp src/spider.cpp includes/spider.h)

target_link_libraries(${PROJECT_NAME} glut GLU GL m)