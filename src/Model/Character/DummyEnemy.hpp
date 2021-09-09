//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_DUMMYENEMY_HPP
#define APPEAL_DUMMYENEMY_HPP

#include "Enemy.hpp"
#include <Character.hpp>
#include <MapObjectInterface.hpp>
#include <iostream>

class DummyEnemy :public Enemy{
public:
  DummyEnemy(int x,int y):Enemy(x,y){
    parameter.level = 1;
    parameter.HP = parameter.maxHP = 100;
    parameter.MP = parameter.maxMP = 100;
    parameter.DEX = 10;
    parameter.POW = 100;
    parameter.EXP = 100;
  }
  void view() override;
  std::string name() override {
    return "敵";
  }
  bool move(const BitMap& bitMap,std::function<void(BitMapKind,Vector2,Vector2)> callback) override;
  bool move(const BitMap& bitMap,const Vector2& vector,std::function<void(BitMapKind,Vector2,Vector2)> callback) override {return false;};
  std::string frontView() override {

    return "　　人　　\n"
           "　／　＼　\n"
           "［・；・］\n"
           "　＼＿／　\n"
           "　　　　　";
  }
};

#endif // APPEAL_DUMMYENEMY_HPP
