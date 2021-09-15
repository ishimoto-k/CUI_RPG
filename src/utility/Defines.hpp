//
// Created by IshimotoKiko on 2021/09/13.
//

#ifndef APPEAL_DEFINES_HPP
#define APPEAL_DEFINES_HPP
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <vector>
namespace define{

//設定ファイルのパス
//実行パスからの相対パス
static std::string AssetsTitle(){
  return "assets/title";
}
static std::string AssetsCharacter(){
  return "assets/character.yaml";
}
static std::string AssetsLevelList(){
  return "assets/LevelList.yaml";
}
static std::string AssetsMapInformation(){
  return "assets/mapInformation.yaml";
}

//設定ファイルのチェック
static bool haveConfigFileCheck(){
  std::vector<std::string> checkList={
      AssetsTitle(),
      AssetsCharacter(),
      AssetsLevelList(),
      AssetsMapInformation()
  };
  for(auto filename:checkList){
    std::ifstream ifs(filename);
    std::cout <<filename<< "の存在を確認中  ";
    if(!ifs){
      std::cout << "・・・NG　存在しませんでした。" << std::endl;
      return false;
    }
    std::cout << std::endl << "・・・\033[44mOK\033[49m " << std::endl;
  }
  return true;
}
}
#endif // APPEAL_DEFINES_HPP
