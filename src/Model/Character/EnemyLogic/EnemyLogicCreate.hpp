//
// Created by IshimotoKiko on 2021/09/11.
//

#ifndef APPEAL_ENEMYLOGICCREATE_HPP
#define APPEAL_ENEMYLOGICCREATE_HPP
#include "RandomLogic.hpp"
class EnemyLogicCreate {
public:
  static std::shared_ptr<EnemyLogicInterface>
  createLogic(std::string logicName, std::vector<int> paramater, std::vector<int> skillIds) {
    if (logicName == "Random") {
      return std::make_shared<RandomLogic>(skillIds);
    }

    return std::make_shared<RandomLogic>(skillIds);
  };
};
#endif // APPEAL_ENEMYLOGICCREATE_HPP
