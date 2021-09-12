//
// Created by IshimotoKiko on 2021/09/03.
//

#include "Enemy.hpp"

void Enemy::view() { std::cout << "敵"; }
bool Enemy::move(const BitMap& bitMap,std::function<void(BitMapKind,Vector2,Vector2)> callback) {
  if(isBoss_)
    return false;
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
  return false;
}
const std::vector<Enemy>& Enemy::getEnemyList(){
  static std::vector<Enemy> enemyList{};
  if(!enemyList.empty())
    return enemyList;
  std::string fileName = "assets/character.yaml";
  try {
    auto nodes = YAML::LoadFile(fileName);
    for (auto i = 0; i < nodes["ENEMY"].size(); i++) {
      Enemy enemy = Enemy();
      auto node = nodes["ENEMY"][i];
      if (!node)
        continue;
      Parameter parameter;
      parameter.ID = node["ID"].as<int>();
      parameter.maxHP = node["HP"].as<int>();
      parameter.maxMP = node["MP"].as<int>();
      parameter.POW = node["POW"].as<int>();
      parameter.DEX = node["DEX"].as<int>();
      parameter.EXP = node["EXP"].as<int>();
      parameter.level = node["LEVEL"].as<int>();
      //    parameter.skillIds = node["getSkill"].as<std::vector<int>>();
      if (node["Actions"]) {
        for (auto actions : node["Actions"]) {
          std::string logicName = actions["Logic"].as<std::string>();
          std::vector<int> commands =
              actions["commands"].as<std::vector<int>>();
          std::vector<int> parameter = {};
          if (actions["parameter"]) {
            parameter = actions["parameter"].as<std::vector<int>>();
          }
          auto logic =
              EnemyLogicCreate::createLogic(logicName, parameter, commands);
          enemy.logic.push_back(logic);
        }
      }
      enemy.parameter = parameter;
      enemy.name_ = node["name"].as<std::string>();
      std::string viewFile = "assets/" + node["ViewPath"].as<std::string>();
      std::ifstream ifs(viewFile);
      if(!ifs.is_open()){
        std::cout << viewFile << "が存在しません。終了します。" << std::endl;
        exit(-1);
      }
      std::string text = std::string(std::istreambuf_iterator<char>(ifs),
                                     std::istreambuf_iterator<char>());
      std::cout << viewFile << "の読み込み成功" << std::endl;
      enemy.setFrontView(text);
      enemyList.push_back(enemy);

    }
    std::cout << fileName << "の読み込み成功" << std::endl;
  }catch (YAML::Exception& e) {
    std::cout << fileName << "が存在しません。終了します。" << std::endl;
    exit(-1);
  }
  return enemyList;
}
std::shared_ptr<Enemy> Enemy::create(int id){
  auto list = getEnemyList();
  if(id <= list.size()){
    std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
    auto itr = std::find_if(list.begin(),list.end(),[id](Enemy enemy){
      return enemy.parameter.ID == id;
    });
    enemy->parameter = itr->parameter;
    enemy->name_ = itr->name_;
    enemy->logic = itr->logic;
    enemy->setFrontView(itr->frontView());
    enemy->makeIdx();
    return enemy;
  }
  return nullptr;
}