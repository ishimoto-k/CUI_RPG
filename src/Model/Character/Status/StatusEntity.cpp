//
// Created by IshimotoKiko on 2021/09/05.
//
#include "../Command/Command.hpp"
#include "StatusCreate.hpp"
#include <random>

#define MAKE_STATUS(classname,id_,statusName) \
class classname : public StatusInterface{ \
public: \
  int id() override { return id_;} \
  std::string name() override { return statusName;} \
  void update(std::string fromName,std::string toName,Parameter& from,Parameter& to,std::vector<std::string>* log) override; \
}; \
void classname::update(std::string fromName,std::string toName,Parameter& from,Parameter& to,std::vector<std::string>* log)


#define CHECK_AND_CREATE_RETURN(name)   \
if (logicName == name::logicName()) {\
 return std::make_shared<name>(paramater,skillIds);\
}


MAKE_STATUS(NoneStatus,0,""){}

MAKE_STATUS(PowerUpStatus,1,"攻撃力アップ"){
  from.POW = float(from.maxPOW)*1.2;
//  std::cout << "攻撃力アップ" << from.POW  <<std::endl;
}

MAKE_STATUS(DefenceUpStatus,2,"守備力アップ"){
  to.DEX = from.maxDEX*1.1;
}


std::shared_ptr<StatusInterface> StatusCreate::createStatus(TypeOfStatus status) {
  switch (status){
  case TypeOfStatus::NONE :
    return std::make_shared<NoneStatus>();
  case TypeOfStatus::POWER_UP:
    return std::make_shared<PowerUpStatus>();
  case TypeOfStatus::DEFENCE_UP:
    return std::make_shared<DefenceUpStatus>();
  }

};