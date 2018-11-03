cmake_minimum_required(VERSION 3.6)

set(PROJECT_NAME
        "Trabalho2_CG2018.2"
        )

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp Vector.h Screen.h Item.h LineStrip.h Color.h Polygon.h Point.h Circle.h HalfEdge.h Edge.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})