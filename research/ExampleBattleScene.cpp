//
// Created by IshimotoKiko on 2021/09/05.
//

#include <BattleScene.hpp>
#include <KeyBoardController.hpp>
#include <fstream>
#include <iostream>

int main(){

  fprintf(stdout,"現在のファイルパス:%s\n", CURRENT_DIRECTORY);


  BattleScene battleScene;
  Observer observer;
  observer.interface(std::make_shared<ObserverInterface>());
  battleScene.view();
  for(int i=0;i<100;i++) {
    printf("\033[;H\033[2J");
    battleScene.view();
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
    if (key == 'w') {
    } else if (key == 's') {
    } else if (key == 'd') {
    } else if (key == 'a') {
    } else if (key == 0) {
    }
  }
}