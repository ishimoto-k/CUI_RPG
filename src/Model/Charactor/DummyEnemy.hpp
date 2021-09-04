//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_DUMMYENEMY_HPP
#define APPEAL_DUMMYENEMY_HPP

#include <iostream>
#include <Vector2.hpp>
using namespace Vec;

class DummyEnemy {
  Vector2 position_ = Vector2(0,0);
  int id_;

public:
  DummyEnemy(int x,int y):position_(Vector2(x,y)){}
  void view(){
    std::cout << "敵";
  }
  int id(){
    return id_;
  }
  void move(const BitMap bitMap){
    auto directions = ShuffulDirections();
    for(auto i:directions){
      auto dir = position_ + i;
      if(at(bitMap,dir) == 0){
        position_ = dir;
        break;
      }
    }
  }
  Vector2 position(){
    return position_;
  }
};

#endif // APPEAL_DUMMYENEMY_HPP
