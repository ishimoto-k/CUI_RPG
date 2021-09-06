//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_COMMANDINTERFACE_HPP
#define APPEAL_COMMANDINTERFACE_HPP
#include <iostream>
class CommandInterface{
public:
  virtual std::string name() = 0;
  virtual std::string description() = 0;
  virtual void select() = 0;
};


#endif // APPEAL_COMMANDINTERFACE_HPP
