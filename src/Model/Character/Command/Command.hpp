//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_COMMAND_HPP
#define APPEAL_COMMAND_HPP
#include <random>
#include "CommandInterface.hpp"
#include "../Skill/SkillsCreate.hpp"
//コマンド　「攻撃」
class Attack :public CommandInterface{
  int id()override {return static_cast<int>(TypeOfSkills::ATTACK);}
  std::string name()override ;
  std::string description()override ;
  void update(std::string fromName,std::string toName,Parameter& from,Parameter& to,std::vector<std::string>* log)override ;
};

//コマンド　「逃げる」
class Escape:public CommandInterface{
  int id()override {return static_cast<int>(TypeOfSkills::ESCAPE);}
  std::string name()override ;
  std::string description()override ;
};
//コマンド　「スキル」
class Skill:public CommandInterface{
  int id()override {return static_cast<int>(TypeOfSkills::SKILL);}
  std::string name() override ;
  std::string description()override ;
};

#endif // APPEAL_COMMAND_HPP
