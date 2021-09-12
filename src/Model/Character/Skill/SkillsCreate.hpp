//
// Created by IshimotoKiko on 2021/09/11.
//

#ifndef APPEAL_SKILLSCREATER_HPP
#define APPEAL_SKILLSCREATER_HPP

enum class TypeOfSkills : int{
  SKILL = 100,
  ESCAPE,
  ATTACK = 1,
  SLASH_MIDDLE,
  SLASH_LARGE,
  HEAL,
};

class SkillsCreate {
public:
  static std::shared_ptr<CommandInterface> createCommand(TypeOfSkills skill);
};
#endif // APPEAL_SKILLSCREATER_HPP
