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
  enum Direction {
    UP,
    DOWN,
    RIGHT,
    LEFT,
    NONE,
  };
  Vector2(int posx,int posy);
  Vector2(Direction direction);
  Vector2 operator +(Vector2 r);
  bool operator == (Vector2 r);
  std::string debug();
};

//ダンジョン生成で扱うパラメーター定数
enum BitMapKind {
  ERR = -1,
  WALL, //壁
  NONE, //道
  PLAYER, //プレイヤー
  ENEMY, //敵
  MAPOBJECT, //マップオブジェクト
  BUILDING_WALL = 100, //ダンジョン生成で使う定数
};
typedef std::vector<std::vector<BitMapKind>> BitMap;

//4方向をランダムに並び替えて配列で出力
static std::vector<Vector2> ShuffulDirections() {
  std::vector<Vector2> vectors = {Vector2(0, 1), Vector2(1, 0), Vector2(0, -1), Vector2(-1, 0)};
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::shuffle(vectors.begin(), vectors.end(), engine);
  return vectors;
}

//指定した位置のBitMapKindを出力
static BitMapKind at(const BitMap& bitmap,Vector2 v){
  if(v.y >= bitmap.size())return ERR;
  if(v.y <= -1)return ERR;
  if(v.x >= bitmap[v.y].size())return ERR;
  if(v.x <= -1)return ERR;
  return bitmap[v.y][v.x];
}

}
#endif // APPEAL_VECTOR2_HPP
