//
// Created by IshimotoKiko on 2021/09/10.
//

#ifndef APPEAL_GAMEINFORMATION_HPP
#define APPEAL_GAMEINFORMATION_HPP
#include <iostream>
#include <yaml-cpp/yaml.h>

//ゲーム情報を扱うクラス
//データの保存と読み込みを行う。
class GameInformation {
  //todo シングルトンにしたほうがいい？
public:
  class SaveDate;

private:
  bool hasSaveFile_ = false;
  std::vector<SaveDate> vectorSaveData;//セーブデータの配列、今回は一つしか使わない
  int useSlot = 0;

  void save_(){
    std::string fileName = "savedata.yaml";
    YAML::Node saveData;
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "SAVEDATA";
    out << YAML::BeginSeq;
    for(auto data:vectorSaveData){
      out << YAML::BeginMap;
      out << YAML::Key << "currentMap";
      out << YAML::Value << data.mapLevel;
      out << YAML::Key << "clearMap";
      out << YAML::Value << data.mapClearStatus;
      out << YAML::Key << "exp";
      out << YAML::Value << data.exp;
      out << YAML::EndMap;
    }
    out << YAML::EndSeq;
    out << YAML::EndMap;
    std::ofstream fout(fileName);
    fout << out.c_str();
  }
public:
  class SaveDate{
  public:
    //保存するデータは3つ
    int mapClearStatus = 1; //到達したマップ
    int mapLevel = 1;       //今いるマップ
    int exp = 0;            //持っている経験値
  };
  GameInformation() {
    std::string fileName = "savedata.yaml";
    try {
      auto nodes = YAML::LoadFile(fileName);
      for(auto savedate:nodes["SAVEDATA"]){
        //データの読み込み
        SaveDate saveDate;
        saveDate.mapLevel = savedate["currentMap"].as<int>();
        saveDate.mapClearStatus = savedate["clearMap"].as<int>();
        saveDate.exp = savedate["exp"].as<int>();
        hasSaveFile_ = true;
        vectorSaveData.push_back(saveDate);
      }
    }catch (YAML::Exception& e) {
      //データがない場合
      //初回起動時。
      SaveDate saveDate;
      saveDate.mapLevel = 1;
      saveDate.mapClearStatus = 1;
      saveDate.exp =0;
      hasSaveFile_ = false;
      vectorSaveData.push_back(saveDate);
    }
  }
  void setSlot(int id){
    useSlot = id;
  }
  void create(){
    useSlot = 0;
    vectorSaveData.clear();
    SaveDate saveDate;
    saveDate.mapLevel = 1;
    saveDate.mapClearStatus = 1;
    saveDate.exp =0;
    hasSaveFile_ = true;
    vectorSaveData.push_back(saveDate);
  }
  SaveDate& getInfo(){
    return vectorSaveData[useSlot];
  }
  void save(){
    save_();
  }
  bool hasSaveFile(){
    return hasSaveFile_;
  }
};

#endif // APPEAL_GAMEINFORMATION_HPP
