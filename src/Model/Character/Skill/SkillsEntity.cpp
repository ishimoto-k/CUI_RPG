//
// Created by IshimotoKiko on 2021/09/05.
//
#include <random>
#include "../Command/Command.hpp"
#include "SkillsCreate.hpp"


#define MAKE_SKILL(classname,mp_,skillName_,desc_) \
class classname : public SkillInterface{ \
public: \
  int mp() override { return mp_;} \
  int id() override { return 4;} \
  std::string name() override { return skillName_;} \
  std::string description() override {return desc_;} \
  void update(std::string fromName,std::string toName,Parameter& from,Parameter& to,std::vector<std::string>* log) override; \
}; \
void classname::update(std::string fromName,std::string toName,Parameter& from,Parameter& to,std::vector<std::string>* log)


#define CHECK_AND_CREATE_RETURN(name)   \
if (logicName == name::logicName()) {\
 return std::make_shared<name>(paramater,skillIds);\
}

int CommandInterface::damageCalc(float level, float pow,float dex) {
  std::random_device seed_gen;
  std::default_random_engine engine(seed_gen());
  std::uniform_real_distribution<> rand(0.9, 1.1);
  auto p = pow/(1+dex*1.5);
  std::cout << pow << " " << dex << " " << (1+dex*1.5) << " " << p << std::endl;
  auto d = p * rand(engine);
  if(d <= 0)
    return 1;
  return d;
}

MAKE_SKILL(SlashMiddle,8,"大斬り","敵に中ダメージ"){
  int damage = damageCalc(from.level,1.5*from.POW ,to.DEX);
  to.HP -= damage;
  log->push_back(fromName+"の"+name());
  log->push_back(toName+"に"+std::to_string(damage)+"のダメージ");
}

MAKE_SKILL(SlashLarge,10,"渾身斬り","敵に大ダメージ"){
  int damage = damageCalc(from.level,2*from.POW ,to.DEX);
  to.HP -= damage;
  from.MP -= mp();
  std::stringstream ss;
  ss << fromName << "は" << name() << "を放った。";
  log->push_back(ss.str());
  log->push_back(toName+"に"+std::to_string(damage)+"のダメージ");
}

MAKE_SKILL(Heal,5,"ヒール","自身を回復"){
  int heal = from.DEX/1.3;
  from.HP += heal;
  if(from.HP >= from.maxHP)from.HP = from.maxHP;
  from.MP -= mp();
  log->push_back(fromName+"の"+name());
  log->push_back(fromName+"に"+std::to_string(heal)+"の回復");
}

std::shared_ptr<CommandInterface> SkillsCreate::createCommand(TypeOfSkills skill) {
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
};