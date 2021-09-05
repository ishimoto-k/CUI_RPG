//
// Created by IshimotoKiko on 2021/09/03.
//

#include "DungeonCreate.hpp"

void DungeonCreate::process(){

  for(auto by = bitmap.begin();by!=bitmap.end();by++){
    if(by == bitmap.begin() || by == (bitmap.end()-1)){
      continue;
    }
    for(auto bx = by->begin();bx!=by->end();bx++){
      if(bx == by->begin() || bx == (by->end()-1)){
        continue;
      }
      int x = std::distance(bx,by->end()-1);
      int y = std::distance(by,bitmap.end()-1);
      if(x % 2){
        continue;
      }
      if(y % 2){
        continue;
      }
      selectWall.emplace_back(x,y);
    }
  }
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::shuffle(selectWall.begin(), selectWall.end(), engine);
  buildStart();
}
void DungeonCreate::build(Vector2 wall) {
  bitmap[(wall).y][(wall).x] = BitMapKind::BUILDING_WALL;
  std::vector<Vector2> vectors = ShuffulDirections();
  auto next_check = wall;
  for (auto vector : vectors) {
    next_check = wall + vector;
    if (at(bitmap,next_check) == BitMapKind::BUILDING_WALL) {
      continue;
    }
    if (at(bitmap,next_check) == BitMapKind::ERR || at(bitmap,next_check + vector) == BitMapKind::ERR) {
      return;
    }
    if (at(bitmap,next_check) == BitMapKind::NONE && at(bitmap,next_check + vector) != BitMapKind::BUILDING_WALL) {
      bitmap[(next_check).y][(next_check).x] = BitMapKind::BUILDING_WALL;
      if (at(bitmap,next_check + vector) == BitMapKind::WALL || at(bitmap,next_check + vector) == BitMapKind::BUILDING_WALL) {
        bitmap[(next_check + vector).y][(next_check + vector).x] = BitMapKind::BUILDING_WALL;
        return;
      }
      bitmap[(next_check + vector).y][(next_check + vector).x] = BitMapKind::BUILDING_WALL;
      if (at(bitmap,next_check + vector) == BitMapKind::NONE) {
        build(next_check + vector);
      }
    } else {
      continue;
    }
  }
}
void DungeonCreate::buildStart(){
  for(auto startWall:selectWall){
    if(bitmap[startWall.y][startWall.x] == BitMapKind::WALL){
      continue;
    }
    build(startWall);
    for(auto by = bitmap.begin();by!=bitmap.end();by++){
      for(auto bx = by->begin();bx!=by->end();bx++){
        if(*bx == BitMapKind::BUILDING_WALL){
          *bx = BitMapKind::WALL;
        }
      }
    }
  }
  std::random_device random;
  for(int i=0;i<(random()%5+3);i++){//部屋を3つ以上適当に作ります。
    std::mt19937 mt(random());
    auto x = mt() % (width_-1);
    int x_ = x+1;
    auto y = mt() % (height_-1);
    int y_ = y+1;
    int width = 2 + mt()%3;
    int height = 2 + mt()%3;
    std::cout << "room create" << std::endl;
    for(int xx = x_ ; xx < x_+width && xx < width_ ; xx++){
      for(int yy = y_ ; yy < y_+height && yy < height_; yy++){
//        bitmap[yy][xx] = NONE;
      }
    }
  }
  return;
}
DungeonCreate::DungeonCreate(int w, int h) : DungeonInterfece(w,h){
  //マップサイズは奇数で固定したいため、奇数の場合は+1する
  int width = (w % 2) == 0 ? w+1 :  w;
  int height = (h % 2) == 0 ? h+1 :  h;
  //マップを白塗りする
  bitmap = std::vector<std::vector<BitMapKind>>(height,std::vector<BitMapKind>(width,BitMapKind::NONE)); // W*Hのマップを生成

  //一番外枠を壁に変更する
  *bitmap.begin() = std::vector<BitMapKind>(width,BitMapKind::WALL);
  *(bitmap.end()-1) = std::vector<BitMapKind>(width,BitMapKind::WALL);
  for(auto i = bitmap.begin();i!=bitmap.end();i++){
    *i->begin() = BitMapKind::WALL;
    *(i->end()-1) = BitMapKind::WALL;
  }
  debug();
}
bool DungeonCreate::create(){
  process();
  return true;
}
void DungeonCreate::debug(){
  for(auto w : bitmap){
    for(auto h : w){
      std::cout << h;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
}