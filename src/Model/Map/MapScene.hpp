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

#include "Warp.hpp"

using namespace Vec;
using namespace Design;

class MapScene : public GameSceneInterface{
public:
  typedef std::shared_ptr<MapObjectInterface> ObjectPtr;

private:
  std::shared_ptr<DungeonInterfece> dungeon;
  MapInformation mapInfo;
  std::vector<std::string> log;
  void setPlayerDirection(Vector2 dir);//プレイヤの進む方向をセットします。
  std::vector<Vector2> nonePlacePosition;
  std::vector<std::shared_ptr<Enemy>> enemies;
  std::shared_ptr<Player> player;
  std::shared_ptr<Enemy> boss = nullptr;

  std::vector<ObjectPtr> mapObjects;
  BitMap drawBitMap;
  Vector2 playerDirection = {0,0};

public:
  class EventBody:public SubjectDataBody{
  public:
    BitMapKind bit = NONE;
    Vector2 fromPosition = Vector2::NONE;
    Vector2 toPosition = Vector2::NONE;
  };

  MapScene(){};
  void setDungeon(std::shared_ptr<DungeonInterfece> dungeonPtr);//ダンジョン生成のアルゴリズムを委譲し、ダンジョン生成を行います。
  void makeDungeon(int level);//ダンジョンの生成を行います。setDungeonも代わりに行います。

  void setEnemy(std::vector<std::shared_ptr<Enemy>> enemyPtr);//あらかじめ生成した敵をダンジョンに配置します。
  void buildEnemies();//ダンジョンに敵を配置します。内部で敵を生成し、setEnemyも代わりに行います。
  bool eraseEnemy(std::shared_ptr<Enemy> enemy);//ダンジョンの特定の敵を消します。
  bool eraseBoss();//ダンジョンのボスを消します。
  void setPlayer(std::shared_ptr<Player> playerPtr,bool direction);//プレイヤーを配置します。direction=trueは前階層から来た時、falseは戻ってきた時
  std::shared_ptr<Enemy> getEnemyFromPos(Vector2 pos);//指定した座標の敵を取得します。存在しない場合はnullptrです。
  Vector2 getRandomNonePosition();//敵とプレイヤーが存在しないエリアの座標をランダムに取得します。

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
