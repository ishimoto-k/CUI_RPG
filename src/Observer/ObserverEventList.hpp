//
// Created by IshimotoKiko on 2021/08/31.
//

#ifndef APPEAL_OBSERVEREVENTLIST_HPP
#define APPEAL_OBSERVEREVENTLIST_HPP
enum class ObserverEventList : int {
  DUMMY = 0,

  MAP_VIEW = 0x1000,
  MAP_VIEW__PLAYER_CollisionDetection,
  MAP_VIEW__ENEMY_CollisionDetection,
};
#endif    // APPEAL_OBSERVEREVENTLIST_HPP
