//
// Created by IshimotoKiko on 2021/09/04.
//

#ifndef APPEAL_PLAYER_HPP
#define APPEAL_PLAYER_HPP

#include <Character.hpp>
#include <MapObjectInterface.hpp>
#include <Skills.hpp>
#include <iostream>

class Player :public MapObjectInterface,public Character{
  std::vector<Parameter> levelList;
public:
  Player(int x,int y):MapObjectInterface(x,y) {
    isEnemy = false;
    parameter.level = 4;
    parameter.HP = parameter.maxHP = 100;
    parameter.MP = parameter.maxMP = 8;
    parameter.DEX = 100;
    parameter.POW = 100;
    parameter.EXP = 0;

    skill = std::vector<std::shared_ptr<CommandInterface>>{
        std::make_shared<SlashMiddle>(),
        std::make_shared<SlashLarge>(),
        std::make_shared<Heal>(),
    };
  }
  std::string name(){
    return "冒険者";
  }
  void view() override;
  void move(const BitMap& bitMap) override;
  void move(const BitMap& bitMap,const Vector2& direction) override;
  bool addExp(int exp) override {
    parameter.EXP += exp;
    if(parameter.EXP > Parameter::getEventList()[parameter.level].targetEXP){
      auto tmp =  parameter.EXP;
      parameter = Parameter::getEventList()[parameter.level+1];
      parameter.EXP = tmp;
      return true;
    }
    return false;
  }
};
#endif // APPEAL_PLAYER_HPP
