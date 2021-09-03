//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_DUMMYENEMY_HPP
#define APPEAL_DUMMYENEMY_HPP

#include <iostream>

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
};

#endif // APPEAL_DUMMYENEMY_HPP
