//
// Created by IshimotoKiko on 2021/09/04.
//

#include "Player.hpp"

void Player::view() { std::cout << "Ｏ"; }
void Player::move(const BitMap& bitMap) {
}
void Player::move(const BitMap& bitMap,const Vector2& direction) {
  auto pos = position_ + direction;
  if (at(bitMap, pos) == NONE) {
    position_ = pos;
  } else{
    auto body = std::make_shared<EventBody>();
    body->bit = bitMap[pos.y][pos.x];
    notify(ObserverEventList::MAP_VIEW__PLAYER_CollisionDetection,body);
  }
}