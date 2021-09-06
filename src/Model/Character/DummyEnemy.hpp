//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_DUMMYENEMY_HPP
#define APPEAL_DUMMYENEMY_HPP

#include "../Map/MapObjectInterface.hpp"
#include <iostream>

class DummyEnemy :public MapObjectInterface{
public:
  DummyEnemy(int x,int y):MapObjectInterface(x,y){}
  void view() override;
  void move(const BitMap& bitMap) override;
  void move(const BitMap& bitMap,const Vector2& vecctor) override {};
};

#endif // APPEAL_DUMMYENEMY_HPP
