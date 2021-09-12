//
// Created by IshimotoKiko on 2021/09/03.
//

#include "../src/Model/Character/DummyEnemy.hpp"
#include "../src/Model/Map/MapScene.hpp"
#include "Model/BattleScene/BattleScene.hpp"
#include "Model/GameSeaneStatus.hpp"
#include <DungeonCreate.hpp>
#include <KeyBoardController.hpp>
#include <Title.hpp>
#include <iostream>
#include <thread>
#include <vector>

#include "GameInformation.hpp"

int main(){
  GameInformation gameInformation;
  gameInformation.setSlot(0);

  GameSeaneStatus gameStatus = GameSeaneStatus::TITLE;
  GameSeaneStatus prevGameStatus = gameStatus;
  KeyBoardController keyBoardController;
  auto titleScene = std::make_shared<Title>();
  auto mapScene = std::make_shared<MapScene>();
  auto battleScene = std::make_shared<BattleScene>();
  std::vector<std::string> log;
  std::shared_ptr<Player> player = nullptr;

  std::shared_ptr<GameSceneInterface> gameScene = titleScene; //起動時はタイトル画面
  if(gameInformation.hasSaveFile()){
    titleScene->setCursor(Title::SelectList::LOAD);
  }

  Key key = Key::NONE;
  Observer observer;
  observer.interface(std::make_shared<ObserverInterface>());
  observer.interface()->addListener(ObserverEventList::MAP_SCENE__PLAYER_CollisionDetection,[&](SubjectData subject){
    auto msg = static_cast<MapScene::EventBody*>(subject.get());
    if(msg->bit == BitMapKind::ENEMY){
      if(gameStatus != GameSeaneStatus::BATTLE){
        log.push_back("敵と遭遇した");
        battleScene->setPlayer(player);
        battleScene->setEnemy(mapScene->getEnemyFromPos(msg->toPosition));
        gameStatus = GameSeaneStatus::BATTLE;
      }
    }
//    std::cout << "object collision detection bit = "<< msg->bit << std::endl;
  });
  observer.interface()->addListener(ObserverEventList::MAP_SCENE__ENEMY_CollisionDetection,[&](SubjectData subject){
    auto msg = static_cast<MapScene::EventBody*>(subject.get());
    if(msg->bit == BitMapKind::PLAYER){
      if(gameStatus != GameSeaneStatus::BATTLE){
        log.push_back("敵と遭遇した");
        battleScene->setPlayer(player);
        battleScene->setEnemy(mapScene->getEnemyFromPos(msg->fromPosition));
        gameStatus = GameSeaneStatus::BATTLE;
      }
    }
//    std::cout << "enemy was object collision detection bit = "<< msg->bit << std::endl;
  });
  observer.interface()->addListener(ObserverEventList::KEYBOARD__ON_INPUT,[&](SubjectData subject){
    auto msg = static_cast<UserControllerInterface::EventBody*>(subject.get());
    gameStatus.keyBoardWait = KeyBoardWait::HIT;
    key = msg->key;
  });
  observer.interface()->addListener(ObserverEventList::TITLE_SCENE_ON_SELECT,[&](SubjectData subject){
    auto msg = static_cast<Title::EventBody*>(subject.get());
    if(msg->selectList == Title::SelectList::START){
      gameInformation.create();
      mapScene->makeDungeon(gameInformation.getInfo().mapLevel);
      auto pos = mapScene->getRandomNonePosition();
      player = std::make_shared<Player>(pos.x,pos.y,0);
      mapScene->setPlayer(player,false);
      gameStatus = GameSeaneStatus::MAP_VIEW;
    }else if(msg->selectList == Title::SelectList::LOAD){
      mapScene->makeDungeon(gameInformation.getInfo().mapLevel);
      auto pos = mapScene->getRandomNonePosition();
      player = std::make_shared<Player>(pos.x,pos.y,gameInformation.getInfo().exp);
      mapScene->setPlayer(player,false);
      gameStatus = GameSeaneStatus::MAP_VIEW;
    }else if(msg->selectList == Title::SelectList::END){
      gameStatus = GameSeaneStatus::GAME_OVER;
    }
  });

  observer.interface()->addListener(ObserverEventList::BATTLE_SCENE_ESCAPE,[&](SubjectData subject){
    auto msg = static_cast<BattleScene::EventBody*>(subject.get());
//    std::cout << "BATTLE_SCENE_ESCAPE ";
    gameStatus = GameSeaneStatus::MAP_VIEW;
  });
  observer.interface()->addListener(ObserverEventList::BATTLE_SCENE_WIN,[&](SubjectData subject){
    auto msg = static_cast<BattleScene::EventBody*>(subject.get());
    //todo 倒した敵情報をsharedで取得し、削除する。mapSeaneが削除する。
//    std::cout << "BATTLE_SCENE_WIN ";
    gameStatus = GameSeaneStatus::MAP_VIEW;
    if(!mapScene->eraseEnemy(msg->enemy)){
      mapScene->eraseBoss();
    }
  });
  observer.interface()->addListener(ObserverEventList::BATTLE_SCENE_LOSE,[&](SubjectData subject){
    auto msg = static_cast<BattleScene::EventBody*>(subject.get());
//    std::cout << "BATTLE_SCENE_LOSE ";
    gameStatus = GameSeaneStatus::GAME_OVER;
  });

  observer.interface()->addListener(ObserverEventList::MAP_SCENE__SELECT_WARP_START,[&](SubjectData subject){
//    std::cout << "MAP_SCENE__SELECT_WARP_START ";
    if(gameInformation.getInfo().mapLevel == 1){
      log.emplace_back("これ以上もどれません");
      return;
    }
    gameInformation.getInfo().mapLevel = gameInformation.getInfo().mapLevel-1;
    gameInformation.getInfo().exp = player->parameter.EXP;
    gameInformation.save();
    log.push_back("セーブが完了しました");
    mapScene->makeDungeon(gameInformation.getInfo().mapLevel);
    auto pos = mapScene->getRandomNonePosition();
    player->set(pos);
    mapScene->setPlayer(player,true);
    if(gameInformation.getInfo().mapClearStatus >= gameInformation.getInfo().mapLevel){
      mapScene->eraseBoss();
    }
  });
  observer.interface()->addListener(ObserverEventList::MAP_SCENE__SELECT_WARP_GOAL,[&](SubjectData subject){
//    std::cout << "MAP_SCENE__SELECT_WARP_GOAL ";
    gameInformation.getInfo().mapClearStatus = gameInformation.getInfo().mapLevel = gameInformation.getInfo().mapLevel+1;
    gameInformation.getInfo().exp = player->parameter.EXP;
    gameInformation.save();
    log.push_back("セーブが完了しました");
    mapScene->makeDungeon(gameInformation.getInfo().mapLevel);
    auto pos = mapScene->getRandomNonePosition();
    player->set(pos);
    mapScene->setPlayer(player,false);
    if(gameInformation.getInfo().mapClearStatus > gameInformation.getInfo().mapLevel){
      mapScene->eraseBoss();
    }
    if(gameInformation.getInfo().mapLevel == MapInformation::getMapInfoList().size()){
      log.emplace_back("ゲームクリア");
      return;
    }
  });

  titleScene->addObserver(observer);

  keyBoardController.addObserver(observer);
  keyBoardController.startInputMonitoring();

  battleScene->addObserver(observer);
  mapScene->addObserver(observer);
  Vector2 pos = Vector2::NONE;


  printf("\033[;H\033[2J");
  gameScene->view();
  for(int i=0;gameStatus != GameSeaneStatus::GAME_OVER;i++) {
    //    system("clear");

//    std::cout << "gameStatus " << gameStatus.log() << std::endl;
    while (1) { /* キーが押されるまで待つ */
      if (gameStatus.keyBoardWait != KeyBoardWait::WAIT) {
        break;
      }
      std::this_thread::yield();
    }
    if(prevGameStatus != gameStatus){
      prevGameStatus = gameStatus;
      log.clear();
//      log.push_back("status check");
      continue;
    }

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
      gameStatus = GameSeaneStatus::GAME_OVER;
    }
    key = Key::NONE;
    gameStatus.keyBoardWait = KeyBoardWait::WAIT;
    printf("\033[;H\033[2J");

    if (gameStatus == GameSeaneStatus::TITLE) {
      gameScene = titleScene;
    } else if (gameStatus == GameSeaneStatus::MAP_VIEW) {
      gameScene = mapScene;
    } else if (gameStatus == GameSeaneStatus::BATTLE) {
      gameScene = battleScene;
    } else if (gameStatus == GameSeaneStatus::GAME_OVER) {
      break;
    }
    gameScene->update();
    gameScene->view();


    for (auto i : log) {
      std::cout << i << std::endl;
    }
    log.clear();
  }
  std::cout << "ゲーム終了" << std::endl;
  keyBoardController.stopInputMonitoring();//スレッド終了
}