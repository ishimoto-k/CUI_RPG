//
// Created by IshimotoKiko on 2021/09/12.
//

#ifndef APPEAL_HEALPOINT_HPP
#define APPEAL_HEALPOINT_HPP
#include "MapObjectInterface.hpp"

class HealPoint : public MapObjectInterface {
  bool isUse_ = false;

public:
  HealPoint(int x, int y) : MapObjectInterface(x, y) {
  }
  void view() override { std::cout << "\033[44m　\033[49m"; };
  void backViewStart() override {
    if (isUse_)
      std::cout << "\033[42m";
    else
      std::cout << "\033[102m";
  }
  void use(bool u){
    isUse_ = u;
  }
  bool use(){
    return isUse_;
  }
  void backViewEnd() override { std::cout << "\033[49m"; }
  void select() override { MapObjectInterface::select(); }

  bool move(const BitMap &bitMap,
            std::function<void(BitMapKind, Vector2, Vector2)> callback)
      override {
    return false;
  }
  bool move(const BitMap &bitMap, const Vector2 &vector,
            std::function<void(BitMapKind, Vector2, Vector2)> callback)
      override {
    return false;
  }
};

#endif // APPEAL_HEALPOINT_HPP
