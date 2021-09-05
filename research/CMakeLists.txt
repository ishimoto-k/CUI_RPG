


link_libraries(dungeon Map)
add_executable(example_wall_stretching WallStretching.cpp)
add_executable(example_map_view ExampleMapView.cpp)
add_executable(example_keybord_input ExampleKeyBoardInput.cpp)
target_link_libraries(example_map_view dungeon Map)