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
  void makeDungeon(int level);
  void buildEnemies();
  void eraseEnemy(std::shared_ptr<Enemy> enemy);
  void setDungeon(std::shared_ptr<DungeonInterfece> dungeonPtr);
  void setEnemy(std::vector<std::shared_ptr<Enemy>> enemyPtr);
  void setPlayer(std::shared_ptr<Player> playerPtr);
  std::shared_ptr<Enemy> getEnemyFromPos(Vector2 pos);

  Vector2 getRandomNonePosition();
  void setPlayerDirection(Vector2 dir);
  void Up()override;
  void Down()override;
  void Left()override;
  void Right()override;
  void Select()override;
  void Cancel()override;
  void Esc()override;
  void update()override;
  void view() override;
};

#endif // APPEAL_MAPSCENE_HPP
