//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_KEYBOARDCONTROLLER_HPP
#define APPEAL_KEYBOARDCONTROLLER_HPP
#include "UserControllerInterface.hpp"
#include <fcntl.h>
#include <map>
#include <termios.h>
#include <thread>

class KeyBoardController : public UserControllerInterface{
  std::thread inputThread;
  bool running = false;
  termios oldt;
public:
  KeyBoardController(){
    tcgetattr(STDIN_FILENO, &oldt);
  }
  int getCharactor(); //キー入力された値を取得
  void startInputMonitoring() override;
  static bool checkInputKey(); //キー入力チェック
  void stopInputMonitoring() override;
  virtual ~KeyBoardController();
};

#endif // APPEAL_KEYBOARDCONTROLLER_HPP
