//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_DUNGEONCREATE_HPP
#define APPEAL_DUNGEONCREATE_HPP


#include <iostream>
#include <vector>
#include <random>
#include "DungeonInterface.hpp"

//メインのアルゴリズムは壁伸ばし法
class DungeonCreate : public DungeonInterfece{
  std::vector<Vector2> selectWall;
  int at(Vector2 v);
  void process();
  void build(Vector2 wall);
  void buildStart();
public:
  DungeonCreate(int w, int h);
  bool create() override;
  void debug() override;
};
#endif // APPEAL_DUNGEONCREATE_HPP
