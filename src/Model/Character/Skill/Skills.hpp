//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_SKILLS_HPP
#define APPEAL_SKILLS_HPP
#include "../Command/CommandInterface.hpp"
#include <sstream>

class SlashMiddle : public SkillInterface{
  int mp() override { return 8;}
  int id() override { return 4;}
  std::string name() override {
    return "大斬り";
  };
  std::string description() override {
    return "敵に中ダメージ";
  };
  void update(std::string fromName,std::string toName,Parameter& from,Parameter& to,std::vector<std::string>* log) override {
    int damage = 1.5*from.POW - to.DEX;
    to.HP -= damage;
    log->push_back(fromName+"の"+name());
    log->push_back(toName+"に"+std::to_string(damage)+"のダメージ");
  }
};

class SlashLarge : public SkillInterface{
  int mp() override { return 10;}
  int id() override { return 4;}
  std::string name() override {
    return "渾身斬り";
  };
  std::string description()override {
    return "敵に大ダメージ";
  };
  void update(std::string fromName,std::string toName,Parameter& from,Parameter& to,std::vector<std::string>* log)override {
    int damage = 2*from.POW - to.DEX;
    to.HP -= damage;
    from.MP -= mp();
    std::stringstream ss;

    ss << fromName << "は" << name() << "を放った。";
    log->push_back(ss.str());
    log->push_back(toName+"に"+std::to_string(damage)+"のダメージ");
  }
};

class Heal : public SkillInterface{
  int mp() override { return 5;}
  int id() override { return 4;}
  std::string name()override {
    return "ヒール";
  };
  std::string description()override {
    return "自身を回復";
  };
  void update(std::string fromName,std::string toName,Parameter& from,Parameter& to,std::vector<std::string>* log)override {
    int heal = from.DEX/1.3;
    from.HP += heal;
    if(from.HP >= from.maxHP)from.HP = from.maxHP;
    from.MP -= mp();
    log->push_back(fromName+"の"+name());
    log->push_back(fromName+"に"+std::to_string(heal)+"の回復");
  }
};

#endif // APPEAL_SKILLS_HPP
