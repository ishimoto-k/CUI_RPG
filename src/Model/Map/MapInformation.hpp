//
// Created by IshimotoKiko on 2021/09/09.
//

#ifndef APPEAL_MAPINFORMATION_HPP
#define APPEAL_MAPINFORMATION_HPP

#include <yaml-cpp/yaml.h>

class MapInformation {
public:
  int level;
  int width;
  int height;
  int roomsMin;
  int roomsMax;
  int enemies;
  int heal;
  std::vector<int> typeOfEnemy;
  int boss;

  static const std::vector<MapInformation> &getMapInfoList() {
    static std::vector<MapInformation> mapInfoList{};
    if (!mapInfoList.empty())
      return mapInfoList;
    std::string fileName = "assets/mapInformation.yaml";
    try {
      auto nodes = YAML::LoadFile(fileName);
      for (auto i = 0; i < nodes["MAP"].size(); i++) {
        auto index = std::to_string(i);
        auto node = nodes["MAP"][index];
        if (!node)
          continue;
        MapInformation parameter;
        parameter.level = i + 1;
        parameter.width = node["width"].as<int>();
        parameter.height = node["height"].as<int>();
        parameter.roomsMin = node["roomsMin"].as<int>();
        parameter.roomsMax = node["roomsMax"].as<int>();
        parameter.enemies = node["enemies"].as<int>();
        parameter.heal = node["heal"].as<int>();
        parameter.typeOfEnemy = node["enemyKind"].as<std::vector<int>>();
        parameter.boss = node["boss"].as<int>();
        mapInfoList.push_back(parameter);
      }
      std::cout << fileName << "の読み込み成功" << std::endl;
    }catch (YAML::Exception &e) {
      std::cout << fileName << "が存在しません。終了します。" << std::endl;
      exit(-1);
    }
    return mapInfoList;
  }
  static const MapInformation getMapInfo(int level){
    auto list = getMapInfoList();
    if(list.size() > level){
      return list[level];
    }
    MapInformation parameter;
    parameter.level = -1;
    parameter.width = 10;
    parameter.height = 10;
    parameter.roomsMin = 1;
    parameter.roomsMax = 2;
    parameter.enemies = 1;
    parameter.heal = 0;
    parameter.typeOfEnemy = {1,2};
    parameter.boss = 0;
    return parameter;
  }
};
#endif // APPEAL_MAPINFORMATION_HPP
