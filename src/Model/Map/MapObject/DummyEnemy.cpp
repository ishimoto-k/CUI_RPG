//
// Created by IshimotoKiko on 2021/09/03.
//

#include "DummyEnemy.hpp"

void DummyEnemy::view() { std::cout << "敵"; }
void DummyEnemy::move(const BitMap& bitMap) {
  auto directions = ShuffulDirections();
  for (auto i : directions) {
    auto dir = position_ + i;
    if (at(bitMap, dir) == 0) {
      position_ = dir;
      break;
    }
  }
}