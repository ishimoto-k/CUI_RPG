//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_USERCONTROLLERINTERFACE_HPP
#define APPEAL_USERCONTROLLERINTERFACE_HPP

#include <iostream>
#include <Observer.hpp>
#include <unistd.h>
using namespace Design;

//enum inputType{
//  NORMAL_CONTROLLER,
//  SCRIPT,
//};
class Key{
public:
  enum Kind{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SELECT,
    CANCEL,
    ESC,
  };
  Key(Kind k){
    kind = k;
  }
  Key(char rawKey){
    switch (rawKey){
    case 'w':
      kind = UP;
      break;
    case 'a':
      kind = LEFT;
      break;
    case 's':
      kind = DOWN;
      break;
    case 'd':
      kind = RIGHT;
      break;
    case 'z':
      kind = SELECT;
      break;
    case 'x':
      kind = CANCEL;
      break;
    case 27:
      kind = ESC;
      break;
    }
  }
  std::string debug(){
    switch (kind){
    case NONE:
      return "NONE";
    case UP:
      return "UP";
    case DOWN:
      return "DOWN";
    case LEFT:
      return "LEFT";
    case RIGHT:
      return "RIGHT";
    case SELECT:
      return "SELECT";
    case CANCEL:
      return "CANCEL";
    case ESC:
      return "ESC";
    }
  }
  Kind kind = NONE;
  bool operator == (Kind k){ return kind == k;}
};
class UserControllerInterface:public Subject{
public:
  class EventBody:public SubjectDataBody{
  public:
    Key key = Key::NONE;
  };
  virtual void startInputMonitoring() = 0;
  virtual void stopInputMonitoring() = 0;
};


#endif // APPEAL_USERCONTROLLERINTERFACE_HPP
