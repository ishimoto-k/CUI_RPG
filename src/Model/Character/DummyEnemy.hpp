//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_DUMMYENEMY_HPP
#define APPEAL_DUMMYENEMY_HPP

#include <MapObjectInterface.hpp>
#include <Character.hpp>
#include <iostream>

class DummyEnemy :public MapObjectInterface,public Character{
public:
  DummyEnemy(int x,int y):MapObjectInterface(x,y){
    parameter.level = 1;
    parameter.HP = parameter.maxHP = 100;
    parameter.MP = parameter.maxMP = 100;
    parameter.DEX = 10;
    parameter.POW = 100;
    parameter.EXP = 100;
  }
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

#endif // APPEAL_DUMMYENEMY_HPP
