//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_MAPVIEW_HPP
#define APPEAL_MAPVIEW_HPP
#include <memory>
#include <DungeonInterface.hpp>

class MapView {
public:
  std::shared_ptr<DungeonInterfece> dungeon;
  MapView(){};

  void setDungeon(std::shared_ptr<DungeonInterfece> dungeonPtr){
    dungeon = dungeonPtr;
    dungeon->create();
  }
  void draw(){

  };
};

#endif // APPEAL_MAPVIEW_HPP
