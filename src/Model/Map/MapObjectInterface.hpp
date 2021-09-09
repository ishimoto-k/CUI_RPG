//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_MAPOBJECTINTERFACE_HPP
#define APPEAL_MAPOBJECTINTERFACE_HPP

#include <Vector2.hpp>
#include <Observer.hpp>

using namespace Vec;
using namespace Design;

class MapObjectInterface{
protected:
  Vector2 position_ = Vector2(0,0);
  int id_;

public:
  MapObjectInterface() = default;
  MapObjectInterface(int x,int y):position_(Vector2(x,y)){}
  virtual void view() = 0;
  int id(){
    return id_;
  }
  void set(Vector2 position){
    position_ = position;
  }
  virtual bool move(const BitMap& bitMap,std::function<void(BitMapKind,Vector2,Vector2)> callback) = 0;
  virtual bool move(const BitMap& bitMap,const Vector2& vector,std::function<void(BitMapKind,Vector2,Vector2)> callback) = 0;
  Vector2 position(){
    return position_;
  }
};

#endif // APPEAL_CHARACTORINTERFACE_HPP
