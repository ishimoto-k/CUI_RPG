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
  enum Direction{
      UP,
      DOWN,
      RIGHT,
      LEFT,
  };
  Vector2(int posx,int posy){
    x = posx;
    y = posy;
  }
  Vector2(Direction direction){
    switch (direction) {
    case UP:
      x = 0, y = -1;
      break;
    case DOWN:
      x = 0, y = 1;
      break;
    case RIGHT:
      x = 1, y = 0;
      break;
    case LEFT:
      x = -1, y = 0;
      break;
    }
  }

  Vector2 operator +(Vector2 r){ return Vector2(x+r.x,y+r.y);}
  bool operator == (Vector2 r){
    return x==r.x&&y==r.y;
  }
};

//ダンジョン生成で扱う一時的なパラメーター定数
enum BitMapKind {
  ERR = -1,
  WALL,
  NONE,
  OBJECT,
  BUILDING_WALL = 100,
};
typedef std::vector<std::vector<BitMapKind>> BitMap;

static std::vector<Vector2> ShuffulDirections() {
  std::vector<Vector2> vectors = {Vector2(0, 1), Vector2(1, 0), Vector2(0, -1), Vector2(-1, 0)};
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::shuffle(vectors.begin(), vectors.end(), engine);
  return vectors;
}

static BitMapKind at(const BitMap& bitmap,Vector2 v){
  if(v.y >= bitmap.size())return ERR;
  if(v.y <= -1)return ERR;
  if(v.x >= bitmap[v.y].size())return ERR;
  if(v.x <= -1)return ERR;
  return bitmap[v.y][v.x];
}

}
#endif // APPEAL_VECTOR2_HPP
