//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_GAMESTATUS_HPP
#define APPEAL_GAMESTATUS_HPP

enum KeyBoardWait{
  HIT,
  WAIT,
};
class GameStatus{
public:
  enum Status{
    TITLE = 0x1000,
    MAP_VIEW = 0x2000,
    BATTLE = 0x3000,
    GAME_OVER = 0x4000,
  };
  KeyBoardWait keyBoardWait = KeyBoardWait::WAIT;
  GameStatus(Status status):status_(status){};
  Status getStatus(){
    return status_;
  };
  bool operator ==(Status s){ return status_==s;}
  bool operator !=(Status s){ return status_!=s;}
  std::string log(){
    return std::to_string(status_);
  }
private:
  Status status_;

};
#endif // APPEAL_GAMESTATUS_HPP
