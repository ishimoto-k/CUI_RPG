//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_CHARACTER_HPP
#define APPEAL_CHARACTER_HPP
#include "Command/CommandInterface.hpp"
#include "Parameter.hpp"

class Character {
public:
  Parameter parameter;
  virtual std::string frontView(){ return "";}
  virtual std::string name() = 0;
  std::vector<std::shared_ptr<SkillInterface>> skill;
  virtual void initBattleBefore(){};
  virtual bool addExp(int exp){return false;};
};

#endif // APPEAL_CHARACTER_HPP
