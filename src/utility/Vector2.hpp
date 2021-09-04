//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_VECTOR2_HPP
#define APPEAL_VECTOR2_HPP

#include <random>

namespace Vec{

class Vector2{
public:
  int x;
  int y;
  Vector2(int posx,int posy){
    x = posx;
    y = posy;
  }

  Vector2 operator +(Vector2 r){ return Vector2(x+r.x,y+r.y);}
  bool operator == (Vector2 r){
    return x==r.x&&y==r.y;
  }
};
typedef std::vector<std::vector<int>> BitMap;

static std::vector<Vector2> ShuffulDirections() {
  std::vector<Vector2> vectors = {Vector2(0, 1), Vector2(1, 0), Vector2(0, -1), Vector2(-1, 0)};
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::shuffle(vectors.begin(), vectors.end(), engine);
  return vectors;
}

static int at(const BitMap& bitmap,Vector2 v){
    if(v.y >= bitmap.size())return -1;
    if(v.y <= -1)return -1;
    if(v.x >= bitmap[v.y].size())return -1;
    if(v.x <= -1)return -1;
    return bitmap[v.y][v.x];
}
}
#endif // APPEAL_VECTOR2_HPP
