//
// Created by IshimotoKiko on 2021/09/02.
//
//

#include <iostream>
#include <vector>
#include <random>

#include "DungeonCreate.hpp"

int main(){
  auto dungeon = DungeonCreate(2,2);
  dungeon.create();
  dungeon.debug();
}