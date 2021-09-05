//
// Created by IshimotoKiko on 2021/09/03.
//

#include "Enemy.hpp"

void Enemy::view() { std::cout << "敵"; }
void Enemy::move(const BitMap& bitMap) {
  auto directions = ShuffulDirections();
  for (auto i : directions) {
    auto dir = position_ + i;
    if (at(bitMap, dir) == NONE) {
      position_ = dir;
      break;
    }
  }
}