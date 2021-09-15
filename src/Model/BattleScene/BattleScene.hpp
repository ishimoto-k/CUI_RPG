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
  CommandSelect, //コマンド選択画面
  SkillSelect,//スキル選択画面
  EnemySelect,//todo 敵を同時出現した時用。エネミー選択画面
  Action, //ターン処理中
  ESCAPE, //逃げる
  Win, //勝ち
  Lose, //負け
};
class BattleScene:public GameSceneInterface{
public:
  class EventBody:public SubjectDataBody{
    //イベント送信に必要なクラス
  public:
    State state;
    std::shared_ptr<Enemy> enemy = nullptr;
  };
private:
  std::shared_ptr<Player> player;//プレイヤー
  std::shared_ptr<Enemy> enemy;//エネミー
  std::vector<std::shared_ptr<CommandInterface>> commands = {//コマンド選択肢
      std::make_shared<Attack>(),
      std::make_shared<Skill>(),
      std::make_shared<Escape>(),
  };
  std::vector<std::shared_ptr<CommandInterface>> selectList = commands;//コマンド選択肢、表示用
  std::shared_ptr<CommandInterface> selection = commands[0]; //コマンド選択初期値
  std::vector<std::string> log;//バトルログ
  State state = State::CommandSelect;//バトルステータス
  int turnCounter = 1; //ターン経過数
  int cursor = 0; //カーソル位置
  bool isWin_ = false; //勝利?
public:
  typedef std::shared_ptr<Character> CharacterPtr;
  BattleScene(){
  }
  virtual ~BattleScene(){

  }
  void setPlayer(std::shared_ptr<Player> playPtr);
  void setEnemy(std::shared_ptr<Enemy> enemyPtr);
  void action(CharacterPtr fromChara,CharacterPtr toChara,std::shared_ptr<CommandInterface> command);
  void turnStart(CharacterPtr fromChara,CharacterPtr toChara);
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
