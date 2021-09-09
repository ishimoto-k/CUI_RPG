//
// Created by IshimotoKiko on 2021/09/09.
//

#ifndef APPEAL_GAMESCENEINTERFACE_HPP
#define APPEAL_GAMESCENEINTERFACE_HPP
#include <Observer.hpp>
using namespace Design;
class GameSceneInterface : public Subject{
public:
  virtual  void Up() = 0;
  virtual  void Down() = 0;
  virtual  void Left() = 0;
  virtual  void Right() = 0;
  virtual  void Select() = 0;
  virtual  void Cancel() = 0;
  virtual  void Esc() = 0;
  virtual  void update() = 0;
  virtual  void view() = 0;
};
#endif // APPEAL_GAMESCENEINTERFACE_HPP
