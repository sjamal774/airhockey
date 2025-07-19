cmake_minimum_required(VERSION 3.10)

# Build glad as a static library
add_library(glad STATIC
    src/glad.c
)

# Tell glad where its headers live
target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include

)

find_path(GLM_INCLUDE_DIR glm/glm.hpp)
include_directories(${GLM_INCLUDE_DIR})
