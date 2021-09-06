//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_CHARACTER_HPP
#define APPEAL_CHARACTER_HPP
#include <SkillInterface.hpp>

class Character {
public:
  std::string name;
  bool isEnemy=false;
  int level;
  int HP;
  int MP;
  int POW;
  int DEX;
  std::vector<SkillInterface> skill;
};

#endif // APPEAL_CHARACTER_HPP
