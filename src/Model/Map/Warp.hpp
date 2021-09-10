//
// Created by IshimotoKiko on 2021/09/10.
//

#ifndef APPEAL_WARP_HPP
#define APPEAL_WARP_HPP
#include "MapObjectInterface.hpp"

class Warp : public MapObjectInterface{
  bool isStart_ = true;
public:
  Warp(int x,int y,bool isStart):MapObjectInterface(x,y){
    isStart_ = isStart;
  }
  void view()override{
    std::cout << "\033[44m　\033[49m";
  };
  void backViewStart()override{
    if(isStart_)
      std::cout << "\033[44m";
    else
      std::cout << "\033[104m";
  }
  void backViewEnd()override{
      std::cout << "\033[49m";
  }
  void select()override {
    MapObjectInterface::select();
  }

  bool move(const BitMap& bitMap,std::function<void(BitMapKind,Vector2,Vector2)> callback) override{
      return false;
  }
  bool move(const BitMap& bitMap,const Vector2& vector,std::function<void(BitMapKind,Vector2,Vector2)> callback) override {
      return false;
  }
};

#endif // APPEAL_WARP_HPP
