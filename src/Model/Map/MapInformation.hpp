//
// Created by IshimotoKiko on 2021/09/09.
//

#ifndef APPEAL_MAPINFORMATION_HPP
#define APPEAL_MAPINFORMATION_HPP

#include <yaml-cpp/yaml.h>
#include <Defines.hpp>

//マップ情報を保持するクラス
class MapInformation {
public:
  int level; //階層
  int width; //マップ横幅
  int height;//マップ縦幅
  int roomsMin;//マップの最低限の部屋数
  int roomsMax;//マップの最大限の部屋数
  int enemies; //マップに出現する敵数
  int heal;    //回復スポットの数
  std::vector<int> typeOfEnemy; //出現する敵の種類
  int boss; //出現するボスの種類　//0は出現しない

  static const std::vector<MapInformation> &getMapInfoList() {
    //マップ情報をファイルから読み込む。
    static std::vector<MapInformation> mapInfoList{};
    if (!mapInfoList.empty())
      return mapInfoList;
    std::string fileName = define::AssetsMapInformation();
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
    }
    return mapInfoList;
  }
  static const MapInformation getMapInfo(int level){
    //level = 階層
    //階層毎の情報を取得する
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
