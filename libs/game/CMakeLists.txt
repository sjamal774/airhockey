file(GLOB_RECURSE HEADERS "include/*.h")
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_library(game_lib ${HEADERS} ${SOURCES})
find_path(GLM_INCLUDE_DIR glm/glm.hpp)
include_directories(${GLM_INCLUDE_DIR})
target_include_directories(game_lib PUBLIC include)
target_link_libraries(game_lib PUBLIC glfw glad glm gfx_lib)
