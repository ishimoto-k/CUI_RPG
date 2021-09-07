//
// Created by IshimotoKiko on 2021/09/04.
//

#ifndef APPEAL_PLAYER_HPP
#define APPEAL_PLAYER_HPP

#include <MapObjectInterface.hpp>
#include <Character.hpp>
#include <iostream>
#include <Fire.hpp>

class Player :public MapObjectInterface,public Character{
public:
  Player(int x,int y):MapObjectInterface(x,y){
    isEnemy = false;
    parameter.level = 1;
    parameter.HP = parameter.maxHP = 100;
    parameter.MP = parameter.maxMP = 100;
    parameter.DEX = 100;
    parameter.POW = 100;

    skill = std::vector<std::shared_ptr<CommandInterface>>{
        std::make_shared<Fire>(),
        std::make_shared<Ice>()
          };
  }
  std::string name(){
    return "冒険者";
  }
  void view() override;
  void move(const BitMap& bitMap) override;
  void move(const BitMap& bitMap,const Vector2& direction) override;

};
#endif // APPEAL_PLAYER_HPP
