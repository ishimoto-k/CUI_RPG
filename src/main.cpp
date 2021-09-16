//
// Created by IshimotoKiko on 2021/09/03.
//

#include "../src/Model/Character/DummyEnemy.hpp"
#include "../src/Model/Map/MapScene.hpp"
#include "Model/BattleScene/BattleScene.hpp"
#include "Model/GameSeaneStatus.hpp"
#include <DungeonCreate.hpp>
#include <KeyBoardController.hpp>
#include <Title.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <Defines.hpp>
#include "GameInformation.hpp"

int main(){
  //ゲームの設定ファイルの存在確認
  if(!define::haveConfigFileCheck()){
    std::cout << "ゲームを起動できませんでした。" << std::endl;
    return -1;
  }
  //ゲームのセーブデータの読み込み
  GameInformation gameInformation;
  //スロット0を使用。セーブスロットは増やせるようにしている。
  gameInformation.setSlot(0);
  //キー入力の値(enum)
  Key key = Key::NONE;
  //オブザーバー(イベントリスナー)
  Observer observer;

  //ゲームステータスの生成　初めはタイトル画面
  GameSeaneStatus gameStatus = GameSeaneStatus::TITLE;
  //前回の画面ステータスを保持
  GameSeaneStatus prevGameStatus = gameStatus;
  //キーボード入力コントローラーの生成
  KeyBoardController keyBoardController;
  //タイトルシーン、マップシーン、バトルシーンを生成しておく
  //後述のgameSceneに代入することでロジックを変化させる
  auto titleScene = std::make_shared<Title>();
  auto mapScene = std::make_shared<MapScene>();
  auto battleScene = std::make_shared<BattleScene>();
  std::vector<std::string> log;
  std::shared_ptr<Player> player = nullptr;

  //タイトル画面のロジックに切り替え
  std::shared_ptr<GameSceneInterface> gameScene = titleScene; //起動時はタイトル画面
  //セーブデータが存在すれば、タイトルのカーソルを「つづきから」に位置する
  if(gameInformation.hasSaveFile()){
    titleScene->setCursor(Title::SelectList::LOAD);
  }
  //イベントハンドラーの実装
  observer.interface(std::make_shared<ObserverInterface>());
  observer.interface()->addListener(ObserverEventList::MAP_SCENE_PLAYER_CollisionDetection,[&](SubjectData subject){
    //プレイヤーがオブジェクトに接触
    auto msg = static_cast<MapScene::EventBody*>(subject.get());
    //オブジェクトはエネミーの場合
    if(msg->bit == BitMapKind::ENEMY){
      if(gameStatus != GameSeaneStatus::BATTLE){
        log.emplace_back("敵と遭遇した");
        //バトルシーンにプレイヤーとエネミーをセット
        battleScene->setPlayer(player);
        battleScene->setEnemy(mapScene->getEnemyFromPos(msg->toPosition));
        //ゲームステータスをバトルに変更
        gameStatus = GameSeaneStatus::BATTLE;
      }
    }
//    std::cout << "object collision detection bit = "<< msg->bit << std::endl;
  });
  observer.interface()->addListener(ObserverEventList::MAP_SCENE_ENEMY_CollisionDetection,[&](SubjectData subject){
    auto msg = static_cast<MapScene::EventBody*>(subject.get());
    return;
//    std::cout << "enemy was object collision detection bit = "<< msg->bit << std::endl;
  });
  observer.interface()->addListener(ObserverEventList::KEYBOARD_ON_INPUT,[&](SubjectData subject){
    auto msg = static_cast<UserControllerInterface::EventBody*>(subject.get());
    //キーボード入力があるとイベント発火
    //keyBoardWaitをhitに変更
    gameStatus.keyBoardWait = KeyBoardWait::HIT;
    //keyの値を代入(enum)
    key = msg->key;
  });
  observer.interface()->addListener(ObserverEventList::TITLE_SCENE_ON_SELECT,[&](SubjectData subject){
    //タイトル画面で決定を押した時のイベント
    auto msg = static_cast<Title::EventBody*>(subject.get());
    if(msg->selectList == Title::SelectList::START){
      //「はじめから」を選択
      gameInformation.create();//ゲーム情報の初期化
      //ダンジョン生成
      mapScene->makeDungeon(gameInformation.getInfo().mapLevel);
      //プレイヤーを適当に配置
      auto pos = mapScene->getRandomNonePosition();
      player = std::make_shared<Player>(pos.x,pos.y,0);
      mapScene->setPlayerAndCreateMapObject(player,false);
      //ゲームステータスをマップに変更
      gameStatus = GameSeaneStatus::MAP_VIEW;
    }else if(msg->selectList == Title::SelectList::LOAD){
      //セーブデータからロードした情報をもとにダンジョンを生成
      mapScene->makeDungeon(gameInformation.getInfo().mapLevel);
      auto pos = mapScene->getRandomNonePosition();
      player = std::make_shared<Player>(pos.x,pos.y,gameInformation.getInfo().exp);
      mapScene->setPlayerAndCreateMapObject(player,false);
      //ゲームステータスをマップに変更
      if(gameInformation.getInfo().mapClearStatus > gameInformation.getInfo().mapLevel){
        mapScene->eraseBoss();
      }
      gameStatus = GameSeaneStatus::MAP_VIEW;
    }else if(msg->selectList == Title::SelectList::END){
      //ゲームステータスを終了に変更
      gameStatus = GameSeaneStatus::GAME_OVER;
    }
  });

  observer.interface()->addListener(ObserverEventList::BATTLE_SCENE_ESCAPE,[&](SubjectData subject){
    //戦闘から逃げる
    auto msg = static_cast<BattleScene::EventBody*>(subject.get());
//    std::cout << "BATTLE_SCENE_ESCAPE ";
    gameStatus = GameSeaneStatus::MAP_VIEW;
  });
  observer.interface()->addListener(ObserverEventList::BATTLE_SCENE_WIN,[&](SubjectData subject){
    //    std::cout << "BATTLE_SCENE_WIN ";
    //戦闘で勝利
    auto msg = static_cast<BattleScene::EventBody*>(subject.get());
    //todo -> done 倒した敵情報をsharedで取得し、削除する。mapSeaneが削除する。

    //ゲームステータスをマップにする。z
    gameStatus = GameSeaneStatus::MAP_VIEW;
    if(!mapScene->eraseEnemy(msg->enemy)){
      //エネミーを消す
      mapScene->eraseBoss();
    }
  });
  observer.interface()->addListener(ObserverEventList::BATTLE_SCENE_LOSE,[&](SubjectData subject){
    //    std::cout << "BATTLE_SCENE_LOSE ";
    //戦闘で敗北
    //ゲームステータスをタイトルにする。
    auto msg = static_cast<BattleScene::EventBody*>(subject.get());
    gameStatus = GameSeaneStatus::TITLE;
  });

  observer.interface()->addListener(ObserverEventList::MAP_SCENE_SELECT_WARP_START,[&](SubjectData subject){
//    std::cout << "MAP_SCENE_SELECT_WARP_START ";
    //マップシーンで出口ワープを選択した
    if(gameInformation.getInfo().mapLevel == 1){
      //階層１の場合は戻れない
      log.emplace_back("これ以上もどれません");
      return;
    }
    //階層移動したタイミングで保存する。
    gameInformation.getInfo().mapLevel = gameInformation.getInfo().mapLevel-1; //階層-1
    gameInformation.getInfo().exp = player->parameter.EXP;
    gameInformation.save();
    log.push_back("セーブが完了しました");
    //ダンジョンを作り直す。
    mapScene->makeDungeon(gameInformation.getInfo().mapLevel);
    auto pos = mapScene->getRandomNonePosition();
    player->set(pos);
    mapScene->setPlayerAndCreateMapObject(player,true);
    //攻略済みのダンジョンはボスを消す。
    if(gameInformation.getInfo().mapClearStatus >= gameInformation.getInfo().mapLevel){
      mapScene->eraseBoss();
    }
  });
  observer.interface()->addListener(ObserverEventList::MAP_SCENE_SELECT_WARP_GOAL,[&](SubjectData subject){
//    std::cout << "MAP_SCENE_SELECT_WARP_GOAL ";
    //マップシーンで入り口ワープを選択した
    gameInformation.getInfo().mapLevel =gameInformation.getInfo().mapLevel +1;
    if(gameInformation.getInfo().mapClearStatus < gameInformation.getInfo().mapLevel){
      gameInformation.getInfo().mapClearStatus = gameInformation.getInfo().mapLevel;
    }
    if(gameInformation.getInfo().mapLevel > MapInformation::getMapInfoList().size()){
      //最終マップの場合はクリア
      log.emplace_back("ゲームクリア");
      gameInformation.getInfo().mapLevel = MapInformation::getMapInfoList().size();
      gameInformation.getInfo().mapClearStatus = gameInformation.getInfo().mapLevel+1;
      gameInformation.getInfo().exp = player->parameter.EXP;
      gameInformation.save();
      return;
    }
    //階層移動したタイミングで保存する。
    gameInformation.getInfo().exp = player->parameter.EXP;
    gameInformation.save();
    //ダンジョンを作り直す。
    mapScene->makeDungeon(gameInformation.getInfo().mapLevel);
    auto pos = mapScene->getRandomNonePosition();
    player->set(pos);
    mapScene->setPlayerAndCreateMapObject(player,false);
    //攻略済みのダンジョンはボスを消す。
    if(gameInformation.getInfo().mapClearStatus > gameInformation.getInfo().mapLevel){
      mapScene->eraseBoss();
    }
  });

  //オブザーバーの登録
  titleScene->addObserver(observer);
  keyBoardController.addObserver(observer);
  keyBoardController.startInputMonitoring();
  battleScene->addObserver(observer);
  mapScene->addObserver(observer);
  Vector2 pos = Vector2::NONE;

  std::string operation = "\n移動：WASD\nセレクト：Z  キャンセル:X";
  printf("\033[;H\033[2J");//画面クリア
  gameScene->view();
  //ゲーム操作方法を表示
  std::cout << operation << std::endl;

  for(int i=0;gameStatus != GameSeaneStatus::GAME_OVER;i++) {
    //    system("clear");
    while (1) { /* キーが押されるまで待つ */
      if (gameStatus.keyBoardWait != KeyBoardWait::WAIT) {
        break;
      }
      std::this_thread::yield();
    }
    if(prevGameStatus != gameStatus){
      prevGameStatus = gameStatus;
      log.clear();
      continue;
    }

    //ゲームシーンにキーコマンドを命令
    if (key == Key::UP) {
      gameScene->Up();
    } else if (key == Key::DOWN) {
      gameScene->Down();
    } else if (key == Key::RIGHT) {
      gameScene->Right();
    } else if (key == Key::LEFT) {
      gameScene->Left();
    } else if (key == Key::SELECT) {
      gameScene->Select();
    } else if (key == Key::CANCEL) {
      gameScene->Cancel();
    } else if (key == Key::ESC) {
      gameScene->Esc();
      gameStatus = GameSeaneStatus::GAME_OVER;
    }
    key = Key::NONE;
    gameStatus.keyBoardWait = KeyBoardWait::WAIT;
    printf("\033[;H\033[2J");

    if (gameStatus == GameSeaneStatus::TITLE) {
      //ゲームステータスがタイトルなら、ゲームシーンをタイトルシーンに変更
      gameScene = titleScene;
    } else if (gameStatus == GameSeaneStatus::MAP_VIEW) {
      //ゲームステータスがマップなら、ゲームシーンをマップシーンに変更
      gameScene = mapScene;
    } else if (gameStatus == GameSeaneStatus::BATTLE) {
      //ゲームステータスが戦闘なら、ゲームシーンをバトルシーンに変更
      gameScene = battleScene;
    } else if (gameStatus == GameSeaneStatus::GAME_OVER) {
      //ゲームステータスが終了なら、終了する。
      break;
    }
    //ロジック処理
    gameScene->update();
    //表示処理
    gameScene->view();


    //ゲームログを出力
    for (auto i : log) {
      std::cout << i << std::endl;
    }
    log.clear();

    //ゲーム操作方法を表示
    std::cout << operation << std::endl;
  }
  std::cout << "ゲーム終了" << std::endl;
  keyBoardController.stopInputMonitoring();//スレッド終了
}