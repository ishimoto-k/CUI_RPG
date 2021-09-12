//
// Created by IshimotoKiko on 2021/09/11.
//

#ifndef APPEAL_STATUSCREATER_HPP
#define APPEAL_STATUSCREATER_HPP

#include "../Command/CommandInterface.hpp"
#include "StatusInterface.hpp"
#include "StatusEnum.hpp"

class StatusCreate {
public:
  static std::shared_ptr<StatusInterface> createStatus(TypeOfStatus status);
};
#endif // APPEAL_SKILLSCREATER_HPP
