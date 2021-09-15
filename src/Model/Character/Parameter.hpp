//
// Created by IshimotoKiko on 2021/09/07.
//

#ifndef APPEAL_PARAMETER_HPP
#define APPEAL_PARAMETER_HPP
#include <vector>
#include <yaml-cpp/yaml.h>
#include <Defines.hpp>
#include "Status/StatusEnum.hpp"
class Parameter {
public:
  int ID; //id
  int level; //レベル
  int POW; //戦闘中の攻撃力、戦闘中は変動する。戦闘開始時にmaxPOWを代入する。
  int DEX; //戦闘中の守備力、戦闘中は変動する。戦闘開始時にmaxDEXを代入する。
  int HP;  //戦闘中のHP、戦闘中は変動する。戦闘開始時にmaxHPを代入する。
  int MP;  //戦闘中のMP、戦闘中は変動する。戦闘開始時にmaxMPを代入する。
  int maxHP;
  int maxMP;
  int maxPOW;
  int maxDEX;
  int EXP; //現在の経験値
  int targetEXP; //次レベルまでの経験値
  std::vector<int> skillIds; //習得しているスキルID
  std::vector<TypeOfStatus> status = {}; //かかっている状態異常ID
  static const std::vector<Parameter>& getLevelList() {
    // assetsからプレイヤーリストを読み込む。
    static std::vector<Parameter> levelList{};
    if (!levelList.empty())
      return levelList;

    auto fileName = define::AssetsLevelList();
    try {
      auto nodes = YAML::LoadFile(fileName);
      for (auto i = 1; i <= nodes["Level"].size(); i++) {
        auto index = std::to_string(i);
        auto node = nodes["Level"][index];
        if (!node)
          continue;
        Parameter parameter;
        parameter.HP = parameter.maxHP = node["HP"].as<int>();
        parameter.MP = parameter.maxMP = node["MP"].as<int>();
        parameter.POW = parameter.maxPOW = node["POW"].as<int>();
        parameter.DEX = parameter.maxDEX = node["DEX"].as<int>();
        parameter.targetEXP = node["needEXP"].as<int>();
        parameter.level = i;
        if (node["getSkill"])
          parameter.skillIds = node["getSkill"].as<std::vector<int>>();
        levelList.push_back(parameter);
      }
      std::cout << fileName << "の読み込み成功" << std::endl;
    } catch (YAML::Exception &e) {
      std::cout << fileName << "が存在しません。終了します。" << std::endl;
//      exit(-1);
    }
    return levelList;
  }
  static Parameter loadFromLevel(int level){
    //レベル値からステータスを取得
    auto list = getLevelList();
    if(level < list.size()){
      auto itr = std::find_if(list.begin(),list.end(),[level](Parameter parameter){
        return parameter.level == level;
      });
      return *itr;
    }
    return Parameter();
  }
  static Parameter loadFromExp(int exp){
    //経験値かレベルとステータスを習得
    auto list = getLevelList();
    bool check = false;
    for(auto l:list){
      if(check){
        if(l.targetEXP > exp){
          auto p = l;
          p.EXP = exp;
          return p;
        }
        check = false;
      }
      if(l.targetEXP <= exp){
        check = true;
      }
    }
    auto p = loadFromLevel(1);
    p.EXP = 0;
    return p;
  }
  static std::vector<int> loadSkillFromLevel(int level){
    //レベルから、覚えているスキルを取得
    //10の場合、1~10までで獲得するスキルをリストにして返す
    auto list = getLevelList();
    std::vector<int> skills = {};
    for(int i=0;i<level && i < list.size(); i++){
      skills.insert(skills.end(),list[i].skillIds.begin(),list[i].skillIds.end());
    }
    std::sort(skills.begin(), skills.end());
    skills.erase(std::unique(skills.begin(), skills.end()), skills.end());
    //被ったものは削除
    std::sort(skills.begin(), skills.end());
    return skills;
  }
};




#endif // APPEAL_PARAMETER_HPP
