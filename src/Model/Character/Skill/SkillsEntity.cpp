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

int CommandInterface::damageCalc(float flevel,float tolevel, float pow,float dex) { //physical
  //アステリオス方式
  std::random_device seed_gen;
  std::default_random_engine engine(seed_gen());
  std::uniform_real_distribution<> rand(0.9, 1.1);
  int d = ((pow*1.1+flevel/3) - (dex*1.2+tolevel/3)) * rand(engine);
  if(d <= 0){
    return seed_gen()%2+1;
  }
  return d;
//  float d = (1+dex*1.5*tolevel*1.2);
//  float attack = flevel*0.8*(float(pow)/d)*pow * rand(engine);
//  if(attack <= 0)
//    return seed_gen()%3+1;
//  return int(attack);
}
int magicCalc(float flevel, float fdex, float todex) { //physical
  std::random_device seed_gen;
  std::default_random_engine engine(seed_gen());
  std::uniform_real_distribution<> rand(0.9, 1.1);
  float d = ((fdex*1.1+flevel/10) - (todex*1.3)) * rand(engine);
  if(d <= 0){
    return seed_gen()%2+1;
  }
  return d;
//  float attack = ((float(fdex)/d)+fdex) * rand(engine);
//  if(attack <= 0)
//    return seed_gen()%3+1;
//  return int(attack);
}

MAKE_SKILL(SlashMiddle,8,"大斬り","敵に中ダメージ"){
  int damage = damageCalc(from.level,to.level,1.2*from.POW ,to.DEX);
  to.HP -= damage;
  from.MP -= mp();
  log->push_back(fromName+"の"+name());
  log->push_back(toName+"に"+std::to_string(damage)+"のダメージ");
}

MAKE_SKILL(SlashLarge,10,"渾身斬り","敵に大ダメージ"){
  int damage = damageCalc(from.level,to.level,1.5*from.POW ,to.DEX);
  to.HP -= damage;
  from.MP -= mp();
  std::stringstream ss;
  ss << fromName << "は" << name() << "を放った。";
  log->push_back(ss.str());
  log->push_back(toName+"に"+std::to_string(damage)+"のダメージ");
}

MAKE_SKILL(Heal,5,"ヒール","自身を回復"){
  int heal = magicCalc(from.level,from.DEX*0.8,from.DEX) + from.maxHP*0.1;//from.DEX/1.3;
  from.HP += heal;
  if(from.HP >= from.maxHP)from.HP = from.maxHP;
  from.MP -= mp();
  log->push_back(fromName+"の"+name());
  log->push_back(fromName+"に"+std::to_string(heal)+"の回復");
}
MAKE_SKILL(HighHeal,10,"ハイヒール","自身を大回復"){
  int heal = magicCalc(from.level,from.DEX*1.1,from.DEX) + from.maxHP*0.3;//from.DEX/1.3;
  from.HP += heal;
  if(from.HP >= from.maxHP)from.HP = from.maxHP;
  from.MP -= mp();
  log->push_back(fromName+"の"+name());
  log->push_back(fromName+"に"+std::to_string(heal)+"の回復");
}

MAKE_SKILL(PowerUp,10,"ちからため","自身の攻撃力をあげる"){
  from.status.push_back(TypeOfStatus::POWER_UP);
  log->push_back(fromName+"の"+name());
  log->push_back(fromName+"は攻撃力が上がった");
}

MAKE_SKILL(DefUp,0,"防御","1ターン身を守る"){
  from.DEX = from.maxDEX + 50;
  log->push_back(fromName+"は身を守った");
}


MAKE_SKILL(Poison,1,"毒攻撃","相手を毒にする"){
  to.status.push_back(TypeOfStatus::POISON);
  log->push_back(toName+"は毒になった");
}

std::shared_ptr<CommandInterface>
SkillsCreate::createCommand(TypeOfSkills skill) {
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
  case TypeOfSkills::HIGH_HEAL:
    return std::make_shared<HighHeal>();
  case TypeOfSkills::POWERUP:
    return std::make_shared<PowerUp>();
  case TypeOfSkills::DEFUP:
    return std::make_shared<DefUp>();
  case TypeOfSkills::POISON:
    return std::make_shared<Poison>();
  }
};