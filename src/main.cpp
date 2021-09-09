//
// Created by IshimotoKiko on 2021/09/03.
//


#include <iostream>
#include <vector>
#include <random>

#include "../src/Model/Character/DummyEnemy.hpp"
#include "../src/Model/Map/MapView.hpp"
#include "Model/GameStatus.hpp"
#include <DungeonCreate.hpp>
#include <KeyBoardController.hpp>
#include <Title.hpp>
#include <thread>
int main(){

  GameStatus gameStatus = GameStatus::TITLE;
  KeyBoardController keyBoardController;

  Title title;
  Key key = Key::NONE;
  MapView mapView;
  Observer observer;
  observer.interface(std::make_shared<ObserverInterface>());
  observer.interface()->addListener(ObserverEventList::MAP_VIEW__PLAYER_CollisionDetection,[](SubjectData subject){
    auto msg = static_cast<MapObjectInterface::EventBody*>(subject.get());
    std::cout << "object collision detection bit = "<< msg->bit << std::endl;
  });
  observer.interface()->addListener(ObserverEventList::MAP_VIEW__ENEMY_CollisionDetection,[](SubjectData subject){
    auto msg = static_cast<MapObjectInterface::EventBody*>(subject.get());
    std::cout << "enemy was object collision detection bit = "<< msg->bit << std::endl;
  });
  observer.interface()->addListener(ObserverEventList::KEYBOARD__ON_INPUT,[&](SubjectData subject){
    auto msg = static_cast<UserControllerInterface::EventBody*>(subject.get());
    gameStatus.keyBoardWait = GameStatus::KeyBoardWait::HIT;
    key = msg->key;
    std::cout << "KEYBOARD__ON_INPUT "<< msg->key.debug() << std::endl;
  });
  keyBoardController.addObserver(observer);
  keyBoardController.startInputMonitoring();

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
  mapView.draw();
  for(int i=0;i<100;i++) {
    printf("\033[;H\033[2J");
    //    system("clear");
    if(gameStatus == GameStatus::TITLE){
      title.view();
    }else {
      mapView.update();
      mapView.draw();
    }

    while (1) { /* キーが押されるまで待つ */
      if(gameStatus.keyBoardWait != GameStatus::WAIT){
        break;
      }
    }

    if(gameStatus == GameStatus::TITLE){
      std::cout << key.debug() << std::endl;
      if (key == Key::UP) {
        title.cursorUp();
      } else if (key == Key::DOWN) {
        title.cursorDown();
      } else if (key == Key::RIGHT) {
      } else if (key == Key::LEFT) {
      } else if (key == Key::ESC) {
      }
    }else {
      std::cout << key.debug() << std::endl;
      if (key == Key::UP) {
        mapView.setPlayerDirection(Vector2::UP);
      } else if (key == Key::DOWN) {
        mapView.setPlayerDirection(Vector2::DOWN);
      } else if (key == Key::RIGHT) {
        mapView.setPlayerDirection(Vector2::RIGHT);
      } else if (key == Key::LEFT) {
        mapView.setPlayerDirection(Vector2::LEFT);
      } else if (key == Key::ESC) {
        mapView.setPlayerDirection(Vector2::NONE);
      }
    }
    key = Key::NONE;
    gameStatus.keyBoardWait = GameStatus::KeyBoardWait::WAIT;
  }
}