//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_ENEMY_HPP
#define APPEAL_ENEMY_HPP

#include <MapObjectInterface.hpp>
#include <Character.hpp>
#include <iostream>

class Enemy :public MapObjectInterface,public Character{
public:
  Enemy(int x,int y):MapObjectInterface(x,y){}
  void view() override;
  std::string name(){
    return "敵";
  }
  void move(const BitMap& bitMap) override;
  void move(const BitMap& bitMap,const Vector2& vecctor) override {};
  std::string frontView() override {
    return "　　人　　\n"
           "　／　＼　\n"
           "［・；・］\n"
           "　＼＿／　\n"
           "　　　　　";
  }
};
#endif // APPEAL_ENEMY_HPP
