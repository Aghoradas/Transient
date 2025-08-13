cmake_minimum_required(VERSION 3.31)
project(Transient)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Transient
        src/main.cpp
        src/player.cpp
        src/look_mech.cpp
        src/scene_engine.cpp
        src/scene_factory.cpp
        src/scene_operations.cpp
        src/inventory.cpp
)


target_link_libraries(Transient
        PRIVATE raylib m pthread dl GL X11)
