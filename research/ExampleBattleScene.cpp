//
// Created by IshimotoKiko on 2021/09/05.
//

#include <BattleScene.hpp>
#include <DummyEnemy.hpp>
#include <KeyBoardController.hpp>
#include <Player.hpp>
#include <fstream>
#include <iostream>

int main(){
  enum GameState{
    BATTLE,
    EXIT,
  };
  GameState gameState = BATTLE;
  BattleScene battleScene;
  Observer observer;
  observer.interface(std::make_shared<ObserverInterface>());

  observer.interface()->addListener(ObserverEventList::BATTLE_SCENE_ESCAPE,[&](SubjectData subject){
    auto msg = static_cast<BattleScene::EventBody*>(subject.get());
    std::cout << "BATTLE_SCENE_ESCAPE ";
    gameState = EXIT;
  });
  observer.interface()->addListener(ObserverEventList::BATTLE_SCENE_WIN,[&](SubjectData subject){
    auto msg = static_cast<BattleScene::EventBody*>(subject.get());
    std::cout << "BATTLE_SCENE_WIN ";
    gameState = EXIT;
  });
  observer.interface()->addListener(ObserverEventList::BATTLE_SCENE_LOSE,[&](SubjectData subject){
    auto msg = static_cast<BattleScene::EventBody*>(subject.get());
    std::cout << "BATTLE_SCENE_LOSE ";
    gameState = EXIT;
  });
  battleScene.addObserver(observer);
  battleScene.setPlayer(std::make_shared<Player>(10,10));
  battleScene.setEnemy(Enemy::getEnemyList()[0]);
  battleScene.view();
  for(int i=0;i<100;i++) {
    printf("\033[;H\033[2J");
    int key = 0;
    int counter = 0;
    battleScene.update();
    battleScene.view();
    if(EXIT == gameState){
      goto finish;
    }
    while (1) { /* キーが押されるまで待つ */
      std::this_thread::sleep_for(std::chrono::milliseconds(16));
      if (KeyBoardController::checkInputKey()) {
        key = getchar(); /* 入力されたキー番号 */
        break;
      }
    }
    if (key == 'w') {
      battleScene.cursorUp();
    } else if (key == 's') {
      battleScene.cursorDown();
    } else if (key == 'd') {
    } else if (key == 'a') {
    } else if (key == 'z') {
      battleScene.select();
    } else if (key == 'x') {
      battleScene.cancel();
    } else if (key == 0) {
    }
  }
  finish:
  std::cout << "Exit" << std::endl;
}