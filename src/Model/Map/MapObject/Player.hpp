//
// Created by IshimotoKiko on 2021/09/04.
//

#ifndef APPEAL_PLAYER_HPP
#define APPEAL_PLAYER_HPP

#include <iostream>
#include "MapObjectInterface.hpp"

class Player :public MapObjectInterface{
public:
  Player(int x,int y):MapObjectInterface(x,y){}
  void view() override;
  void move(const BitMap& bitMap) override;
  void move(const BitMap& bitMap,const Vector2& direction) override;
};
#endif // APPEAL_PLAYER_HPP
