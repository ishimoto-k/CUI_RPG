//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_ATTACK_HPP
#define APPEAL_ATTACK_HPP
#include "CommandInterface.hpp"
class Attack :public CommandInterface{
  std::string name(){
    return "攻撃";
  };
  std::string description(){
    return "敵に物理攻撃をします";
  };
  void select(){
    std::cout<<"攻撃します"<<std::endl;
  };
};

#endif // APPEAL_ATTACK_HPP
