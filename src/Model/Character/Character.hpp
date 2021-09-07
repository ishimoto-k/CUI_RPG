//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_CHARACTER_HPP
#define APPEAL_CHARACTER_HPP
#include <Command/CommandInterface.hpp>

struct Parameter {
  std::string name;
  int level;
  int POW;
  int DEX;
  int maxHP;
  int maxMP;
};
class Character {
public:
  Parameter parameter;
  virtual std::string frontView(){}
  virtual std::string name() = 0;
  bool isEnemy;
  int HP;
  int MP;
  std::vector<std::shared_ptr<SkillInterface>> skill;
  virtual void action(){};
};

#endif // APPEAL_CHARACTER_HPP
