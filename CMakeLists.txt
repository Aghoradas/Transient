cmake_minimum_required(VERSION 3.31)
project(Point_Click)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Point_Click
        src/main.cpp
        src/player.cpp
        src/look_mech.cpp
        src/scene_engine.cpp
        src/scene_factory.cpp
        src/scene_operations.cpp
)


target_link_libraries(Point_Click
        PRIVATE raylib m pthread dl GL X11)
