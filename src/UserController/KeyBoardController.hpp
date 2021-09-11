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
public:
  KeyBoardController(){
  }
  int getCharactor();
  void startInputMonitoring() override;
  static int getKey();
  static bool checkInputKey();
  void stopInputMonitoring() override;
  virtual ~KeyBoardController();
};

#endif // APPEAL_KEYBOARDCONTROLLER_HPP
