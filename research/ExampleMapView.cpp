//
// Created by IshimotoKiko on 2021/09/03.
//


#include <iostream>
#include <vector>
#include <random>

#include "../src/Model/Map/MapView.hpp"
#include <DummyEnemy.hpp>
#include <DungeonCreate.hpp>
#include <InputKeyBoard.hpp>
int main(){
  MapView mapView;
  mapView.setDungeon(std::make_shared<DungeonCreate>(20,20));
  mapView.dungeon->debug();
  auto pos = mapView.getRandomNonePosition();
  std::vector<std::shared_ptr<MapObjectInterface>> enemies;
  for(int i=0;i<1;i++) {
    enemies.push_back(std::make_shared<DummyEnemy>(pos.x, pos.y));
    pos = mapView.getRandomNonePosition();
  }

  mapView.setEnemy({std::make_shared<DummyEnemy>(pos.x,pos.y),std::make_shared<DummyEnemy>(pos.x,pos.y)});
  pos = mapView.getRandomNonePosition();
  mapView.setPlayer(std::make_shared<Player>(pos.x,pos.y));
  mapView.draw();
  for(int i=0;i<100;i++) {
    printf( "\033[;H\033[2J" );
    system("clear");
    mapView.update();
    mapView.draw();
    int key;
    while (1) {	/* キーが押されるまで待つ */
      if ( InputKeyBoard::checkInputKey() ){
        key = getchar();	/* 入力されたキー番号 */
        break ;
      }
    }
    if(key == 'w'){
      mapView.setPlayerDirection(Vector2::UP);
    }
    else if(key == 's'){
      mapView.setPlayerDirection(Vector2::DOWN);
    }
    else if(key == 'd'){
      mapView.setPlayerDirection(Vector2::RIGHT);
    }
    else if(key == 'a'){
      mapView.setPlayerDirection(Vector2::LEFT);
    }
//    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}