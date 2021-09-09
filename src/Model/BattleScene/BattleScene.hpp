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
#include <DummyEnemy.hpp>

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
  void setEnemy(std::shared_ptr<DummyEnemy> enemyPtr){enemy = enemyPtr;}
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
    command->update(fromChara->name(),toChara->name(),fromChara->parameter,toChara->parameter,&log);
//    log.push_back(fromChara->name()+"の"+command->name());
//    log.push_back(toChara->name()+"に50のダメージ");
  }

  void update() {
    //戦闘ロジック
    if (state == Action) {
      log.clear(); //バトルログを消す
      action(player, enemy, selection);
      if (enemy->parameter.HP <= 0) {
        enemy->parameter.HP = 0;
        auto body = std::make_shared<EventBody>();
        log.push_back(enemy->name()+"を倒した");
        log.push_back(std::to_string(enemy->parameter.EXP)+"の経験値を獲得した");
        auto tmpSkillSize = player->skill.size();
        if(player->addExp(enemy->parameter.EXP)){
          log.push_back(player->name()+"はレベルアップし、");
          log.push_back(std::to_string(player->parameter.level)+"になった");
          if(tmpSkillSize < player->skill.size()){
            for(auto skill = player->skill.begin()+(tmpSkillSize-1); skill!=player->skill.end();skill++){
              log.push_back((*skill)->name()+"を覚えた");
            }
          }
        }
        body->state = Win;
        notify(ObserverEventList::BATTLE_SCENE_WIN, body);
        goto finish;
      }
      action(enemy, player, std::make_shared<Attack>());
      if (player->parameter.HP <= 0) {
        player->parameter.HP = 0;
        auto body = std::make_shared<EventBody>();
        log.push_back(player->name()+"は敗北した");
        body->state = Lose;
        notify(ObserverEventList::BATTLE_SCENE_LOSE, body);
        goto finish;
      }
    finish:
      state = CommandSelect;
      turnCounter++;
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
      if(player->parameter.MP >= skill->mp()){
        selection = skill;
        state = Action;
      }else{
        log.clear();
        log.push_back("MPが足りない");
      }
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
        log.clear();
        log.push_back("戦闘から離脱しました");
        auto body = std::make_shared<EventBody>();
        body->state = state;
        notify(ObserverEventList::BATTLE_SCENE_ESCAPE,body);
        break;
      }
    }
  }
  void view(){
    std::cout << std::endl << enemy->frontView() << std::endl;
    std::cout << enemy->name() << std::endl << " HP:" << enemy->parameter.maxHP  << "/" << enemy->parameter.HP << std::endl;
    std::cout << player->name() << std::endl << " HP:" << player->parameter.maxHP  << "/" << player->parameter.HP << " ";
    std::cout << "MP:" << player->parameter.maxMP  << "/" << player->parameter.MP << std::endl << std::endl;
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
        std::cout<< (*command)->name() ;
        if(state == SkillSelect) {
          if(player->parameter.MP < (*command)->mp()){
            std::cout << "　" << "\t\033[2m"<< (*command)->mp() << "\033[0m" << std::endl;
          }else{
            std::cout << "　\t" << (*command)->mp() <<  std::endl;
          }
        }else{
          std::cout << std::endl;
        }
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
