//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_BATTLESCENE_HPP
#define APPEAL_BATTLESCENE_HPP

#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <Observer.hpp>

#include "../GameSceneInterface.hpp"
#include "Command/Command.hpp"
#include <DummyEnemy.hpp>
#include <Enemy.hpp>
#include <Player.hpp>
using namespace Design;
enum class State{
  CommandSelect,
  SkillSelect,
  EnemySelect,
  Action,
  ESCAPE,
  Win,
  Lose,
};
class BattleScene:public GameSceneInterface{
public:
  class EventBody:public SubjectDataBody{
  public:
    State state;
    std::shared_ptr<Enemy> enemy = nullptr;
  };
private:
//  std::vector<std::shared_ptr<Command>> commandLists;
//  YAML::Node config = YAML::LoadFile("");
  std::shared_ptr<Player> player;
  std::shared_ptr<Enemy> enemy;
  std::vector<std::shared_ptr<CommandInterface>> commands = {
      std::make_shared<Attack>(),
      std::make_shared<Skill>(),
      std::make_shared<Escape>(),
  };
  std::vector<std::shared_ptr<CommandInterface>> selectList = commands;
  std::shared_ptr<CommandInterface> selection = commands[0];
  std::vector<std::string> log;
  State state = State::CommandSelect;
  int turnCounter = 1;
  int cursor = 0;
  bool isWin_ = false;
public:
  typedef std::shared_ptr<Character> CharacterPtr;
  BattleScene(){
  }
  virtual ~BattleScene(){

  }
  void setPlayer(std::shared_ptr<Player> playPtr);
  void setEnemy(std::shared_ptr<Enemy> enemyPtr);
  void action(CharacterPtr fromChara,CharacterPtr toChara,std::shared_ptr<CommandInterface> command);
  void Up() override;
  void Down() override;
  void Left() override;
  void Right()override;
  void Esc() override;
  void Cancel() override;
  void Select() override;
  void update() override;
  void view() override;
};

#endif // APPEAL_BATTLESCEAN_HPP
