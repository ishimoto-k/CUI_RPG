//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_CHARACTER_HPP
#define APPEAL_CHARACTER_HPP
#include "Command/CommandInterface.hpp"
#include "Parameter.hpp"
#include <Status/StatusCreate.hpp>
#include <Skill/SkillsCreate.hpp>

class Character {
public:
  Parameter parameter;
  virtual std::string frontView(){ return "";}
  virtual std::string name() = 0;
  std::vector<std::shared_ptr<SkillInterface>> skill;
  std::vector<std::shared_ptr<StatusInterface>> status;
  virtual void initBattleBefore(){};
  virtual bool addExp(int exp){return false;};
  virtual void battleTurnStart(std::shared_ptr<Character> toChara,std::vector<std::string> &log){
    std::sort(parameter.status.begin(), parameter.status.end());
    parameter.status.erase(std::unique(parameter.status.begin(), parameter.status.end()), parameter.status.end());
    for(auto st : parameter.status){
      auto createSt = StatusCreate::createStatus(st);
      auto ans = std::find_if(status.begin(),status.end(),[createSt](std::shared_ptr<StatusInterface> st_){
        return st_->id() == createSt->id();
      });
      if(ans == status.end()){
        status.push_back(createSt);
      }
    }
    for(auto st: status){
      st->update(name(), toChara->name(), parameter, toChara->parameter, &log);
    }
    return;
  }
};

#endif // APPEAL_CHARACTER_HPP
