//
// Created by IshimotoKiko on 2021/09/07.
//

#ifndef APPEAL_PARAMETER_HPP
#define APPEAL_PARAMETER_HPP
#include <vector>
#include <yaml-cpp/yaml.h>

class Parameter {
public:
  int ID;
  int level;
  int POW;
  int DEX;
  int maxHP;
  int maxMP;
  int HP;
  int MP;
  int EXP;
  int targetEXP;
  std::vector<int> skillIds;
  static const std::vector<Parameter>& getLevelList(){
    static std::vector<Parameter> levelList{};
    if(!levelList.empty())
      return levelList;

    auto nodes = YAML::LoadFile(std::string(CURRENT_DIRECTORY)+"/assets/LevelList.yaml");
    for(auto i = 1 ; i <= nodes["Level"].size(); i++){
      auto index = std::to_string(i);
      auto node = nodes["Level"][index];
      if(!node)
        continue;
      Parameter parameter;
      parameter.HP = parameter.maxHP = node["HP"].as<int>();
      parameter.MP = parameter.maxMP = node["MP"].as<int>();
      parameter.POW = node["POW"].as<int>();
      parameter.DEX = node["DEX"].as<int>();
      parameter.targetEXP = node["needEXP"].as<int>();
      parameter.level = i;
      if(node["getSkill"])
        parameter.skillIds = node["getSkill"].as<std::vector<int>>();
      levelList.push_back(parameter);
    }
    return levelList;
  }
  static Parameter loadFromLevel(int level){
    auto list = getLevelList();
    if(level < list.size()){
      auto itr = std::find_if(list.begin(),list.end(),[level](Parameter parameter){
        return parameter.level == level;
      });
      return *itr;
    }
    return Parameter();
  }
  static std::vector<int> loadSkillFromLevel(int level){
    auto list = getLevelList();
    std::vector<int> skills = {};
    for(int i=0;i<level && i < list.size(); i++){
      skills.insert(skills.end(),list[i].skillIds.begin(),list[i].skillIds.end());
    }
    std::sort(skills.begin(), skills.end());
    skills.erase(std::unique(skills.begin(), skills.end()), skills.end());
    return skills;
  }
};




#endif // APPEAL_PARAMETER_HPP
