//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_ENEMY_HPP
#define APPEAL_ENEMY_HPP

#include <Character.hpp>
#include <Command/Command.hpp>
#include <EnemyLogicInterface.hpp>
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
  std::vector<std::shared_ptr<EnemyLogicInterface>> logic;

public:
  std::string getIdx(){
    //同じオブジェクトかを判断するためのユニークID
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
    parameter.POW = parameter.maxPOW;
    parameter.DEX = parameter.maxDEX;
    parameter.status.clear();
    status.clear();
  }
  std::shared_ptr<CommandInterface> battleLogic(int turn,Parameter other){
    //todo virtual化
    if(turn == 0)
      return nullptr;
    int around = turn;
    std::shared_ptr<CommandInterface> command = nullptr;
    do{
      //エネミーロジックの読み込み、
      //ターンごとに行動が変わる
      int select = (around-1)%logic.size();
      auto l = logic[select];
      command = l->execute(parameter,other);//ロジックの実行とコマンドの取得
      around ++;
    }while (!command);
    return command;
  }

  static const std::vector<Enemy>& getEnemyList();//assetsから敵情報を読み込む
  static std::shared_ptr<Enemy> create(int id);//敵情報をIDから取得
};
#endif // APPEAL_ENEMY_HPP
