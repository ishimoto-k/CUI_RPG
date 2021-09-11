//
// Created by IshimotoKiko on 2021/09/11.
//

#ifndef APPEAL_SKILLSCREATER_HPP
#define APPEAL_SKILLSCREATER_HPP
#include "Skills.hpp"
#include "Command.hpp"

class SkillsCreate {
public:
  static std::shared_ptr<CommandInterface> createCommand(TypeOfSkills skill) {
    switch (skill){
    case TypeOfSkills::SKILL:
    case TypeOfSkills::ESCAPE:
      return nullptr;
    case TypeOfSkills::ATTACK:
      return std::make_shared<Attack>();
    case TypeOfSkills::SLASH_MIDDLE:
      return std::make_shared<SlashMiddle>();
    case TypeOfSkills::SLASH_LARGE:
      return std::make_shared<SlashLarge>();
    case TypeOfSkills::HEAL:
      return std::make_shared<Heal>();
    }
    return std::make_shared<Attack>();
  };
};
#endif // APPEAL_SKILLSCREATER_HPP
