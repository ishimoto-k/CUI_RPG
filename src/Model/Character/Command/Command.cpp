//
// Created by IshimotoKiko on 2021/09/05.
//

#include "Command.hpp"

std::string Attack::name(){
  return "攻撃";
};
std::string Attack::description(){
  return "敵に攻撃します";
};
void Attack::update(std::string fromName,std::string toName,Parameter& from,Parameter& to,std::vector<std::string>* log){
  int damage = from.POW - to.DEX;
  to.HP -= damage;
  log->push_back(fromName+"の"+name());
  log->push_back(toName+"に"+std::to_string(damage)+"のダメージ");
}

std::string Escape::name(){
  return "逃げる";
}
std::string Escape::description(){
  return "戦闘から離脱します";
}

std::string Skill::name(){
  return "スキル";
}
std::string Skill::description(){
  return "スキルを使用します";
}

