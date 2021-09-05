

add_library(Map STATIC
        Map/MapView.cpp
        Map/MapObject/DummyEnemy.cpp
        Map/MapObject/Enemy.cpp
        Map/MapObject/Player.cpp
        )
target_include_directories(Map INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/Map
        ${CMAKE_CURRENT_LIST_DIR}/Map/MapObject
        )
target_link_libraries(Map dungeon)
add_library(BattleScene STATIC
        BattleScene/BattleScene.cpp
        )
target_include_directories(BattleScene INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/BattleScene
        )

add_library(Data STATIC
        Data/Character.cpp
        )
target_include_directories(Data INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/Data
        )