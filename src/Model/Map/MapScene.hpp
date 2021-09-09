//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_MAPSCENE_HPP
#define APPEAL_MAPSCENE_HPP
#include "../Character/Player.hpp"
#include "../GameSceneInterface.hpp"
#include "MapInformation.hpp"
#include "MapObjectInterface.hpp"
#include <DungeonCreate.hpp>
#include <DungeonInterface.hpp>
#include <Enemy.hpp>
#include <Observer.hpp>
#include <Vector2.hpp>
#include <memory>

using namespace Vec;
using namespace Design;

class MapScene : public GameSceneInterface{
  MapInformation mapInfo;
  std::vector<std::string> log;
public:

  std::shared_ptr<DungeonInterfece> dungeon;
  std::vector<Vector2> nonePlacePosition;
  std::vector<std::shared_ptr<Enemy>> enemies;
  std::shared_ptr<Player> player;
  BitMap drawBitMap;
  Vector2 playerDirection = {0,0};
  Observer observer;

  class EventBody:public SubjectDataBody{
  public:
    BitMapKind bit = NONE;
    Vector2 fromPosition = Vector2::NONE;
    Vector2 toPosition = Vector2::NONE;
  };

  MapScene(){};
  void makeDungeon(int level){
    mapInfo = MapInformation::getMapInfo(level-1);
    setDungeon(std::make_shared<DungeonCreate>(mapInfo.width,mapInfo.height,mapInfo.roomsMin,mapInfo.roomsMax));
    buildEnemies();
    if(mapInfo.boss != 0){ //bossが存在する。

    }
    setEnemy(enemies);
  }
  void buildEnemies(){
    std::random_device seed_gen;
    std::mt19937 engine {seed_gen()};
    int size = mapInfo.typeOfEnemy.size();

    for(int i=enemies.size();i<=mapInfo.enemies;i++) {
      auto enemy = Enemy::create(mapInfo.typeOfEnemy[engine()%size]);
      log.push_back("敵を生成 " + enemy->getIdx());
      auto pos = getRandomNonePosition();
      enemy->set(pos);
      enemies.push_back(enemy);
    }
  }
  void eraseEnemy(std::shared_ptr<Enemy> enemy){
    for(auto en=enemies.begin();en != enemies.end();en++){
      log.push_back("敵を倒しました。" + (*en)->getIdx() + " " +(*en)->position().debug());
      if((*en)->getIdx() == enemy->getIdx()){
        auto pos = (*en)->position();
        drawBitMap[pos.y][pos.x] = BitMapKind::NONE;
        log.push_back("敵を倒しました。" + (*en)->getIdx() + " " +(*en)->position().debug());
        enemies.erase(en);
        return;
      }
    }
  }
  void setDungeon(std::shared_ptr<DungeonInterfece> dungeonPtr){
    dungeon = dungeonPtr;
    dungeon->create();
    dungeon->debug();
    auto bitmap = dungeon->getBitMap();
    for(int y=0;y<bitmap.size();y++){
      for(int x=0;x<bitmap[y].size();x++){
        if(bitmap[y][x] != BitMapKind::WALL){
          nonePlacePosition.emplace_back(x,y);
        }
      }
    }
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    std::shuffle(nonePlacePosition.begin(), nonePlacePosition.end(), engine);
    drawBitMap = dungeon->getBitMap();
  }
  void setEnemy(std::vector<std::shared_ptr<Enemy>> enemyPtr){
    enemies = enemyPtr;
  }
  void setPlayer(std::shared_ptr<Player> playerPtr){
    player = playerPtr;
  }
  std::shared_ptr<Enemy> getEnemyFromPos(Vector2 pos){
    for(auto enemy:enemies){
      if(enemy->position() == pos){
        log.push_back("success getEnemyFromPos" + enemy->getIdx());
        return enemy;
      }
    }
    log.push_back("failed getEnemyFromPos");
    return nullptr;
  }

  Vector2 getRandomNonePosition(){
    auto itr = nonePlacePosition.begin();
    nonePlacePosition.erase(itr);
    return *itr;
  }
  void setPlayerDirection(Vector2 dir){
    playerDirection = dir;
  }
  void Up()override {
    setPlayerDirection(Vector2::UP);
  }
  void Down()override {
    setPlayerDirection(Vector2::DOWN);
  };
  void Left()override {setPlayerDirection(Vector2::LEFT);};
  void Right()override {setPlayerDirection(Vector2::RIGHT);};
  void Select()override {};
  void Cancel()override {};
  void Esc()override {};
  void update()override {
    static int count = 0;
    auto pos = player->position();
    drawBitMap[pos.y][pos.x] = BitMapKind::NONE;
    bool collisionCheck =  player->move(drawBitMap,playerDirection,[this](BitMapKind bitmap,Vector2 toPos,Vector2 fromPos){
      auto body = std::make_shared<EventBody>();
      body->bit = bitmap;
      body->toPosition = toPos;
      body->fromPosition = fromPos;
      notify(ObserverEventList::MAP_VIEW__PLAYER_CollisionDetection,body);
    });//最初にプレイヤーを動かす　//Objectに衝突するとイベント発生する
    pos = player->position();
    drawBitMap[pos.y][pos.x] = BitMapKind::PLAYER;
    if(!collisionCheck) {
      for (auto enemy : enemies) { //次にエネミーを動かす　//Objectに衝突するとイベント発生する
        auto pos = enemy->position();
        drawBitMap[pos.y][pos.x] = BitMapKind::NONE;
        enemy->move(drawBitMap,[this](BitMapKind bitmap,Vector2 toPos,Vector2 fromPos){
          auto body = std::make_shared<EventBody>();
          body->bit = bitmap;
          body->toPosition = toPos;
          body->fromPosition = fromPos;
          notify(ObserverEventList::MAP_VIEW__ENEMY_CollisionDetection,body);
        });
        pos = enemy->position();
        drawBitMap[pos.y][pos.x] = BitMapKind::ENEMY;
      }
    }
    setPlayerDirection(Vector2::NONE);
    if(count % 10 == 0) {
      buildEnemies();
    }
    count++;
  }
  void view() override {
    for(int y=0; y<drawBitMap.size(); y++){
      for(int x=0; x<drawBitMap[y].size(); x++){
        bool check = false;
        for(auto enemy:enemies){
          if(Vector2(x,y) == enemy->position()){
            enemy->view();
            check = true;
            continue;
          }
        }
        if(check)
          continue;
        if(Vector2(x,y) == player->position()){
          player->view();
          continue;
        }
        else if(drawBitMap[y][x] == WALL)	/* 移動可能な床 */
          printf("\033[41m　\033[49m");	/* ← 注）全角スペース */
        else if(drawBitMap[y][x] == NONE)	/* 壁 */
          printf("　");
        else if(drawBitMap[y][x] == 2)	/* 塗った床 */
          printf("ｘ");
      }
      std::cout << std::endl;
    }
    for(auto l:log){
      std::cout << l << std::endl;
    }
  };
};

#endif // APPEAL_MAPSCENE_HPP
