//
// Created by IshimotoKiko on 2021/09/03.
//


#include <iostream>
#include <vector>
#include <random>

#include "../src/Model/Character/DummyEnemy.hpp"
#include "../src/Model/Map/MapScene.hpp"
#include <DungeonCreate.hpp>
#include <KeyBoardController.hpp>
#include <thread>
int main(){
  MapScene mapView;
  Observer observer;
  observer.interface(std::make_shared<ObserverInterface>());
  observer.interface()->addListener(ObserverEventList::MAP_VIEW__PLAYER_CollisionDetection,[](SubjectData subject){
    auto msg = static_cast<MapScene::EventBody*>(subject.get());
    std::cout << "object collision detection bit = "<< msg->bit << std::endl;

  });
  observer.interface()->addListener(ObserverEventList::MAP_VIEW__ENEMY_CollisionDetection,[](SubjectData subject){
    auto msg = static_cast<MapScene::EventBody*>(subject.get());
    std::cout << "enemy was object collision detection bit = "<< msg->bit << std::endl;

  });
  mapView.addObserver(observer);
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
  mapView.view();
  for(int i=0;i<100;i++) {
    printf("\033[;H\033[2J");
    //    system("clear");
    mapView.update();
    mapView.view();
    int key = 0;
    int counter = 0;
    while (1) { /* キーが押されるまで待つ */
      std::this_thread::sleep_for(std::chrono::milliseconds(16));
      if (KeyBoardController::checkInputKey()) {
        key = getchar(); /* 入力されたキー番号 */
        break;
      }
      counter++;
      if (counter == 60) {
        break;
      }
    }
    std::cout << key << std::endl;
    if (key == 'w') {
      mapView.setPlayerDirection(Vector2::UP);
    } else if (key == 's') {
      mapView.setPlayerDirection(Vector2::DOWN);
    } else if (key == 'd') {
      mapView.setPlayerDirection(Vector2::RIGHT);
    } else if (key == 'a') {
      mapView.setPlayerDirection(Vector2::LEFT);
    } else if (key == 0) {
      mapView.setPlayerDirection(Vector2::NONE);
    }
  }
}