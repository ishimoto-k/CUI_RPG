//
// Created by IshimotoKiko on 2021/09/07.
//

#ifndef APPEAL_PARAMETER_HPP
#define APPEAL_PARAMETER_HPP
#include <vector>
#include <yaml-cpp/yaml.h>

class Parameter {
public:
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
      parameter.maxHP = node["HP"].as<int>();
      parameter.maxMP = node["MP"].as<int>();
      parameter.POW = node["POW"].as<int>();
      parameter.DEX = node["DEX"].as<int>();
      parameter.targetEXP = node["needEXP"].as<int>();
      parameter.level = i;
      if(node["getSkill"]){
        auto getskills = node["getSkill"];
        for(auto s =0;s< getskills.size();s++){
          parameter.skillIds.push_back(getskills[s].as<int>());
        }
      }
      levelList.push_back(parameter);
    }
    return levelList;
  }
};




#endif // APPEAL_PARAMETER_HPP
