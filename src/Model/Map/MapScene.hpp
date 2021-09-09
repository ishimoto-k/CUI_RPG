//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_MAPSCENE_HPP
#define APPEAL_MAPSCENE_HPP
#include "../Character/Player.hpp"
#include "../GameSceneInterface.hpp"
#include "MapObjectInterface.hpp"
#include <DungeonInterface.hpp>
#include <Enemy.hpp>
#include <Observer.hpp>
#include <Vector2.hpp>
#include <memory>
using namespace Vec;
using namespace Design;

class MapScene : public GameSceneInterface{
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
        return enemy;
      }
    }
  }

  Vector2 getRandomNonePosition(){
    auto itr = nonePlacePosition.begin();
    nonePlacePosition.erase(itr);
    return *itr;
  }
  void setPlayerDirection(Vector2 dir){
    playerDirection = dir;
  }
  void Up(){
    setPlayerDirection(Vector2::UP);
  }
  void Down(){
    setPlayerDirection(Vector2::DOWN);
  };
  void Left(){setPlayerDirection(Vector2::LEFT);};
  void Right(){setPlayerDirection(Vector2::RIGHT);};
  void Select(){};
  void Cancel(){};
  void Esc(){};
  void update() override {
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
  };
};

#endif // APPEAL_MAPSCENE_HPP
