//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_ESCAPE_HPP
#define APPEAL_ESCAPE_HPP
#include "CommandInterface.hpp"

class Escape:public CommandInterface{
  int id(){return 3;}
  std::string name(){
    return "逃げる";
  };
  std::string description(){
    return "戦闘から離脱します";
  };
};
class Skill:public CommandInterface{
  int id(){return 2;}
  std::string name(){
    return "スキル";
  };
  std::string description(){
    return "スキルを使用します";
  };
};

#endif // APPEAL_SKEILLSELECT_HPP
