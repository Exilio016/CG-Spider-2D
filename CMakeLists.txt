cmake_minimum_required(VERSION 3.10)
project(Aranha2D)

include_directories(includes)

set(CMAKE_CXX_STANDARD 11)
set(OPENGL-LIBS glut GLU GL)

file(GLOB SOURCES "src/*.cpp")

add_executable(Aranha2D ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${OPENGL-LIBS} m)