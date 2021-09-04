

add_library(Map STATIC
        Map/MapView.cpp
        Map/MapObject/DummyEnemy.cpp
        Map/MapObject/Enemy.cpp
        )
target_include_directories(Map INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/Map
        ${CMAKE_CURRENT_LIST_DIR}/Map/MapObject
        )
target_link_libraries(Map dungeon)