project(air_hockey_app)

add_executable(main Main.cpp)
target_link_libraries(main PRIVATE game_lib gfx_lib)