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
  }
}