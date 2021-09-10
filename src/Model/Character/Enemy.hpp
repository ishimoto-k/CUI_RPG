//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_ENEMY_HPP
#define APPEAL_ENEMY_HPP

#include <Character.hpp>
#include <MapObjectInterface.hpp>
#include <fstream>
#include <iostream>
#include <iterator>

class Enemy :public MapObjectInterface,public Character{
protected:
  std::string frontViewText_ = "";
  std::string idx_ = "";
  std::string name_ = "";
  bool isBoss_ = false;
  void makeIdx(){
    if(idx_ != "")
      return;
    std::string unique_identifier;
    std::string chars = "abcdefghijklmnopqrstuwxyzABCDEFGHIJKLMNOPQRSTUWXYZ0123456789,./;'[]-=<>?:{}|_+";
    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<> idx(0, 32);
    for (int i = 0; i < 32; ++i) {
      unique_identifier += chars[idx(mt)];
    }
    idx_ = unique_identifier;
  }

public:
  std::string getIdx(){
    return idx_;
  }
  Enemy(int x,int y,bool boss = false):MapObjectInterface(x,y){
    makeIdx();
    isBoss_=boss;
  }
  Enemy(bool boss = false){
    Enemy(0,0);
  };
  void setBoss(){isBoss_=true;};
  void view() override;
  std::string name() override {
    return name_;
  }
  virtual bool move(const BitMap& bitMap,std::function<void(BitMapKind,Vector2,Vector2)> callback) override;
  virtual bool move(const BitMap& bitMap,const Vector2& vector,std::function<void(BitMapKind,Vector2,Vector2)> callback) override {
      return true;
  };
  std::string frontView() override {
    return frontViewText_;
  }
  void setFrontView(const std::string& str){
    frontViewText_ = str;
  }
  void initBattleBefore()override {
    parameter.HP = parameter.maxHP;
    parameter.MP = parameter.maxMP;
  }

  static const std::vector<Enemy>& getEnemyList();
  static std::shared_ptr<Enemy> create(int id);
};
#endif // APPEAL_ENEMY_HPP
