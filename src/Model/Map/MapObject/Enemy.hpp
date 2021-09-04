//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_ENEMY_HPP
#define APPEAL_ENEMY_HPP

#include <iostream>
#include "MapObjectInterface.hpp"

class Enemy :public MapObjectInterface{
public:
  Enemy(int x,int y):MapObjectInterface(x,y){}
  void view() override;
  void move(const BitMap& bitMap) override;
  void move(const BitMap& bitMap,const Vector2& vecctor) override {};
};
#endif // APPEAL_ENEMY_HPP
