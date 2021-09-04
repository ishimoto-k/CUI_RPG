//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_MAPVIEW_HPP
#define APPEAL_MAPVIEW_HPP
#include "MapObject/MapObjectInterface.hpp"
#include "MapObject/Player.hpp"
#include <DungeonInterface.hpp>
#include <memory>

#include <Vector2.hpp>
using namespace Vec;

class MapView {
public:
  std::shared_ptr<DungeonInterfece> dungeon;
  std::vector<Vector2> nonePlacePosition;
  std::shared_ptr<MapObjectInterface> enemy;
  std::shared_ptr<Player> player;

  MapView(){};

  void setDungeon(std::shared_ptr<DungeonInterfece> dungeonPtr){
    dungeon = dungeonPtr;
    dungeon->create();
    dungeon->debug();
    auto bitmap = dungeon->getBitMap();
    for(int y=0;y<bitmap.size();y++){
      for(int x=0;x<bitmap[y].size();x++){
        if(bitmap[y][x] != WALL){
          nonePlacePosition.push_back(Vector2(x,y));
        }
      }
    }
  }
  void setEnemy(std::shared_ptr<MapObjectInterface> enemyPtr){
    enemy = enemyPtr;
  }
  void setPlayer(std::shared_ptr<Player> playerPtr){
    player = playerPtr;
  }

  Vector2 getRandomNonePosition(){
    std::random_device randomDevice;
    auto index = randomDevice()%nonePlacePosition.size();
    return nonePlacePosition[index];
  }
  void update(){
    enemy->move(dungeon->getBitMap());
    player->move(dungeon->getBitMap(),Vector2(0,0));
  }
  void draw(){
    auto bitmap = dungeon->getBitMap();
    for(int y=0; y<bitmap.size(); y++){
      for(int x=0; x<bitmap[y].size(); x++){
        if(Vector2(x,y) == enemy->position()){
          enemy->view();
          continue;
        }
        if(Vector2(x,y) == player->position()){
          player->view();
          continue;
        }
        else if(bitmap[y][x] == WALL)	/* 移動可能な床 */
          printf("\033[41m壁\033[49m");	/* ← 注）全角スペース */
        else if(bitmap[y][x] == NONE)	/* 壁 */
          printf("　");
        else if(bitmap[y][x] == 2)	/* 塗った床 */
          printf("ｘ");
      }
      std::cout << std::endl;
    }
    printf("move: ←↑→↓ restart: ESC\n");	/* 操作説明 */
  };
};

#endif // APPEAL_MAPVIEW_HPP
