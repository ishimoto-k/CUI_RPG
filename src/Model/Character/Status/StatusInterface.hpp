//
// Created by IshimotoKiko on 2021/09/12.
//

#ifndef APPEAL_STATUSINTERFACE_HPP
#define APPEAL_STATUSINTERFACE_HPP
#include "../Parameter.hpp"

//状態異常のインターフェース
class StatusInterface{
protected:
  bool active_ = true;
public:
  bool getActive(){ return active_;}
  virtual int id() = 0;//IDの取得
  virtual std::string name() = 0;//状態異常の名前

  //状態異常の効果を発動
  virtual bool update(std::string fromName,std::string toName,Parameter& from,Parameter& to,std::vector<std::string>* log){return true;}
};

#endif // APPEAL_STATUSINTERFACE_HPP
