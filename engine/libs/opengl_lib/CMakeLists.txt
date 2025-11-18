cmake_minimum_required(VERSION 3.10)

find_package(SFML REQUIRED COMPONENTS network window graphics system audio)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)


project(opengl_lib VERSION 0.1)

set(SOURCES
    src/opengl_lib/RenderSystemSFML.cpp
    )

add_library(opengl_lib STATIC ${SOURCES})

target_include_directories(opengl_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)

target_link_libraries(opengl_lib PUBLIC
     sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    mlg::mlg
    OpenGL::GL glfw GLEW::GLEW
)

add_library(opengl_lib::opengl_lib ALIAS opengl_lib)
