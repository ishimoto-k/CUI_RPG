//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_FIRE_HPP
#define APPEAL_FIRE_HPP
#include "SkillInterface.hpp"

class Fire : public SkillInterface{
  std::string name(){
    return "炎";
  };
  std::string description(){
    return "敵に50の火属性ダメージ";
  };
  void select(){
    std::cout<<"敵に50の火属性ダメージ"<<std::endl;
  };
};

#endif // APPEAL_FIRE_HPP
