//
// Created by IshimotoKiko on 2021/09/02.
//
//

#include "DungeonCreate.hpp"

//ダンジョン生成アルゴリズムの動作確認
int main(){
  auto dungeon = DungeonCreate(2,2);
  dungeon.create();
  dungeon.debug();
}