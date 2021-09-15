//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_COMMANDINTERFACE_HPP
#define APPEAL_COMMANDINTERFACE_HPP
#include <iostream>
#include <vector>
#include "../Parameter.hpp"
class CommandInterface{
public:
  static int damageCalc(float p_level,float e_level, float pow,float dex);//ダメージ計算
  virtual int id() = 0;//コマンド・スキルのID
  virtual int mp() { return 0;}//消費MP
  virtual std::string name() = 0;//コマンド・スキル名
  virtual std::string description() = 0;//コマンド・スキルの説明
  virtual void update(std::string fromName,std::string toName,Parameter& from,Parameter& to,std::vector<std::string>* log){};//コマンド・スキルの実行
};
typedef CommandInterface SkillInterface;
//CommandInterface = SkillInterface

#endif // APPEAL_COMMANDINTERFACE_HPP
