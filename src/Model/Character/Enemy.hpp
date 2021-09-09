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
  std::string frontViewText_ = "";
  std::string idx_ = "";
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
  Enemy(int x,int y):MapObjectInterface(x,y){makeIdx();}
  Enemy(){
    Enemy(0,0);
  };
  void view() override;
  std::string name(){
    return "敵";
  }
  bool move(const BitMap& bitMap,std::function<void(BitMapKind,Vector2,Vector2)> callback) override;
  bool move(const BitMap& bitMap,const Vector2& vector,std::function<void(BitMapKind,Vector2,Vector2)> callback) override {};
  std::string frontView() override {
    return frontViewText_;
  }
  void setFrontView(const std::string& str){
    frontViewText_ = str;
  }
  void initBattleBefore(){
    parameter.HP = parameter.maxHP;
    parameter.MP = parameter.maxMP;
  }
  //  - name: 弱い敵
  //      ID: 1
  //      LEVEL: 2
  //      HP: 40
  //      MP: 0
  //      POW: 5
  //      DEX: 3
  //      EXP: 15
  //      ViewPath: enemy1
  //      Actions:
  //        - { Logic: Random,commands: [0]}
  static const std::vector<Enemy>& getEnemyList(){
    static std::vector<Enemy> enemyList{};
    if(!enemyList.empty())
      return enemyList;

    auto nodes = YAML::LoadFile(std::string(CURRENT_DIRECTORY)+"/assets/character.yaml");
    for(auto i = 1 ; i <= nodes["ENEMY"].size(); i++){
      auto node = nodes["ENEMY"][i];
      if(!node)
        continue;
      Parameter parameter;
      parameter.maxHP = node["HP"].as<int>();
      parameter.maxMP = node["MP"].as<int>();
      parameter.POW = node["POW"].as<int>();
      parameter.DEX = node["DEX"].as<int>();
      parameter.EXP = node["EXP"].as<int>();
      parameter.level = node["LEVEL"].as<int>();
      if(node["getSkill"]){
        auto getskills = node["getSkill"];
        for(auto s =0;s< getskills.size();s++){
          parameter.skillIds.push_back(getskills[s].as<int>());
        }
      }
      Enemy enemy = Enemy();
      enemy.parameter = parameter;
      std::ifstream ifs(std::string(CURRENT_DIRECTORY)+"/assets/"+node["ViewPath"].as<std::string>());
      std::string text = std::string(std::istreambuf_iterator<char>(ifs),
                         std::istreambuf_iterator<char>());
      enemy.setFrontView(text);
      enemyList.push_back(enemy);
    }
    return enemyList;
  }
  static std::shared_ptr<Enemy> create(int id){
    auto list = getEnemyList();
    if(id < list.size()){
      std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
      enemy->parameter = list[id].parameter;
      enemy->setFrontView(list[id].frontView());
      enemy->makeIdx();
      return enemy;
    }
    return nullptr;
  }
};
#endif // APPEAL_ENEMY_HPP
