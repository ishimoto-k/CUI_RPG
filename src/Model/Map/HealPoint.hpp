//
// Created by IshimotoKiko on 2021/09/12.
//

#ifndef APPEAL_HEALPOINT_HPP
#define APPEAL_HEALPOINT_HPP
#include "MapObjectInterface.hpp"

//回復スポット
class HealPoint : public MapObjectInterface {
  bool isUse_ = false;

public:
  HealPoint(int x, int y);
  void view() override;
  void backViewStart() override;
  void use(bool u);
  bool use();
  void backViewEnd() override;
  void select() override;
  bool move(const BitMap &bitMap,
            std::function<void(BitMapKind, Vector2, Vector2)> callback) override;
  bool move(const BitMap &bitMap, const Vector2 &vector,
            std::function<void(BitMapKind, Vector2, Vector2)> callback) override;
};

#endif // APPEAL_HEALPOINT_HPP
