//
// Created by IshimotoKiko on 2021/09/05.
//
#include "../Command/Command.hpp"
#include "StatusCreate.hpp"
#include <random>

#define MAKE_STATUS(classname,id_,statusName,turn_) \
class classname : public StatusInterface{              \
public: \
  int id() override { return static_cast<int>(id_);}                     \
  int turn = turn_+1;\
  bool check(){return turn <= 0;}\
  std::string name() override { return statusName;} \
  bool update(std::string fromName,std::string toName,Parameter& from,Parameter& to,std::vector<std::string>* log) override; \
}; \
bool classname::update(std::string fromName,std::string toName,Parameter& from,Parameter& to,std::vector<std::string>* log)



#define CHECK_AND_CREATE_RETURN(name)   \
if (logicName == name::logicName()) {\
 return std::make_shared<name>(paramater,skillIds);\
}


MAKE_STATUS(NoneStatus, TypeOfStatus::NONE,"",0){
  return true;
}

MAKE_STATUS(PowerUpStatus,TypeOfStatus::POWER_UP,"攻撃力アップ",3){
  turn--;
  if(check()){
    if(turn == 0){
      log->push_back("攻撃力が元に戻った");
    }
    return true;
  }
  from.POW = float(from.POW)*1.5;
  return false;
}

MAKE_STATUS(DefenceUpStatus,TypeOfStatus::DEFENCE_UP,"守備力アップ",3){
  turn--;
  if(check()){
    if(turn == 0){
      log->push_back("守備力が元に戻った");
    }
    return true;
  }
  from.DEX = from.DEX*1.1;
  return false;
}


MAKE_STATUS(PoisonStatus,TypeOfStatus::POISON,"毒状態",5){
  turn--;
  if(check()){
    if(turn == 0){
      log->push_back("毒が治った");
    }
    return true;
  }
  int damage = to.maxPOW/3;
  from.HP = from.HP - damage;
  log->push_back(fromName+"は毒で" + std::to_string(damage) +"ダメージ食らった");
  std::cout << "毒" << turn << std::endl;
  return false;
}


std::shared_ptr<StatusInterface> StatusCreate::createStatus(TypeOfStatus status) {
  switch (status){
  case TypeOfStatus::NONE :
    return std::make_shared<NoneStatus>();
  case TypeOfStatus::POWER_UP:
    return std::make_shared<PowerUpStatus>();
  case TypeOfStatus::DEFENCE_UP:
    return std::make_shared<DefenceUpStatus>();
  case TypeOfStatus::POISON:
    return std::make_shared<PoisonStatus>();
  }
}