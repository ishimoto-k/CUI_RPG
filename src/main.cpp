//
// Created by IshimotoKiko on 2021/09/03.
//

#include "../src/Model/Character/DummyEnemy.hpp"
#include "../src/Model/Map/MapScene.hpp"
#include "Model/BattleScene/BattleScene.hpp"
#include "Model/GameStatus.hpp"
#include <DungeonCreate.hpp>
#include <KeyBoardController.hpp>
#include <Title.hpp>
#include <iostream>
#include <thread>
#include <vector>
int main(){

  GameStatus gameStatus = GameStatus::TITLE;
  KeyBoardController keyBoardController;
  auto titleScene = std::make_shared<Title>();
  auto mapScene = std::make_shared<MapScene>();
  auto battleScene = std::make_shared<BattleScene>();
  std::vector<std::string> log;
  std::shared_ptr<Player> player = nullptr;

  std::shared_ptr<GameSceneInterface> gameScene = titleScene; //起動時はタイトル画面

  Key key = Key::NONE;
  Observer observer;
  observer.interface(std::make_shared<ObserverInterface>());
  observer.interface()->addListener(ObserverEventList::MAP_VIEW__PLAYER_CollisionDetection,[&](SubjectData subject){
    auto msg = static_cast<MapScene::EventBody*>(subject.get());
    if(msg->bit == BitMapKind::ENEMY){
      if(gameStatus != GameStatus::BATTLE){
        log.push_back("敵と遭遇した");
        battleScene->setPlayer(player);
        battleScene->setEnemy(mapScene->getEnemyFromPos(msg->toPosition));
        gameStatus = GameStatus::BATTLE;
      }
    }
    std::cout << "object collision detection bit = "<< msg->bit << std::endl;
  });
  observer.interface()->addListener(ObserverEventList::MAP_VIEW__ENEMY_CollisionDetection,[&](SubjectData subject){
    auto msg = static_cast<MapScene::EventBody*>(subject.get());
    if(msg->bit == BitMapKind::PLAYER){
      if(gameStatus != GameStatus::BATTLE){
        log.push_back("敵から遭遇した");
        battleScene->setPlayer(player);
        battleScene->setEnemy(mapScene->getEnemyFromPos(msg->fromPosition));
        gameStatus = GameStatus::BATTLE;
      }
    }
    std::cout << "enemy was object collision detection bit = "<< msg->bit << std::endl;
  });
  observer.interface()->addListener(ObserverEventList::KEYBOARD__ON_INPUT,[&](SubjectData subject){
    auto msg = static_cast<UserControllerInterface::EventBody*>(subject.get());
    gameStatus.keyBoardWait = KeyBoardWait::HIT;
    key = msg->key;
//    std::cout << "KEYBOARD__ON_INPUT "<< msg->key.debug() << std::endl;
  });
  observer.interface()->addListener(ObserverEventList::TITLE_SCENE_ON_SELECT,[&](SubjectData subject){
    auto msg = static_cast<Title::EventBody*>(subject.get());
    if(msg->selectList == Title::SelectList::START){
      gameStatus = GameStatus::MAP_VIEW;
    }
  });

  observer.interface()->addListener(ObserverEventList::BATTLE_SCENE_ESCAPE,[&](SubjectData subject){
    auto msg = static_cast<BattleScene::EventBody*>(subject.get());
    std::cout << "BATTLE_SCENE_ESCAPE ";
    gameStatus = GameStatus::MAP_VIEW;
  });
  observer.interface()->addListener(ObserverEventList::BATTLE_SCENE_WIN,[&](SubjectData subject){
    auto msg = static_cast<BattleScene::EventBody*>(subject.get());
    //todo 倒した敵情報をsharedで取得し、削除する。mapSeaneが削除する。
    std::cout << "BATTLE_SCENE_WIN ";
    gameStatus = GameStatus::MAP_VIEW;
  });
  observer.interface()->addListener(ObserverEventList::BATTLE_SCENE_LOSE,[&](SubjectData subject){
    auto msg = static_cast<BattleScene::EventBody*>(subject.get());
    std::cout << "BATTLE_SCENE_LOSE ";
    gameStatus = GameStatus::GAME_OVER;
  });

  titleScene->addObserver(observer);

  keyBoardController.addObserver(observer);
  keyBoardController.startInputMonitoring();

  battleScene->addObserver(observer);
  mapScene->addObserver(observer);
  mapScene->makeDungeon(0);
  mapScene->dungeon->debug();
  Vector2 pos = Vector2::NONE;

  pos = mapScene->getRandomNonePosition();
  player = std::make_shared<Player>(pos.x,pos.y);
  mapScene->setPlayer(player);
  gameScene->view();
  for(int i=0;gameStatus != GameStatus::GAME_OVER;i++) {
    //    system("clear");
    while (1) { /* キーが押されるまで待つ */
      if (gameStatus.keyBoardWait != KeyBoardWait::WAIT) {
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
    gameStatus.keyBoardWait = KeyBoardWait::WAIT;
    if (gameStatus == GameStatus::TITLE) {
      gameScene = titleScene;
    } else if (gameStatus == GameStatus::MAP_VIEW) {
      gameScene = mapScene;
    } else if (gameStatus == GameStatus::BATTLE) {
      gameScene = battleScene;
    } else if (gameStatus == GameStatus::GAME_OVER) {
      break;
    }
    gameScene->update();
    printf("\033[;H\033[2J");
    std::cout << "gameStatus " << gameStatus.log() << std::endl;
    gameScene->view();
    for (auto i : log) {
      std::cout << i << std::endl;
    }
    log.clear();
  }
}