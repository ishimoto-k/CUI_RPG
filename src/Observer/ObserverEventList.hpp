//
// Created by IshimotoKiko on 2021/08/31.
//

#ifndef APPEAL_OBSERVEREVENTLIST_HPP
#define APPEAL_OBSERVEREVENTLIST_HPP
//イベントのリスト
enum class ObserverEventList : int {
  DUMMY = 0,

  TITLE_SCENE = 0x1000,
  TITLE_SCENE_ON_SELECT, //タイトル画面で選択したときのイベント

  MAP_SCENE = 0x2000,
  MAP_SCENE_PLAYER_CollisionDetection, //マップ画面でプレイヤーがオブジェクトに衝突したときのイベント
  MAP_SCENE_ENEMY_CollisionDetection,  //マップ画面で敵がオブジェクトに衝突したときのイベント
  MAP_SCENE_SELECT_WARP_START, //マップ画面で入り口を選択したときのイベント
  MAP_SCENE_SELECT_WARP_GOAL, //マップ画面で出口を選択したときのイベント

  BATTLE_SCENE = 0x4000,
  BATTLE_SCENE_ESCAPE, //戦闘離脱
  BATTLE_SCENE_WIN,//戦闘勝利
  BATTLE_SCENE_LOSE,//戦闘敗北

  KEYBOARD = 0x10000,
  KEYBOARD_ON_INPUT,
};
#endif    // APPEAL_OBSERVEREVENTLIST_HPP
