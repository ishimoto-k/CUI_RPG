


add_library(Charactor STATIC
        Charactor/Enemy.cpp
        Charactor/DummyEnemy.cpp
        )
target_include_directories(Charactor INTERFACE ${CMAKE_CURRENT_LIST_DIR}/Charactor)


add_library(Map STATIC Map/MapView.cpp)
target_include_directories(Map INTERFACE ${CMAKE_CURRENT_LIST_DIR}/MapView)
target_link_libraries(Map dungeon)