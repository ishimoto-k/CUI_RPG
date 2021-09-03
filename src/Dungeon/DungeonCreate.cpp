//
// Created by IshimotoKiko on 2021/09/03.
//

#include "DungeonCreate.hpp"



Vector2 operator +(Vector2 l,Vector2 r){ return Vector2(l.first+r.first,l.second+r.second);}
int DungeonCreate::at(Vector2 v){
  if(v.first >= bitmap.size())return ERR;
  if(v.first <= -1)return ERR;
  if(v.second >= bitmap[v.first].size())return ERR;
  if(v.second <= -1)return ERR;
  return bitmap[v.first][v.second];
}
void DungeonCreate::process(){

  for(auto bx = bitmap.begin();bx!=bitmap.end();bx++){
    if(bx == bitmap.begin() || bx == (bitmap.end()-1)){
      continue;
    }
    for(auto by = bx->begin();by!=bx->end();by++){
      if(by == bx->begin() || by == (bx->end()-1)){
        continue;
      }
      int x = std::distance(bx,bitmap.end()-1);
      int y = std::distance(by,bx->end()-1);
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
  bitmap[(wall).first][(wall).second] = BUILDING_WALL;
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
      bitmap[(next_check).first][(next_check).second] = BUILDING_WALL;
      if (at(next_check + vector) == WALL || at(next_check + vector) == BUILDING_WALL) {
        std::cout << "finish" << std::endl;
        return;
      }
      bitmap[(next_check + vector).first][(next_check + vector).second] =BUILDING_WALL;
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
    if(bitmap[startWall.first][startWall.second] == WALL){
      continue;
    }
    build(startWall);
    for(auto bx = bitmap.begin();bx!=bitmap.end();bx++){
      for(auto by = bx->begin();by!=bx->end();by++){
        if(*by == BUILDING_WALL){
          *by = WALL;
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
        bitmap[xx][yy] = NONE;
      }
    }
  }
  bitmap[5][2] = 9;
  return;
}
DungeonCreate::DungeonCreate(int w, int h) : DungeonInterfece(w,h){
  //マップサイズは奇数で固定したいため、奇数の場合は+1する
  int width = (w % 2) == 0 ? w+1 :  w;
  int height = (h % 2) == 0 ? h+1 :  h;
  //マップを白塗りする
  bitmap = std::vector<std::vector<int>>(width,std::vector<int>(height,NONE)); // W*Hのマップを生成

  //一番外枠を壁に変更する
  *bitmap.begin() = std::vector<int>(height,WALL);
  *(bitmap.end()-1) = std::vector<int>(height,WALL);
  for(auto i = bitmap.begin();i!=bitmap.end();i++){
    *i->begin() = WALL;
    *(i->end()-1) = WALL;
  }
};
BitMap DungeonCreate::create(){
  process();
  return bitmap;
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