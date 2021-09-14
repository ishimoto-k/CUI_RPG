//
// Created by IshimotoKiko on 2021/09/12.
//

#include "HealPoint.hpp"

HealPoint::HealPoint(int x, int y) : MapObjectInterface(x, y) {}
void HealPoint::view() { std::cout << "\033[44m　\033[49m"; };
void HealPoint::backViewStart() {
  if (isUse_)
    std::cout << "\033[42m";
  else
    std::cout << "\033[102m";
}
void HealPoint::use(bool u) { isUse_ = u; }
bool HealPoint::use() { return isUse_; }
void HealPoint::backViewEnd() { std::cout << "\033[49m"; }
void HealPoint::select() { MapObjectInterface::select(); }

bool HealPoint::move(
    const BitMap &bitMap,
    std::function<void(BitMapKind, Vector2, Vector2)> callback) {
  return false;
}
bool HealPoint::move(
    const BitMap &bitMap, const Vector2 &vector,
    std::function<void(BitMapKind, Vector2, Vector2)> callback) {
  return false;
}
