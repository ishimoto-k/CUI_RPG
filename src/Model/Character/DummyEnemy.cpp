//
// Created by IshimotoKiko on 2021/09/03.
//

#include "DummyEnemy.hpp"

void DummyEnemy::view() { std::cout << "敵"; }
void DummyEnemy::move(const BitMap& bitMap) {
  auto directions = ShuffulDirections();
  for (auto i : directions) {
    auto dir = position_ + i;
    auto bit = at(bitMap, dir);
    if (bit != NONE && bit != WALL) {
      auto body = std::make_shared<EventBody>();
      body->bit = bitMap[dir.y][dir.x];
      notify(ObserverEventList::MAP_VIEW__ENEMY_CollisionDetection,body);
      break;
    } else if(bit == NONE){
      position_ = dir;
      break;
    }
  }
}