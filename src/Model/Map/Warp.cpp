//
// Created by IshimotoKiko on 2021/09/10.
//

#include "Warp.hpp"

Warp::Warp(int x, int y, bool isStart) : MapObjectInterface(x, y) {
  isStart_ = isStart;
}
void Warp::view() { std::cout << "\033[44m　\033[49m"; };
void Warp::backViewStart() {
  if (isStart_)
    std::cout << "\033[44m";
  else
    std::cout << "\033[104m";
}
void Warp::backViewEnd() { std::cout << "\033[49m"; }
void Warp::select() { MapObjectInterface::select(); }

bool Warp::move(const BitMap &bitMap,
                std::function<void(BitMapKind, Vector2, Vector2)> callback) {
  return false;
}
bool Warp::move(const BitMap &bitMap, const Vector2 &vector,
                std::function<void(BitMapKind, Vector2, Vector2)> callback) {
  return false;
}
