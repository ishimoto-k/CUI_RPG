


link_libraries(dungeon Map Charactor)
add_executable(wall_stretching WallStretching.cpp)
add_executable(map_view ExampleMapView.cpp)
target_link_libraries(map_view dungeon Map Charactor)