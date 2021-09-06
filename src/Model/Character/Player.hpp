//
// Created by IshimotoKiko on 2021/09/04.
//

#ifndef APPEAL_PLAYER_HPP
#define APPEAL_PLAYER_HPP

#include <MapObjectInterface.hpp>
#include <Character.hpp>
#include <iostream>
#include <Fire.hpp>

class Player :public MapObjectInterface,public Character{
public:
  Player(int x,int y):MapObjectInterface(x,y){}
  void view() override;
  void move(const BitMap& bitMap) override;
  void move(const BitMap& bitMap,const Vector2& direction) override;

  std::vector<std::shared_ptr<SkillInterface>> skill = {std::make_shared<Fire>()};
};
#endif // APPEAL_PLAYER_HPP
