cmake_minimum_required(VERSION 3.14)
project(airhockey)

find_package(Freetype REQUIRED)

file(GLOB_RECURSE HEADERS "include/*.h")
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(gfx_lib ${HEADERS} ${SOURCES})

target_include_directories(gfx_lib PUBLIC
    include
    ${CMAKE_SOURCE_DIR}/libs/extern
)

target_link_libraries(gfx_lib PUBLIC
    glfw
    glad
    glm
    Freetype::Freetype
)
