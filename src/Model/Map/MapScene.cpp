//
// Created by IshimotoKiko on 2021/09/03.
//

#include "MapScene.hpp"

void MapScene::makeDungeon(int level) {
  mapInfo = MapInformation::getMapInfo(level - 1);
  setDungeon(std::make_shared<DungeonCreate>(
      mapInfo.width, mapInfo.height, mapInfo.roomsMin, mapInfo.roomsMax));
  buildEnemies();
  if (mapInfo.boss != 0) { // bossが存在する。
  }
  setEnemy(enemies);
}
void MapScene::buildEnemies() {
  std::random_device seed_gen;
  std::mt19937 engine{seed_gen()};
  int size = mapInfo.typeOfEnemy.size();

  for (int i = enemies.size(); i <= mapInfo.enemies; i++) {
    auto enemy = Enemy::create(mapInfo.typeOfEnemy[engine() % size]);
//    log.push_back("敵を生成 " + enemy->getIdx());
    auto pos = getRandomNonePosition();
    enemy->set(pos);
    enemies.push_back(enemy);
  }
}
void MapScene::eraseEnemy(std::shared_ptr<Enemy> enemy) {
  for (auto en = enemies.begin(); en != enemies.end(); en++) {
//    log.push_back("敵を倒しました。" + (*en)->getIdx() + " " + (*en)->position().debug());
    if ((*en)->getIdx() == enemy->getIdx()) {
      auto pos = (*en)->position();
      drawBitMap[pos.y][pos.x] = BitMapKind::NONE;
//      log.push_back("敵を倒しました。" + (*en)->getIdx() + " " + (*en)->position().debug());
      enemies.erase(en);
      return;
    }
  }
}
void MapScene::setDungeon(std::shared_ptr<DungeonInterfece> dungeonPtr) {
  dungeon = dungeonPtr;
  dungeon->create();
  dungeon->debug();
  auto bitmap = dungeon->getBitMap();
  for (int y = 0; y < bitmap.size(); y++) {
    for (int x = 0; x < bitmap[y].size(); x++) {
      if (bitmap[y][x] != BitMapKind::WALL) {
        nonePlacePosition.emplace_back(x, y);
      }
    }
  }
  drawBitMap = dungeon->getBitMap();
}
void MapScene::setEnemy(std::vector<std::shared_ptr<Enemy>> enemyPtr) {
  enemies = enemyPtr;
}
void MapScene::setPlayer(std::shared_ptr<Player> playerPtr) {
  player = playerPtr;
}
std::shared_ptr<Enemy> MapScene::getEnemyFromPos(Vector2 pos) {
  for (auto enemy : enemies) {
    if (enemy->position() == pos) {
//      log.push_back("success getEnemyFromPos" + enemy->getIdx());
      return enemy;
    }
  }
//  log.push_back("failed getEnemyFromPos");
  return nullptr;
}

Vector2 MapScene::getRandomNonePosition() {
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::shuffle(nonePlacePosition.begin(), nonePlacePosition.end(), engine);
  auto itr = nonePlacePosition.begin();
  for(;itr!=nonePlacePosition.end();itr++){
    if(drawBitMap[itr->y][itr->x]  == NONE){
      return *itr;
    }
  }
//  nonePlacePosition.erase(itr);
  return *itr;
}
void MapScene::setPlayerDirection(Vector2 dir) { playerDirection = dir; }
void MapScene::Up() { setPlayerDirection(Vector2::UP); }
void MapScene::Down() { setPlayerDirection(Vector2::DOWN); };
void MapScene::Left() { setPlayerDirection(Vector2::LEFT); }
void MapScene::Right() { setPlayerDirection(Vector2::RIGHT); }
void MapScene::Select() {}
void MapScene::Cancel() {}
void MapScene::Esc() {}
void MapScene::update() {
  static int count = 0;
  auto pos = player->position();
  drawBitMap[pos.y][pos.x] = BitMapKind::NONE;
  bool collisionCheck = player->move(
      drawBitMap, playerDirection,
      [this](BitMapKind bitmap, Vector2 toPos, Vector2 fromPos) {
        auto body = std::make_shared<EventBody>();
        body->bit = bitmap;
        body->toPosition = toPos;
        body->fromPosition = fromPos;
        notify(ObserverEventList::MAP_VIEW__PLAYER_CollisionDetection, body);
      }); //最初にプレイヤーを動かす　//Objectに衝突するとイベント発生する
  pos = player->position();
  drawBitMap[pos.y][pos.x] = BitMapKind::PLAYER;
  if (!collisionCheck) {
    for (
        auto enemy :
        enemies) { //次にエネミーを動かす　//Objectに衝突するとイベント発生する
      auto pos = enemy->position();
      drawBitMap[pos.y][pos.x] = BitMapKind::NONE;
      enemy->move(drawBitMap, [this](BitMapKind bitmap, Vector2 toPos,
                                     Vector2 fromPos) {
        auto body = std::make_shared<EventBody>();
        body->bit = bitmap;
        body->toPosition = toPos;
        body->fromPosition = fromPos;
        notify(ObserverEventList::MAP_VIEW__ENEMY_CollisionDetection, body);
      });
      pos = enemy->position();
      drawBitMap[pos.y][pos.x] = BitMapKind::ENEMY;
    }
  }
  setPlayerDirection(Vector2::NONE);
  if (count % 10 == 0) {
    buildEnemies();
  }
  count++;
}
void MapScene::view() {
  for (int y = 0; y < drawBitMap.size(); y++) {
    for (int x = 0; x < drawBitMap[y].size(); x++) {
      bool check = false;
      for (auto enemy : enemies) {
        if (Vector2(x, y) == enemy->position()) {
          enemy->view();
          check = true;
          continue;
        }
      }
      if (check)
        continue;
      if (Vector2(x, y) == player->position()) {
        player->view();
        continue;
      } else if (drawBitMap[y][x] == WALL) /* 移動可能な床 */
        printf("\033[41m　\033[49m");      /* ← 注）全角スペース */
      else if (drawBitMap[y][x] == NONE)   /* 壁 */
        printf("　");
      else if (drawBitMap[y][x] == 2) /* 塗った床 */
        printf("ｘ");
    }
    std::cout << std::endl;
  }
  for (auto l : log) {
    std::cout << l << std::endl;
  }
}
