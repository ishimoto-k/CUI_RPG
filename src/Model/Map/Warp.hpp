//
// Created by IshimotoKiko on 2021/09/10.
//

#ifndef APPEAL_WARP_HPP
#define APPEAL_WARP_HPP
#include "MapObjectInterface.hpp"

//入口、出口
class Warp : public MapObjectInterface{
  bool isStart_ = true;
public:
  Warp(int x,int y,bool isStart);
  void view()override;
  void backViewStart()override;
  void backViewEnd()override;
  void select()override;
  bool move(const BitMap& bitMap,std::function<void(BitMapKind,Vector2,Vector2)> callback) override;
  bool move(const BitMap& bitMap,const Vector2& vector,std::function<void(BitMapKind,Vector2,Vector2)> callback) override;
};

#endif // APPEAL_WARP_HPP
