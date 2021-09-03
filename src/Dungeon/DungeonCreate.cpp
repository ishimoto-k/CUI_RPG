//
// Created by IshimotoKiko on 2021/09/03.
//

#include "DungeonCreate.hpp"



int DungeonCreate::at(Vector2 v){
  if(v.y >= bitmap.size())return ERR;
  if(v.y <= -1)return ERR;
  if(v.x >= bitmap[v.y].size())return ERR;
  if(v.x <= -1)return ERR;
  return bitmap[v.y][v.x];
}
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
  bitmap[(wall).y][(wall).x] = BUILDING_WALL;
  std::vector<Vector2> vectors = {Vector2(0, 1), Vector2(1, 0),
                                  Vector2(0, -1), Vector2(-1, 0)};
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::shuffle(vectors.begin(), vectors.end(), engine);
  auto next_check = wall;
  for (auto vector : vectors) {
    next_check = wall + vector;
    if (at(next_check) == BUILDING_WALL) {
      continue;
    }
    if (at(next_check) == ERR || at(next_check + vector) == ERR) {
      return;
    }
    if (at(next_check) == NONE && at(next_check + vector) != BUILDING_WALL) {
      bitmap[(next_check).y][(next_check).x] = BUILDING_WALL;
      if (at(next_check + vector) == WALL || at(next_check + vector) == BUILDING_WALL) {
        bitmap[(next_check + vector).y][(next_check + vector).x] = BUILDING_WALL;
        return;
      }
      bitmap[(next_check + vector).y][(next_check + vector).x] = BUILDING_WALL;
      if (at(next_check + vector) == NONE) {
        build(next_check + vector);
      }
    } else {
      continue;
    }
  }
}
void DungeonCreate::buildStart(){
  for(auto startWall:selectWall){
    if(bitmap[startWall.y][startWall.x] == WALL){
      continue;
    }
    build(startWall);
    for(auto by = bitmap.begin();by!=bitmap.end();by++){
      for(auto bx = by->begin();bx!=by->end();bx++){
        if(*bx == BUILDING_WALL){
          *bx = WALL;
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
  bitmap = std::vector<std::vector<int>>(height,std::vector<int>(width,NONE)); // W*Hのマップを生成

  //一番外枠を壁に変更する
  *bitmap.begin() = std::vector<int>(width,WALL);
  *(bitmap.end()-1) = std::vector<int>(width,WALL);
  for(auto i = bitmap.begin();i!=bitmap.end();i++){
    *i->begin() = WALL;
    *(i->end()-1) = WALL;
  }
  debug();
};
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