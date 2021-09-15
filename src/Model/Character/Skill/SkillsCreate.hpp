//
// Created by IshimotoKiko on 2021/09/11.
//

#ifndef APPEAL_SKILLSCREATER_HPP
#define APPEAL_SKILLSCREATER_HPP

//スキルの種類
enum class TypeOfSkills : int{
  SKILL = 100,
  ESCAPE,
  ATTACK = 1,
  SHIELD = 2,
  SLASH_MIDDLE = 3,
  SLASH_LARGE = 4,
  HEAL = 5,
  HIGH_HEAL = 6,
  POWERUP = 7,
  DEFENCEUP = 8,
  POISON = 9,
  MAGIC_MIDDLE = 10,
  MAGIC_HIGH = 11,
};

//ID使ってスキルを生成する
class SkillsCreate {
public:
  static std::shared_ptr<CommandInterface> createCommand(TypeOfSkills skill);
};
#endif // APPEAL_SKILLSCREATER_HPP
