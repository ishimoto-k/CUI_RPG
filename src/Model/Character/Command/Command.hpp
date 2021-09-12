//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_COMMAND_HPP
#define APPEAL_COMMAND_HPP
#include <random>
#include "CommandInterface.hpp"

class Attack :public CommandInterface{
  int id()override {return 1;}
  std::string name()override ;
  std::string description()override ;
  void update(std::string fromName,std::string toName,Parameter& from,Parameter& to,std::vector<std::string>* log)override ;
};

class Escape:public CommandInterface{
  int id()override {return 3;}
  std::string name()override ;
  std::string description()override ;
};
class Skill:public CommandInterface{
  int id()override {return 2;}
  std::string name() override ;
  std::string description()override ;
};

#endif // APPEAL_COMMAND_HPP
