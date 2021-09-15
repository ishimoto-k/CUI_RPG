//
// Created by IshimotoKiko on 2021/09/09.
//

#ifndef APPEAL_GAMESCENEINTERFACE_HPP
#define APPEAL_GAMESCENEINTERFACE_HPP
#include <Observer.hpp>
using namespace Design;
//ゲームシーンのインターフェース
//外界からの入力をゲームシーンに伝える
class GameSceneInterface : public Subject{
public:
  virtual  void Up() = 0;/*上*/
  virtual  void Down() = 0;/*下*/
  virtual  void Left() = 0; /*左*/
  virtual  void Right() = 0; /*右*/
  virtual  void Select() = 0; /*選択*/
  virtual  void Cancel() = 0; /*キャンセル*/
  virtual  void Esc() = 0;/*Esc*/

  virtual  void update() = 0;/*処理*/
  virtual  void view() = 0;/*描画*/
};
#endif // APPEAL_GAMESCENEINTERFACE_HPP
