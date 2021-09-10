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
  Player(int x,int y,int level):MapObjectInterface(x,y) {
    auto p = Parameter::loadFromLevel(level);
    parameter = p;
    parameter.EXP = 0;

    skill = std::vector<std::shared_ptr<CommandInterface>>{
        std::make_shared<SlashMiddle>(),
        std::make_shared<SlashLarge>(),
        std::make_shared<Heal>(),
    };
  }
  std::string name() override {
    return "冒険者";
  }
  void view() override;
  bool move(const BitMap& bitMap,std::function<void(BitMapKind,Vector2,Vector2)> callback) override;
  bool move(const BitMap& bitMap,const Vector2& direction,std::function<void(BitMapKind,Vector2,Vector2)> callback) override;
  bool addExp(int exp) override {
    parameter.EXP += exp;
//    std::cout << "EXP:" <<  parameter.EXP << " targetExp:" << Parameter::loadFromLevel(parameter.level).targetEXP << std::endl;
    if(parameter.EXP > Parameter::loadFromLevel(parameter.level).targetEXP){
      auto tmp =  parameter.EXP;
      parameter = Parameter::loadFromLevel(parameter.level+1);
      parameter.EXP = tmp;
      return true;
    }
    return false;
  }
};
#endif // APPEAL_PLAYER_HPP
