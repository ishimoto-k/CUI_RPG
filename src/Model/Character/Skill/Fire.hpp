//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_FIRE_HPP
#define APPEAL_FIRE_HPP
#include "../Command/CommandInterface.hpp"

class Fire : public SkillInterface{
  int mp() override { return 5;}
  int id() override { return 4;}
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

class Ice : public SkillInterface{
  int mp() override { return 5;}
  int id() override { return 4;}
  std::string name(){
    return "氷";
  };
  std::string description(){
    return "敵に50の氷属性ダメージ";
  };
  void select(){
    std::cout<<"敵に50の氷属性ダメージ"<<std::endl;
  };
};

#endif // APPEAL_FIRE_HPP
