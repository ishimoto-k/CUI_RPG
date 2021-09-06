//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_BATTLESCENE_HPP
#define APPEAL_BATTLESCENE_HPP

#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>

#include "Command/Attack.hpp"
#include "Command/Escape.hpp"
#include <Player.hpp>

class BattleScene {
//  std::vector<std::shared_ptr<Command>> commandLists;
//  YAML::Node config = YAML::LoadFile("");
  std::shared_ptr<Player> player;
  std::vector<std::shared_ptr<CommandInterface>> commands = {
      std::make_shared<Attack>(),
      std::make_shared<Escape>(),
  };
public:
  BattleScene(){
  }
  void setPlayer(std::shared_ptr<Player> play){player = play;}
  int cursor = 0;
  void select(){
    commands[cursor]->select();
  }
  void view(){
    for(auto command = commands.begin();command!=commands.end();command++){
      if(std::distance(commands.begin(),command) == cursor){
        std::cout << "＞";
      }else{
        std::cout << "　";
      }
      std::cout<< (*command)->name() << std::endl;
    }
    std::cout<< "説明:" << std::endl;
    std::cout<< commands[cursor]->description() << std::endl;
  }
};

#endif // APPEAL_BATTLESCEAN_HPP
