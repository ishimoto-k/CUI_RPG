//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_GAMESEANESTATUS_HPP
#define APPEAL_GAMESEANESTATUS_HPP

enum KeyBoardWait{
  HIT,
  WAIT,
};
class GameSeaneStatus {
public:
  enum Status{
    TITLE = 0x1000,
    MAP_VIEW = 0x2000,
    BATTLE = 0x3000,
    GAME_OVER = 0x4000,
  };
  KeyBoardWait keyBoardWait = KeyBoardWait::WAIT;
  GameSeaneStatus(Status status):status_(status){};
  Status getStatus(){
    return status_;
  };
  bool operator ==(GameSeaneStatus s){ return status_==s.status_;}
  bool operator !=(GameSeaneStatus s){ return status_!=s.status_;}
  std::string log(){
    return std::to_string(status_);
  }
private:
  Status status_;

};
#endif // APPEAL_GAMESEANESTATUS_HPP