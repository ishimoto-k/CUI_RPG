//
// Created by IshimotoKiko on 2021/09/03.
//


#include <iostream>
#include <vector>
#include "../src/Model/Character/DummyEnemy.hpp"
#include "../src/Model/Map/MapScene.hpp"
#include "Model/GameStatus.hpp"
#include <DungeonCreate.hpp>
#include <KeyBoardController.hpp>
#include <Title.hpp>
#include <thread>
int main(){

  GameStatus gameStatus = GameStatus::TITLE;
  KeyBoardController keyBoardController;
  auto titleScene = std::make_shared<Title>();
  auto mapScene = std::make_shared<MapScene>();


  std::shared_ptr<GameSceneInterface> gameScene = titleScene; //起動時はタイトル画面

  Key key = Key::NONE;
  Observer observer;
  observer.interface(std::make_shared<ObserverInterface>());
  observer.interface()->addListener(ObserverEventList::MAP_VIEW__PLAYER_CollisionDetection,[](SubjectData subject){
    auto msg = static_cast<MapObjectInterface::EventBody*>(subject.get());
//    std::cout << "object collision detection bit = "<< msg->bit << std::endl;
  });
  observer.interface()->addListener(ObserverEventList::MAP_VIEW__ENEMY_CollisionDetection,[](SubjectData subject){
    auto msg = static_cast<MapObjectInterface::EventBody*>(subject.get());
//    std::cout << "enemy was object collision detection bit = "<< msg->bit << std::endl;
  });
  observer.interface()->addListener(ObserverEventList::KEYBOARD__ON_INPUT,[&](SubjectData subject){
    auto msg = static_cast<UserControllerInterface::EventBody*>(subject.get());
    gameStatus.keyBoardWait = GameStatus::KeyBoardWait::HIT;
    key = msg->key;
//    std::cout << "KEYBOARD__ON_INPUT "<< msg->key.debug() << std::endl;
  });
  observer.interface()->addListener(ObserverEventList::TITLE_SCENE_ON_SELECT,[&](SubjectData subject){
    auto msg = static_cast<Title::EventBody*>(subject.get());
    if(msg->selectList == Title::SelectList::START){
      gameStatus = GameStatus::MAP_VIEW;
    }
  });
  titleScene->addObserver(observer);

  keyBoardController.addObserver(observer);
  keyBoardController.startInputMonitoring();

  mapScene->addObserver(observer);
  mapScene->setDungeon(std::make_shared<DungeonCreate>(20,20));
  mapScene->dungeon->debug();
  auto pos = mapScene->getRandomNonePosition();
  std::vector<std::shared_ptr<MapObjectInterface>> enemies;
  for(int i=0;i<1;i++) {
    enemies.push_back(std::make_shared<DummyEnemy>(pos.x, pos.y));
    pos = mapScene->getRandomNonePosition();
  }

  mapScene->setEnemy({std::make_shared<DummyEnemy>(pos.x,pos.y),std::make_shared<DummyEnemy>(pos.x,pos.y)});
  pos = mapScene->getRandomNonePosition();
  mapScene->setPlayer(std::make_shared<Player>(pos.x,pos.y));
  gameScene->view();
  for(int i=0;i<100;i++) {
    printf("\033[;H\033[2J");
    //    system("clear");
    gameScene->update();
    gameScene->view();

    while (1) { /* キーが押されるまで待つ */
      if(gameStatus.keyBoardWait != GameStatus::WAIT){
        break;
      }
    }

    std::cout << key.debug() << std::endl;
    if (key == Key::UP) {
      gameScene->Up();
    } else if (key == Key::DOWN) {
      gameScene->Down();
    } else if (key == Key::RIGHT) {
      gameScene->Right();
    } else if (key == Key::LEFT) {
      gameScene->Left();
    } else if (key == Key::SELECT) {
      gameScene->Select();
    } else if (key == Key::CANCEL) {
      gameScene->Cancel();
    } else if (key == Key::ESC) {
      gameScene->Esc();
    }
    key = Key::NONE;
    gameStatus.keyBoardWait = GameStatus::KeyBoardWait::WAIT;
    if(gameStatus == GameStatus::TITLE){
      gameScene = titleScene;
    }else if(gameStatus == GameStatus::MAP_VIEW){
      gameScene = mapScene;
    }
  }
}