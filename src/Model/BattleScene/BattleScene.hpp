//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_BATTLESCENE_HPP
#define APPEAL_BATTLESCENE_HPP

#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <Observer.hpp>

#include "Command/Attack.hpp"
#include "Command/Escape.hpp"
#include <Player.hpp>
#include <Enemy.hpp>

using namespace Design;
enum State{
  CommandSelect,
  SkillSelect,
  EnemySelect,
  Action,
  ESCAPE,
  Win,
  Lose,
};
class BattleScene:public Subject{
public:
  class EventBody:public SubjectDataBody{
  public:
    State state;
  };
private:
//  std::vector<std::shared_ptr<Command>> commandLists;
//  YAML::Node config = YAML::LoadFile("");
  std::shared_ptr<Character> player;
  std::shared_ptr<Character> enemy;
  std::vector<std::shared_ptr<CommandInterface>> commands = {
      std::make_shared<Attack>(),
      std::make_shared<Skill>(),
      std::make_shared<Escape>(),
  };
  std::vector<std::shared_ptr<CommandInterface>> selectList = commands;
  std::shared_ptr<CommandInterface> selection = commands[0];
  std::vector<std::string> log;
  State state = CommandSelect;
  int turnCounter = 1;
public:
  BattleScene(){
  }
  void setPlayer(std::shared_ptr<Player> playPtr){player = playPtr;}
  void setEnemy(std::shared_ptr<Enemy> enemyPtr){enemy = enemyPtr;}
  int cursor = 0;
  void cursorUp(){
    cursor = cursor+1;
    if(selectList.size() == cursor)cursor = 0;
  }
  void cursorDown(){
    cursor = cursor-1;
    if(-1 == cursor)cursor = selectList.size()-1;
  }
  void action(std::shared_ptr<Character> fromChara,std::shared_ptr<Character> toChara,std::shared_ptr<CommandInterface> command){
    //todo ダメージ計算とHP減少
    log.push_back(fromChara->name()+"の"+command->name());
    log.push_back(toChara->name()+"に50のダメージ");
  }

  void update(){
    //戦闘ロジック
    if(state == Action){
      log.clear();//バトルログを消す
      action(player,enemy,selection);
      action(enemy,player,std::make_shared<Attack>());
      state = CommandSelect;
      turnCounter ++;
      selectList = commands;
      //ターン終了
    }
  }


  void cancel(){
    if(state == SkillSelect){
      state = CommandSelect;
      selectList = commands;
    }
    cursor = 0;
  }
  void select(){
    if(state == SkillSelect){
      auto skill = selectList[cursor];
      selection = skill;
      state = Action;
    }else {
      auto command = commands[cursor];
      switch (command->id()) {
      case 1:
        selectList = commands;
        cursor = 0;
        selection = commands[0];
        state = Action;
        break;
      case 2:
        cursor = 0;
        state = SkillSelect;
        selectList = player->skill;
        break;
      case 3:
        cursor = 0;
        selection = commands[2];
        state = ESCAPE;
        auto body = std::make_shared<EventBody>();
        body->state = state;
        notify(ObserverEventList::BATTLE_SCENE_ESCAPE,body);
        break;
      }
    }
  }
  void view(){
    std::cout << enemy->frontView() << std::endl;
    std::cout << enemy->name() << std::endl << " HP:" << enemy->parameter.maxHP  << "/" << enemy->HP << std::endl;
    std::cout << player->name() << std::endl << " HP:" << player->parameter.maxHP  << "/" << player->HP << " ";
    std::cout << "MP:" << player->parameter.maxMP  << "/" << player->MP << std::endl << std::endl;
    if(state == CommandSelect || state == SkillSelect){
      if(state == SkillSelect)
        std::cout << "スキル" << std::endl;
      if(state == CommandSelect)
        std::cout << "コマンド" << std::endl;
      for(auto command = selectList.begin();command!=selectList.end();command++){
        if(state == SkillSelect)
          std::cout << "　";
        if(std::distance(selectList.begin(),command) == cursor){
          std::cout << "＞";
        }else{
          std::cout << "　";
        }
        std::cout<< (*command)->name() << std::endl;
      }
      std::cout<< "説明:" << std::endl;
      std::cout<< "　" <<selectList[cursor]->description() << std::endl;
    }else if(state == EnemySelect){//todo select enemy
      std::cout << "どの敵" << std::endl;
    }
    std::cout<< std::endl <<"バトルログ:" << std::endl;
    for(auto l:log){
      std::cout <<"　"<< l << std::endl;
    }
  }
};

#endif // APPEAL_BATTLESCEAN_HPP
