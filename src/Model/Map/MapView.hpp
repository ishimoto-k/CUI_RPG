//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_MAPVIEW_HPP
#define APPEAL_MAPVIEW_HPP
#include "MapObject/MapObjectInterface.hpp"
#include "MapObject/Player.hpp"
#include <DungeonInterface.hpp>
#include <memory>
#include <Observer.hpp>
#include <Vector2.hpp>
using namespace Vec;
using namespace Design;

class MapView : public Subject{
public:
  std::shared_ptr<DungeonInterfece> dungeon;
  std::vector<Vector2> nonePlacePosition;
  std::vector<std::shared_ptr<MapObjectInterface>> enemies;
  std::shared_ptr<Player> player;
  BitMap drawBitMap;
  Vector2 playerDirection = {0,0};

  MapView(){};

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
  }
  void setEnemy(std::vector<std::shared_ptr<MapObjectInterface>> enemyPtr){
    enemies = enemyPtr;
  }
  void setPlayer(std::shared_ptr<Player> playerPtr){
    player = playerPtr;
  }

  Vector2 getRandomNonePosition(){
    auto itr = nonePlacePosition.begin();
    nonePlacePosition.erase(itr);
    return *itr;
  }
  void setPlayerDirection(Vector2 dir){
    playerDirection = dir;
  }
  void update(){
    drawBitMap = dungeon->getBitMap();
    for(auto enemy:enemies){//最初にエネミーを動かす
      enemy->move(drawBitMap);
      auto pos = enemy->position();
      drawBitMap[pos.y][pos.x] = BitMapKind::OBJECT;
    }
    player->move(drawBitMap,playerDirection);//次にプレイヤーを動かす
    auto pos = player->position();
    drawBitMap[pos.y][pos.x] = BitMapKind::OBJECT;
  }
  void draw(){
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
          printf("\033[41m壁\033[49m");	/* ← 注）全角スペース */
        else if(drawBitMap[y][x] == NONE)	/* 壁 */
          printf("　");
        else if(drawBitMap[y][x] == 2)	/* 塗った床 */
          printf("ｘ");
      }
      std::cout << std::endl;
    }
    printf("move: ←↑→↓ restart: ESC\n");	/* 操作説明 */
  };
};

#endif // APPEAL_MAPVIEW_HPP
