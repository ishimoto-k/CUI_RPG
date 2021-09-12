//
// Created by IshimotoKiko on 2021/09/12.
//

#ifndef APPEAL_STATUSINTERFACE_HPP
#define APPEAL_STATUSINTERFACE_HPP
#include "../Parameter.hpp"

class StatusInterface{
protected:
  bool active_ = true;
public:
  bool getActive(){ return active_;}
  virtual int id() = 0;
  virtual std::string name() = 0;
  virtual void update(std::string fromName,std::string toName,Parameter& from,Parameter& to,std::vector<std::string>* log){};
};

#endif // APPEAL_STATUSINTERFACE_HPP
