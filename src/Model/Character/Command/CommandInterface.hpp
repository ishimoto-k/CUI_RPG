//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_COMMANDINTERFACE_HPP
#define APPEAL_COMMANDINTERFACE_HPP
#include <iostream>
//#include <Character.hpp>
class CommandInterface{
public:
  virtual int id() = 0;
  virtual int mp() { return 0;}
  virtual std::string name() = 0;
  virtual std::string description() = 0;
  virtual std::string battleLog(){};
  virtual void select() = 0;
//  virtual void update(Parameter& from,Parameter& to){};
};
typedef CommandInterface SkillInterface;

#endif // APPEAL_COMMANDINTERFACE_HPP
