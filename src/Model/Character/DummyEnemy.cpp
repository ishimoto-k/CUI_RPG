//
// Created by IshimotoKiko on 2021/09/03.
//

#include "DummyEnemy.hpp"

void DummyEnemy::view() { std::cout << "敵"; }
bool DummyEnemy::move(const BitMap& bitMap,std::function<void(BitMapKind,Vector2,Vector2)> callback) {
  auto directions = ShuffulDirections();
  for (auto i : directions) {
    auto dir = position_ + i;
    auto bit = at(bitMap, dir);
    if (bit != NONE && bit != WALL) {
      callback(bit,dir,position_);
      return true;
    } else if(bit == NONE){
      position_ = dir;
      return false;
    }
  }
  return false;
}