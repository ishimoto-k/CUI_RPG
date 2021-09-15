//
// Created by IshimotoKiko on 2021/09/03.
//

#include "MapScene.hpp"
#include "HealPoint.hpp"

void MapScene::makeDungeon(int level) {
  //ダンジョン生成と敵の生成及び配置を行う。
  mapInfo = MapInformation::getMapInfo(level - 1);//configファイルからマップ情報を読み込む。
  setDungeon(std::make_shared<DungeonCreate>(mapInfo.width, mapInfo.height, mapInfo.roomsMin, mapInfo.roomsMax));//ダンジョン生成アルゴリズムを委譲し生成
  enemies.clear();//敵をクリア
  buildEnemies();//敵を生成
  setEnemy(enemies);//生成した敵を格納
  for(auto i = 0; i < mapInfo.heal;i++){//回復スポットを生成
    auto pos = getRandomNonePosition();
    auto heal = std::make_shared<HealPoint>(pos.x,pos.y);
    heal->setOnSelectCallback([this,heal](){
      //回復スポットに触れたときの処理
      if(heal->use()){
        log.emplace_back("回復スポットに触れた。");
        log.emplace_back("しかし何も起きなかった。");
        return;
      }
      //HPとMPを回復
      player->parameter.HP = player->parameter.maxHP;
      player->parameter.MP = player->parameter.maxMP;
      heal->use(true);//使用したので次は使えなくする。マップ移動すると復活しますが。。
      log.emplace_back("回復スポットに触れた。");
      log.emplace_back("\033[32m全回復\033[39mした。");
    });
    drawBitMap[pos.y][pos.x] = BitMapKind::MAPOBJECT;//回復スポットの座標をマップオブジェクトに変更
    mapObjects.push_back(heal);
  }
}
void MapScene::buildEnemies() {
  std::random_device seed_gen;
  std::mt19937 engine{seed_gen()};
  int size = mapInfo.typeOfEnemy.size();//マップ情報から出現する敵の種類を取得
  for (int i = enemies.size(); i < mapInfo.enemies; i++) {
    auto enemy = Enemy::create(mapInfo.typeOfEnemy[engine() % size]);/*ランダムに種類を選択し敵を生成*/
    auto pos = getRandomNonePosition();
    drawBitMap[pos.y][pos.x] = BitMapKind::ENEMY;//敵を配置
    enemy->set(pos);
    enemies.push_back(enemy);
  }
}
bool MapScene::eraseEnemy(std::shared_ptr<Enemy> enemy) {
  //敵を削除
  for (auto en = enemies.begin(); en != enemies.end(); en++) {
    if ((*en)->getIdx() == enemy->getIdx()) {
      auto pos = (*en)->position();
      drawBitMap[pos.y][pos.x] = BitMapKind::NONE;
      log.push_back("敵を倒しました。");
      enemies.erase(en);
      return true;
    }
  }
  return false;
}
bool MapScene::eraseBoss(){
  //ボスを削除
  if(boss) {
    auto pos = (boss)->position();
    drawBitMap[pos.y][pos.x] = BitMapKind::NONE;
    boss = nullptr;
    return true;
  }
  return false;
}
void MapScene::setDungeon(std::shared_ptr<DungeonInterfece> dungeonPtr) {
  //ダンジョンの生成を行います。
  dungeon = dungeonPtr;
  dungeon->create();
//  dungeon->debug();
  mapObjects.clear(); //マップオブジェクトをクリア
  nonePlacePosition.clear();//道リストをクリア
  auto bitmap = dungeon->getBitMap();
  for (int y = 0; y < bitmap.size(); y++) {
    for (int x = 0; x < bitmap[y].size(); x++) {
      if (bitmap[y][x] != BitMapKind::WALL) {
        //道の座標をリストに格納
        nonePlacePosition.emplace_back(x, y);
      }
    }
  }
  drawBitMap = dungeon->getBitMap();
}
void MapScene::setEnemy(std::vector<std::shared_ptr<Enemy>> enemyPtr) {
  enemies = enemyPtr;
}
void MapScene::setPlayerAndCreateMapObject(std::shared_ptr<Player> playerPtr,bool direction) {
  player = playerPtr;

  //プレイヤーの座標上にスタート地点を生成
  auto warp_s = std::make_shared<Warp>(player->position().x,player->position().y, !direction);
  warp_s->setOnSelectCallback([this,direction](){
    //ワープを選択したときの処理
    if(!direction) {
      notify(ObserverEventList::MAP_SCENE_SELECT_WARP_START);
    }else{
      notify(ObserverEventList::MAP_SCENE_SELECT_WARP_GOAL);
    }
  });
  drawBitMap[player->position().y][player->position().x] = BitMapKind::MAPOBJECT;
  mapObjects.push_back(warp_s);

  //ゴール地点を生成
  auto pos = getRandomNonePosition();
  auto warp_f = std::make_shared<Warp>(pos.x,pos.y, direction);
  warp_f->setOnSelectCallback([this,direction](){
    if(direction) {
      notify(ObserverEventList::MAP_SCENE_SELECT_WARP_START);
    }else{
      notify(ObserverEventList::MAP_SCENE_SELECT_WARP_GOAL);
    }
  });
  drawBitMap[pos.y][pos.x] = BitMapKind::MAPOBJECT;
  mapObjects.push_back(warp_f);

  //ボスを生成
  //マップ情報にボスの存在があれば、生成を行う。
  boss = nullptr;
  if(mapInfo.boss != 0){
    boss = Enemy::create(mapInfo.boss);
    boss->set(pos);
    drawBitMap[pos.y][pos.x] = BitMapKind::ENEMY;
    boss->setBoss();
  }
}
std::shared_ptr<Enemy> MapScene::getEnemyFromPos(Vector2 pos) {
  //座標から敵を取得
  for (auto enemy : enemies) {
    if (enemy->position() == pos) {
      return enemy;
    }
  }
  if(boss){
    if (boss->position() == pos) {
      return boss;
    }
  }
  return nullptr;
}

Vector2 MapScene::getRandomNonePosition() {
  //道リストから、ランダムに道座標を取得
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::shuffle(nonePlacePosition.begin(), nonePlacePosition.end(), engine);
  auto itr = nonePlacePosition.begin();
  for(;itr!=nonePlacePosition.end();itr++){
    if(drawBitMap[itr->y][itr->x]  == NONE){
      return *itr;
    }
  }
  return *itr;
}
void MapScene::setPlayerDirection(Vector2 dir) { playerDirection = dir; }
void MapScene::Up() { setPlayerDirection(Vector2::UP); } /*上に進む*/
void MapScene::Down() { setPlayerDirection(Vector2::DOWN); } /*下に進む*/
void MapScene::Left() { setPlayerDirection(Vector2::LEFT); } /*左に進む*/
void MapScene::Right() { setPlayerDirection(Vector2::RIGHT); } /*右に進む*/
void MapScene::Select() { /*セレクト*/
  //プレイヤーの座標にマップオブジェクトが存在するかを確認
  auto ptr = std::find_if(mapObjects.begin(),mapObjects.end(),[this](ObjectPtr objectPtr){
    return player->position() == objectPtr->position();
  });
  if(ptr != mapObjects.end()) {
    //存在すれば、オブジェクトのselectを呼び出す。
    //オブジェクト生成時に、設定したコールバックが呼び出される。
    (*ptr)->select();
  }
}
void MapScene::Cancel() {}
void MapScene::Esc() {}
void MapScene::update() {
  static int count = 0;
  auto pos = player->position();
  drawBitMap[pos.y][pos.x] = BitMapKind::NONE;//プレイヤーのいた座標を道にする。
  bool collisionCheck = player->move(drawBitMap, playerDirection,[this](BitMapKind bitmap, Vector2 toPos, Vector2 fromPos) {
        auto body = std::make_shared<EventBody>();
        body->bit = bitmap;
        body->toPosition = toPos;
        body->fromPosition = fromPos;
        notify(ObserverEventList::MAP_SCENE_PLAYER_CollisionDetection, body);
      }); //最初にプレイヤーを動かす　//Objectに衝突するとイベント発生する
  pos = player->position();
  drawBitMap[pos.y][pos.x] = BitMapKind::PLAYER;//プレイヤーが動いた後の座標をPLAYERにする。
  if (!collisionCheck) {
    for (auto enemy : enemies) { //次にエネミーを動かす　//Objectに衝突するとイベント発生する
      auto pos = enemy->position();
      drawBitMap[pos.y][pos.x] = BitMapKind::NONE;//エネミーのいた座標を道にする。
      enemy->move(drawBitMap, [this](BitMapKind bitmap, Vector2 toPos,Vector2 fromPos) {
        auto body = std::make_shared<EventBody>();
        body->bit = bitmap;
        body->toPosition = toPos;
        body->fromPosition = fromPos;
        notify(ObserverEventList::MAP_SCENE_ENEMY_CollisionDetection, body);
      });
      pos = enemy->position();
      drawBitMap[pos.y][pos.x] = BitMapKind::ENEMY;//エネミーが動いた後の座標をPLAYERにする。
    }
  }
  if(boss){
    //ボスは移動しない。
    auto pos = boss->position();
    drawBitMap[pos.y][pos.x] = BitMapKind::ENEMY;
  }
  setPlayerDirection(Vector2::NONE);//プレイヤーは移動したので、DirectionはNONEにセット
  if (count % 10 == 0) {
    //10フレーム度にエネミーが復活する。
    buildEnemies();
  }
  count++;
}
void MapScene::view() {
  std::cout << "第" << mapInfo.level << "階層" << std::endl;
  for (int y = 0; y < drawBitMap.size(); y++) {
    for (int x = 0; x < drawBitMap[y].size(); x++) {
      std::shared_ptr<MapObjectInterface> tmpObject = nullptr;
      for(auto object: mapObjects){
        //MapObjectは背景色をつける
        if(Vector2(x,y) == object->position()){
          object->backViewStart();
          tmpObject = object;
          break;
        }
      }
      bool check = false;
      for (auto enemy : enemies) {
        if (Vector2(x, y) == enemy->position()) {
          enemy->view();
          check = true;
          continue;
        }
      }
      if(boss) {
        if (Vector2(x, y) == boss->position()) {
          boss->view();
        }
      }
      if (check);//敵の表示を行なった
      else if (Vector2(x, y) == player->position()) {//プレイヤーの表示を行う
        player->view();
      }
      else if (drawBitMap[y][x] == WALL) /* 移動不可能*/
        printf("\033[41m　\033[49m");     /* ←全角スペース */
      else if (drawBitMap[y][x] == NONE || drawBitMap[y][x] == BitMapKind::MAPOBJECT)
        printf("　");/* ←全角スペース */

      if(tmpObject){
        //背景色を戻す
        tmpObject->backViewEnd();
      }
    }
    std::cout << std::endl;
  }

  //最後ステータスやゲームログを出力
  std::cout << player->name() << std::endl;
  std::cout << " LV:" <<player->parameter.level << "\t";
  std::cout << " HP:" << player->parameter.maxHP << "/" << player->parameter.HP << "\t";
  std::cout << "MP:" << player->parameter.maxMP << "/" << player->parameter.MP << std::endl;
  std::cout << " POW:" << player->parameter.POW << "\t DEX:" << player->parameter.DEX << std::endl;
  std::cout << " EXP:" << player->parameter.EXP ;
  if(player->parameter.level != Parameter::getLevelList().size()){
    std::cout << "\t 次のレベルまで:" <<player->parameter.targetEXP-player->parameter.EXP << std::endl;
  }else{
    std::cout << std::endl;
  }
  for (auto l : log) {
    std::cout << l << std::endl;
  }
  log.clear();
}
