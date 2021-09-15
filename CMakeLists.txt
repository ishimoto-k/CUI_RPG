cmake_minimum_required(VERSION 3.7.2)
project(CUI_RPG)

set(CMAKE_CXX_STANDARD 14)

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

add_executable(CUI_RPG src/main.cpp)
target_link_libraries(CUI_RPG
        dungeon
        utility
        Map
        Title
        BattleScene
        )

link_libraries(dungeon Map)
add_executable(example_wall_stretching research/WallStretching.cpp)
add_executable(example_map_view research/ExampleMapScene.cpp)
add_executable(example_keybord_input research/ExampleKeyBoardInput.cpp)
add_executable(example_battle_scene research/ExampleBattleScene.cpp)
target_link_libraries(example_map_view dungeon Map)
target_link_libraries(example_battle_scene BattleScene)


add_executable(example_exp_calc research/ExampleExpCalculation.cpp)

add_custom_command(TARGET CUI_RPG POST_BUILD COMMAND
        ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:CUI_RPG>/assets)