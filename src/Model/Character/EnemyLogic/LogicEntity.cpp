//
// Created by IshimotoKiko on 2021/09/11.
//
#include "EnemyLogicInterface.hpp"
#include <SkillsCreate.hpp>
#include <random>

// MAKE_STATUSはマクロで記載
// EnemyLogicInterfaceを継承したクラスを生成し、
// 容易にエネミーの戦闘ロジックを作成できる。
#define MAKE_LOGIC(name) \
class name : public EnemyLogicInterface{ \
public: \
  name(std::vector<int> parameter,std::vector<int> skillIds):EnemyLogicInterface(parameter,skillIds){}; \
  std::shared_ptr<CommandInterface> execute(Parameter self,Parameter other)override; \
}; \
std::shared_ptr<CommandInterface> name::execute(Parameter self,Parameter other) \


#define CHECK_AND_CREATE_RETURN(name)   \
if (logicName == name::logicName()) {\
 return std::make_shared<name>(paramater,skillIds);\
}

//スキルをランダムで選択する
MAKE_LOGIC(RandomLogic){
//  std::cout << "select RandomLogic " << std::endl;
  std::random_device rnd; // 非決定的な乱数生成器
  std::mt19937 mt(rnd());
  return SkillsCreate::createCommand(static_cast<TypeOfSkills>(skillIds_[mt() % skillIds_.size()]));
}

//HPがx％以下の時に技をランダムで選択する。
MAKE_LOGIC(HPIsLowLogic){
//  std::cout << "select HPIsLowLogic " << std::endl;
  if(paramater_.size() == 0){
    return nullptr;
  }
  std::random_device rnd; // 非決定的な乱数生成器
  std::mt19937 mt(rnd());
  int lessThen = paramater_[0];
  if(self.maxHP*lessThen/100.0 >= self.HP){
    return SkillsCreate::createCommand(static_cast<TypeOfSkills>(skillIds_[mt() % skillIds_.size()]));
  }
  return nullptr;
}

//HPがx％以上の時に技をランダムで選択する。
MAKE_LOGIC(HPIsHighLogic){
//  std::cout << "select HPIsHighLogic " << std::endl;
  if(paramater_.size() == 0){
    return nullptr;
  }
  std::random_device rnd; // 非決定的な乱数生成器
  std::mt19937 mt(rnd());
  int more = paramater_[0];
  if(self.maxHP*more/100.0 <= self.HP){
    return SkillsCreate::createCommand(static_cast<TypeOfSkills>(skillIds_[mt() % skillIds_.size()]));
  }
  return nullptr;
}

std::shared_ptr<EnemyLogicInterface> EnemyLogicCreate::createLogic(std::string logicName, std::vector<int> paramater, std::vector<int> skillIds) {
  //factory method
  if (logicName == "Random") {
    return std::make_shared<RandomLogic>(paramater,skillIds);
  }
  if (logicName == "HPIsLow") {
    return std::make_shared<HPIsLowLogic>(paramater,skillIds);
  }
  if (logicName == "HPIsHigh") {
    return std::make_shared<HPIsHighLogic>(paramater,skillIds);
  }
  return std::make_shared<RandomLogic>(paramater,skillIds);
};