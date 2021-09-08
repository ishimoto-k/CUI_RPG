

add_library(Map STATIC
        Map/MapView.cpp
        )
target_include_directories(Map INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/Map
        )
target_link_libraries(Map dungeon)

add_library(Skill STATIC
        Character/Skill/Skills.cpp
        Character/Command/Attack.cpp
        Character/Command/Escape.cpp
        )
target_include_directories(Skill INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/Character/Skill
        ${CMAKE_CURRENT_LIST_DIR}/Character/Command
        )

add_library(Character STATIC
        Character/DummyEnemy.cpp
        Character/Enemy.cpp
        Character/Player.cpp
        )
target_include_directories(Character INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/Character
        )
target_link_libraries(Character Skill Map)
target_link_libraries(Map Character)

add_library(BattleScene STATIC
        BattleScene/BattleScene.cpp
        )
target_include_directories(BattleScene INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/BattleScene
        )
target_link_libraries(BattleScene Map Character)
