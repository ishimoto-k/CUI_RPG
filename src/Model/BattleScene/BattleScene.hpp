//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_BATTLESCENE_HPP
#define APPEAL_BATTLESCENE_HPP

#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>

class BattleScene {
//  std::vector<std::shared_ptr<Command>> commandLists;
//  YAML::Node config = YAML::LoadFile("");
public:
  BattleScene(){
  }
  int cursor = 0;
  void view(){
    std::vector<std::string> commands = {
        "たたかう",
        "スキル",
    };
    for(auto command = commands.begin();command!=commands.end();command++){
      if(std::distance(commands.begin(),command) == cursor){
        std::cout << "＞";
      }else{
        std::cout << "　";
      }
      std::cout<< (*command) << std::endl;
    }
  }
};

#endif // APPEAL_BATTLESCEAN_HPP
