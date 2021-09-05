//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_MAPOBJECTINTERFACE_HPP
#define APPEAL_MAPOBJECTINTERFACE_HPP

#include <Vector2.hpp>
#include <Observer.hpp>

using namespace Vec;
using namespace Design;

class MapObjectInterface : public Subject {
protected:
  Vector2 position_ = Vector2(0,0);
  int id_;

public:
  class EventBody:public SubjectDataBody{
  public:
    BitMapKind bit;

  };
  MapObjectInterface(int x,int y):position_(Vector2(x,y)){}
  virtual void view() = 0;
  int id(){
    return id_;
  }
  virtual void move(const BitMap& bitMap) = 0;
  virtual void move(const BitMap& bitMap,const Vector2& vecctor) = 0;
  Vector2 position(){
    return position_;
  }
};

#endif // APPEAL_CHARACTORINTERFACE_HPP
