cmake_minimum_required(VERSION 3.15)
project(Appeal)

set(CMAKE_CXX_STANDARD 14)

add_compile_definitions(CURRENT_DIRECTORY="${CMAKE_CURRENT_LIST_DIR}")

add_subdirectory(submodule/yaml-cpp)
link_libraries(yaml-cpp)

add_subdirectory(src/utility)
add_library(event STATIC src/Observer/Observer.cpp)
target_include_directories(event INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/Observer)
add_library(userController STATIC src/UserController/KeyBoardController.cpp)
target_link_libraries(userController utility event)
target_include_directories(userController INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/UserController)
link_libraries(utility event userController)

add_library(dungeon STATIC src/Dungeon/DungeonCreate.cpp)
target_include_directories(dungeon INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/Dungeon)

add_subdirectory(src/Model)

add_subdirectory(research)

add_executable(Appeal src/main.cpp)
target_link_libraries(Appeal
        dungeon
        utility
        Map
        Title
        )