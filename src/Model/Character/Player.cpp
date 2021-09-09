//
// Created by IshimotoKiko on 2021/09/04.
//

#include "Player.hpp"

void Player::view() { std::cout << "Ｏ"; }
bool Player::move(const BitMap& bitMap,std::function<void(BitMapKind,Vector2,Vector2)> callback) {
  return false;
}
bool Player::move(const BitMap& bitMap,const Vector2& direction,std::function<void(BitMapKind,Vector2,Vector2)> callback) {
  auto pos = position_ + direction;
  if (at(bitMap, pos) == NONE) {
    position_ = pos;
    return false;
  } else{
    callback(at(bitMap, pos),pos,position_);
    if(at(bitMap, pos) == ENEMY){
      return true;
    }
    return false;
  }
}