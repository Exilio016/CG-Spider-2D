cmake_minimum_required(VERSION 3.10)
project(Aranha2D)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(includes ${OPENGL_INCLUDE_DIRs} ${GLUT_INCLUDE_DIRs})

file(GLOB SOURCES "src/*.cpp" "includes/*.h")

add_executable(Aranha2D ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} m)