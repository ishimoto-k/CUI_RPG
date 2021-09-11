//
// Created by IshimotoKiko on 2021/09/05.
//
#include "Vector2.hpp"

using namespace Vec;

Vector2::Vector2(int posx,int posy){
  x = posx;
  y = posy;
}
Vector2::Vector2(Direction direction){
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
  case NONE:
    x = 0, y = 0;
    break;
  }
}

Vector2 Vector2::operator +(Vector2 r){ return Vector2(x+r.x,y+r.y);}
bool Vector2::operator == (Vector2 r){
  return x==r.x&&y==r.y;
}
std::string Vector2::debug(){
  return "x:" + std::to_string(x) + " y:" + std::to_string(y);
}
