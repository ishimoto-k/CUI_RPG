//
// Created by IshimotoKiko on 2021/09/03.
//

#include "Enemy.hpp"

void Enemy::view() { std::cout << "敵"; }
bool Enemy::move(const BitMap& bitMap,std::function<void(BitMapKind,Vector2,Vector2)> callback) {
  auto directions = ShuffulDirections();
  for (auto i : directions) {
    auto dir = position_ + i;
    auto bit = at(bitMap, dir);
    if (bit != NONE && bit != WALL) {
      callback(bit,dir,position_);
      return true;
    } else if(bit == NONE){
      position_ = dir;
      return false;
    }
  }
}
const std::vector<Enemy>& Enemy::getEnemyList(){
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
std::shared_ptr<Enemy> Enemy::create(int id){
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