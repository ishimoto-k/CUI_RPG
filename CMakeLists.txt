cmake_minimum_required(VERSION 3.15)
project(Appeal)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_subdirectory(src/utility)
link_libraries(utility)


add_library(event STATIC src/Observer/Observer.cpp)
target_include_directories(event INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/Observer)

add_library(dungeon STATIC src/Dungeon/DungeonCreate.cpp)
target_include_directories(dungeon INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/Dungeon)

add_subdirectory(src/Model)

find_package(GLFW REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${GLFW_INCLUDE_DIR})

add_subdirectory(research)

add_executable(Appeal src/main.cpp)
target_link_libraries(Appeal
        ${GLFW_LIBRARIES}
        ${OPENGL_LIBRARY}
        dungeon
        utility
        Map
        )