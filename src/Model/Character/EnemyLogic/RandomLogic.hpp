//
// Created by IshimotoKiko on 2021/09/11.
//

#ifndef APPEAL_RANDOMLOGIC_HPP
#define APPEAL_RANDOMLOGIC_HPP
#include <random>
#include "EnemyLogicInterface.hpp"
#include "SkillsCreate.hpp"

class RandomLogic : public EnemyLogicInterface{
public:
  RandomLogic(std::vector<int> skillIds):EnemyLogicInterface({},skillIds){};
  std::shared_ptr<CommandInterface> execute(Parameter self,Parameter other)override {
    std::random_device rnd;     // 非決定的な乱数生成器
    std::mt19937 mt(rnd());
    return SkillsCreate::createCommand(static_cast<TypeOfSkills>(skillIds_[mt() % skillIds_.size()]));
  };
};

#endif // APPEAL_RANDOMLOGIC_HPP
