//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_VECTOR2_HPP
#define APPEAL_VECTOR2_HPP


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


}
#endif // APPEAL_VECTOR2_HPP
