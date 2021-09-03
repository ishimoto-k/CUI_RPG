//
// Created by IshimotoKiko on 2021/09/03.
//


#include <iostream>
#include <vector>
#include <random>

#include "../src/Model/Map/MapView.hpp"
#include <DungeonCreate.hpp>
#include <DummyEnemy.hpp>

int main(){
  MapView mapView;
  mapView.setDungeon(std::make_shared<DungeonCreate>(20,10));
  mapView.dungeon->debug();
  auto pos = mapView.getRandomNonePosition();
  mapView.setEnemy(std::make_shared<DummyEnemy>(pos.x,pos.y));
  mapView.draw();
}