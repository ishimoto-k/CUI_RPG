//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_ATTACK_HPP
#define APPEAL_ATTACK_HPP
#include "CommandInterface.hpp"
class Attack :public CommandInterface{
  int id(){return 1;}
  std::string name(){
    return "攻撃";
  };
  std::string description(){
    return "敵に物理攻撃をします";
  };
  void select(){
    std::cout<<"攻撃します"<<std::endl;
  };
  void update(std::string fromName,std::string toName,Parameter& from,Parameter& to,std::vector<std::string>* log){
    int damage = from.POW - to.DEX;
    to.HP -= damage;
    log->push_back(fromName+"の"+name());
    log->push_back(toName+"に"+std::to_string(damage)+"のダメージ");
  }
};

#endif // APPEAL_ATTACK_HPP
