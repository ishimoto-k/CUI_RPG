//
// Created by IshimotoKiko on 2021/09/05.
//
#include <random>
#include "../Command/Command.hpp"
#include "SkillsCreate.hpp"


// MAKE_STATUSはマクロで記載
// SkillInterfaceを継承したクラスを生成し、
// 容易にスキルを作成できる。

#define MAKE_SKILL(classname,id_,mp_,skillName_,desc_) \
class classname : public SkillInterface{ \
public: \
  int mp() override { return mp_;} \
  int id() override { return static_cast<int>(id_);} \
  std::string name() override { return skillName_;} \
  std::string description() override {return desc_;} \
  void update(std::string fromName,std::string toName,Parameter& from,Parameter& to,std::vector<std::string>* log) override; \
}; \
void classname::update(std::string fromName,std::string toName,Parameter& from,Parameter& to,std::vector<std::string>* log)


#define CHECK_AND_CREATE_RETURN(name)   \
if (logicName == name::logicName()) {\
 return std::make_shared<name>(paramater,skillIds);\
}

//基本ダメージ計算
//パラメータは試行錯誤
//POW-DEXのアステリオス方式を採用
//破綻しないよう、パラメータは低く設定
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
}

//基本魔法ダメージ計算
//DEXによるダメージ計算
int magicCalc(float flevel, float fdex, float todex) { //physical
  std::random_device seed_gen;
  std::default_random_engine engine(seed_gen());
  std::uniform_real_distribution<> rand(0.9, 1.3);
  float d = ((fdex*1.1+flevel/5) - (todex*1.3)) * rand(engine);
  if(d <= 0){
    return seed_gen()%2+1;
  }
  return d;
}

MAKE_SKILL(SlashMiddle, TypeOfSkills::SLASH_MIDDLE,4,"大斬り","敵に中ダメージ") {
  int damage = damageCalc(from.level, to.level, 1.2 * from.POW, to.DEX);
  to.HP -= damage;
  from.MP -= mp();
  log->push_back(fromName + "の" + name());
  log->push_back(toName + "に" + std::to_string(damage) + "のダメージ");
}
MAKE_SKILL(SlashLarge,TypeOfSkills::SLASH_LARGE, 8,"渾身斬り","敵に大ダメージ"){
  int damage = damageCalc(from.level,to.level,1.5*from.POW ,to.DEX);
  to.HP -= damage;
  from.MP -= mp();
  std::stringstream ss;
  ss << fromName << "は" << name() << "を放った。";
  log->push_back(ss.str());
  log->push_back(toName+"に"+std::to_string(damage)+"のダメージ");
}
MAKE_SKILL(Heal,TypeOfSkills::HEAL,3,"ヒール","自身を回復"){
  int heal = magicCalc(from.level,from.DEX*0.9,from.DEX) + from.maxHP*0.3;//from.DEX/1.3;
  from.HP += heal;
  if(from.HP >= from.maxHP)from.HP = from.maxHP;
  from.MP -= mp();
  log->push_back(fromName+"の"+name());
  log->push_back(fromName+"に"+std::to_string(heal)+"の回復");
}
MAKE_SKILL(HighHeal,TypeOfSkills::HIGH_HEAL,6,"ハイヒール","自身を大回復"){
  int heal = magicCalc(from.level,from.DEX*1.3,from.DEX) + from.maxHP*0.5;//from.DEX/1.3;
  from.HP += heal;
  if(from.HP >= from.maxHP)from.HP = from.maxHP;
  from.MP -= mp();
  log->push_back(fromName+"の"+name());
  log->push_back(fromName+"に"+std::to_string(heal)+"の回復");
}
MAKE_SKILL(PowerUp,TypeOfSkills::POWERUP,10,"攻撃上げ","3ターン自身の攻撃力をあげる"){
  from.MP -= mp();
  from.status.push_back(TypeOfStatus::POWER_UP);//状態異常IDをparameter.statusに追加
  log->push_back(fromName+"の"+name());
  log->push_back(fromName+"は攻撃力が上がった");
}
MAKE_SKILL(Shield,TypeOfSkills::SHIELD,0,"まもる","1ターン身を守る"){
  from.MP -= mp();
  from.DEX = from.maxDEX + 50;
  log->push_back(fromName+"は身を守った");
}
MAKE_SKILL(DefUp,TypeOfSkills::DEFENCEUP,8,"防御上げ","3ターン自身の防御力をあげる"){
  from.MP -= mp();
  from.status.push_back(TypeOfStatus::DEFENCE_UP);//状態異常IDをparameter.statusに追加
  log->push_back(fromName+"の"+name());
  log->push_back(fromName+"は防御力が上がった");
}
MAKE_SKILL(Poison,TypeOfSkills::POISON,8,"毒攻撃","相手にダメージ与えて毒にする"){
  int damage = damageCalc(from.level,to.level,1.05*from.POW ,to.DEX);
  to.HP -= damage;
  from.MP -= mp();
  std::stringstream ss;
  ss << fromName << "は" << name() << "を放った。";
  log->push_back(ss.str());
  log->push_back(toName+"に"+std::to_string(damage)+"のダメージ");
  std::random_device seed_gen;
  std::default_random_engine engine(seed_gen());
  std::uniform_real_distribution<> rand(0.0, 1.0);
  if(rand(engine) > 0.5){//50%の確率で毒を付与
    log->push_back(toName+"は毒になった");
    to.status.push_back(TypeOfStatus::POISON); //状態異常IDをparameter.statusに追加
  }
}
MAKE_SKILL(MagicMiddle,TypeOfSkills::MAGIC_MIDDLE,8,"中魔法","魔力を消費して中ダメージを与える"){
  int damage = magicCalc(from.level,from.DEX*1.6,0);
  to.HP -= damage;
  from.MP -= mp();
  std::stringstream ss;
  ss << fromName << "は" << name() << "を放った。";
  log->push_back(ss.str());
  log->push_back(toName+"に"+std::to_string(damage)+"のダメージ");
}
MAKE_SKILL(MagicHigh,TypeOfSkills::MAGIC_HIGH,10,"大魔法","魔力を消費して大ダメージを与える"){
  int damage = magicCalc(from.level*1.3,from.DEX*2.0,0);
  to.HP -= damage;
  from.MP -= mp();
  std::stringstream ss;
  ss << fromName << "は" << name() << "を放った。";
  log->push_back(ss.str());
  log->push_back(toName+"に"+std::to_string(damage)+"のダメージ");
}

std::shared_ptr<CommandInterface>
SkillsCreate::createCommand(TypeOfSkills skill) {
  //factory method
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
  case TypeOfSkills::SHIELD:
    return std::make_shared<Shield>();
  case TypeOfSkills::DEFENCEUP:
    return std::make_shared<DefUp>();
  case TypeOfSkills::POISON:
    return std::make_shared<Poison>();
  case TypeOfSkills::MAGIC_MIDDLE:
    return std::make_shared<MagicMiddle>();
  case TypeOfSkills::MAGIC_HIGH:
    return std::make_shared<MagicHigh>();
  }
};