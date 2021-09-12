//
// Created by IshimotoKiko on 2021/09/04.
//

#ifndef APPEAL_PLAYER_HPP
#define APPEAL_PLAYER_HPP

#include <Character.hpp>
#include <MapObjectInterface.hpp>
#include <iostream>

class Player :public MapObjectInterface,public Character{
  std::vector<Parameter> levelList;
  std::vector<std::shared_ptr<SkillInterface>> gotSkills;
public:
  Player(int x,int y,int exp):MapObjectInterface(x,y) {
    auto p = Parameter::loadFromExp(exp);
    parameter = p;
    auto skillIds = Parameter::loadSkillFromLevel(p.level);
    for(auto id:skillIds){
      auto s = SkillsCreate::createCommand(static_cast<TypeOfSkills>(id));
      skill.push_back(s);
    }
  }
  std::string name() override {
    return "冒険者";
  }
  void view() override;
  std::vector<std::shared_ptr<SkillInterface>> getGotSkills(){
    return gotSkills;
  }
  bool move(const BitMap& bitMap,std::function<void(BitMapKind,Vector2,Vector2)> callback) override;
  bool move(const BitMap& bitMap,const Vector2& direction,std::function<void(BitMapKind,Vector2,Vector2)> callback) override;
  bool addExp(int exp) override {
    parameter.EXP += exp;
//    std::cout << "EXP:" <<  parameter.EXP << " targetExp:" << Parameter::loadFromLevel(parameter.level).targetEXP << std::endl;
    if(parameter.EXP > Parameter::loadFromLevel(parameter.level).targetEXP){
      auto tmp =  parameter.EXP;
      parameter = Parameter::loadFromLevel(parameter.level+1);
      gotSkills.clear();
      for(auto id:parameter.skillIds){
        auto s = SkillsCreate::createCommand(static_cast<TypeOfSkills>(id));
        skill.push_back(s);
        gotSkills.push_back(s);
      }
      std::sort(skill.begin(), skill.end());
      skill.erase(std::unique(skill.begin(), skill.end()), skill.end());
      parameter.EXP = tmp;
      return true;
    }
    return false;
  }
  void initBattleBefore() override {
    parameter.HP = parameter.maxHP;
    parameter.MP = parameter.maxMP;
    parameter.POW = parameter.maxPOW;
    parameter.DEX = parameter.maxDEX;
    std::cout << " power "<<parameter.maxPOW << std::endl;
  }
};
#endif // APPEAL_PLAYER_HPP
