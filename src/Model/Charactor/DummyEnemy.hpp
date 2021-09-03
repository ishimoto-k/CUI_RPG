//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_DUMMYENEMY_HPP
#define APPEAL_DUMMYENEMY_HPP

#include <iostream>
#include <Vector2.hpp>
using namespace Vec;

class DummyEnemy {
  int x_;
  int y_;
  int id_;

public:
  DummyEnemy(int x,int y):x_(x),y_(y){};
  void view(){
    std::cout << "D";
  }
  int id(){
    return id_;
  }
  void move(){

  }
  Vector2 position(){
    Vector2 vector2 = Vector2(x_,y_);
    return vector2;
  }
};

#endif // APPEAL_DUMMYENEMY_HPP
