//
// Created by IshimotoKiko on 2021/09/05.
//

#include "BattleScene.hpp"
#include <thread>

void BattleScene::setPlayer(std::shared_ptr<Player> playPtr) {
  //プレイヤーの登録
  player = playPtr;
  player->initBattleBefore();//パラメーター初期化

  //コマンドセレクト画面
  state = State::CommandSelect;
  //ターン1
  turnCounter = 1;
  log.clear();
  isWin_ = false;
}
void BattleScene::setEnemy(std::shared_ptr<Enemy> enemyPtr) {
  //エネミー登録
  enemy = enemyPtr;
  enemy->initBattleBefore();//パラメーター初期化
}

void BattleScene::Up() {
  cursor = cursor - 1;
  if (-1 == cursor)
    cursor = selectList.size() - 1;
}
void BattleScene::Down(){
  cursor = cursor + 1;
  if (selectList.size() == cursor)
    cursor = 0;
}

void BattleScene::action(std::shared_ptr<Character> fromChara,
                         std::shared_ptr<Character> toChara,
                         std::shared_ptr<CommandInterface> command) {
  // コマンドアクション
  command->update(fromChara->name(), toChara->name(), fromChara->parameter,
                  toChara->parameter, &log);
}

void BattleScene::turnStart(CharacterPtr fromChara, CharacterPtr toChara) {
  // ターン開始
  fromChara->battleTurnStart(toChara,log);
}
void BattleScene::Left(){}
void BattleScene::Right(){};
void BattleScene::Esc(){};

void BattleScene::update() {
  //戦闘ロジック
  auto body = std::make_shared<EventBody>();
  if (state == State::Action) {//ターン処理
    log.clear(); //バトルログを消す

    player->initTurnBefore();//プレイヤーの守備力、攻撃力を一旦戻す。

    turnStart(player, enemy);//状態異常を反映
    if (enemy->parameter.HP <= 0) {
      goto win;
    }
    if (player->parameter.HP <= 0) {
      goto lose;
    }
    action(player, enemy, selection);//スキル実行
    if (enemy->parameter.HP <= 0) {
      goto win;
    }
    if (player->parameter.HP <= 0) {
      goto lose;
    }
    enemy->initTurnBefore();//敵の守備力、攻撃力を一旦戻す。
    turnStart(enemy,player);//状態異常を反映
    if (enemy->parameter.HP <= 0) {
      goto win;
    }
    if (player->parameter.HP <= 0) {
      goto lose;
    }
    action(enemy, player, enemy->battleLogic(turnCounter,player->parameter));//バトルロジックよりコマンドが選択される。
    if (enemy->parameter.HP <= 0) {
      goto win;
    }
    if (player->parameter.HP <= 0) {
      goto lose;
    }
    goto finish;
  win:
    //goto win　敵のHPを0にした時
    enemy->parameter.HP = 0;
    log.push_back("\033[4m\033[1m" + enemy->name() + "を倒した" +
                  "\033[0m");
    log.push_back(std::to_string(enemy->parameter.EXP) +
                  "の経験値を獲得した");
    if (player->addExp(enemy->parameter.EXP)) {//経験値UP
      log.push_back(player->name() + "はレベルアップし、");
      log.push_back(std::to_string(player->parameter.level) + "になった");
      auto info = player->getGotSkills();
      if (!info.empty()) {
        for (auto skill = info.begin(); skill != info.end(); skill++) {
          log.push_back((*skill)->name() + "を覚えた");
        }
      }
    }
    isWin_ = true;
    body->state = State::Win;
    body->enemy = enemy;
    notify(ObserverEventList::BATTLE_SCENE_WIN, body);//勝利イベント
    goto finish;
  lose:
    //goto lose　プレイヤーのHPを0にした時
    player->parameter.HP = 0;
    log.push_back(player->name() + "は敗北した");
    body->state = State::Lose;
    notify(ObserverEventList::BATTLE_SCENE_LOSE, body);//敗北イベント
  finish:
    //　終了処理
    state = State::CommandSelect;
    turnCounter++;
    selectList = commands;
    cursor = 0;
    return;
    //ターン終了
  }
}

void BattleScene::Cancel() {
  if (state == State::SkillSelect) {
    state = State::CommandSelect;
    selectList = commands;
  }
  cursor = 0;
}
void BattleScene::Select() {
  if (state == State::SkillSelect) {
    auto skill = selectList[cursor];
    if (player->parameter.MP >= skill->mp()) {
      //持っているMPがスキルの消費MP足りていれば発動
      selection = skill;
      state = State::Action;
    } else {
      log.clear();
      log.emplace_back("MPが足りない");
    }
  } else {
    auto command = commands[cursor];
    switch (command->id()) {
    case static_cast<int>(TypeOfSkills::ATTACK): //ATTACK
      selectList = commands;
      cursor = 0;
      selection = commands[0];
      state = State::Action;
      break;
    case static_cast<int>(TypeOfSkills::SKILL): //SKILL
      cursor = 0;
      state = State::SkillSelect;
      selectList = player->skill;
      break;
    case static_cast<int>(TypeOfSkills::ESCAPE): //ESCAPE
      cursor = 0;
      selection = commands[2];
      state = State::ESCAPE;
      log.clear();
      log.emplace_back("戦闘から離脱しました");
      auto body = std::make_shared<EventBody>();
      body->state = state;
      notify(ObserverEventList::BATTLE_SCENE_ESCAPE, body);
      break;
    }
  }
}

void BattleScene::view() {
  //敵の絵を表示
  std::cout << std::endl << enemy->frontView() << std::endl;
  //敵のパラメーター
  std::cout << enemy->name() << std::endl
            << " HP:" << enemy->parameter.maxHP << "/" << enemy->parameter.HP
            << std::endl;
  //プレイヤーのパラメーター
  std::cout << player->name() << std::endl
            << " HP:" << player->parameter.maxHP << "/"
            << player->parameter.HP << " ";
  std::cout << "MP:" << player->parameter.maxMP << "/" << player->parameter.MP
            << std::endl
            << std::endl;
  if (state == State::CommandSelect || state == State::SkillSelect) {
    if (state == State::SkillSelect)
      std::cout << "スキル" << std::endl;
    if (state == State::CommandSelect)
      std::cout << "コマンド" << std::endl;
    for (auto command = selectList.begin(); command != selectList.end();
         command++) {
      if (state == State::SkillSelect)
        std::cout << "　";
      if (std::distance(selectList.begin(), command) == cursor) {
        std::cout << "＞";
      } else {
        std::cout << "　";
      }
      std::cout << (*command)->name();
      if (state == State::SkillSelect) {
        if (player->parameter.MP < (*command)->mp()) {
          //MP足りない場合は灰色文字
          std::cout << "\t\033[2m" << (*command)->mp() << "\033[0m" << std::endl;
        } else {
          std::cout << "\t" << (*command)->mp() << std::endl;
        }
      } else {
        std::cout << std::endl;
      }
    }
    std::cout << "説明:" << std::endl;
    std::cout << "　" << selectList[cursor]->description() << std::endl;
  } else if (state == State::EnemySelect) { // todo select enemy
    std::cout << "どの敵" << std::endl;
  }
  std::cout << std::endl << "バトルログ:" << std::endl;
  for (auto l : log) {
    std::cout << "　" << l << std::endl;
  }
  if(isWin_){
    //勝利時は若干waitを入れ、キーボードの入力を無効にする。
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}