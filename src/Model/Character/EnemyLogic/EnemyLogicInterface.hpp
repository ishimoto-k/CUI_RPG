//
// Created by IshimotoKiko on 2021/09/09.
//

#ifndef APPEAL_ENEMYLOGICINTERFACE_HPP
#define APPEAL_ENEMYLOGICINTERFACE_HPP
#include <CommandInterface.hpp>

class EnemyLogicInterface{
protected:
  std::vector<int> paramater_,skillIds_;
public:
  EnemyLogicInterface(std::vector<int> paramater,std::vector<int> skillIds):paramater_(paramater),skillIds_(skillIds){}
  virtual std::shared_ptr<CommandInterface> execute(Parameter self,Parameter other) = 0;
};
class EnemyLogicCreate {
public:
  static std::shared_ptr<EnemyLogicInterface> createLogic(std::string logicName, std::vector<int> paramater, std::vector<int> skillIds);
};
#endif // APPEAL_ENEMYLOGICINTERFACE_HPP
