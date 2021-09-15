//
// Created by IshimotoKiko on 2021/09/03.
//

#include "DungeonCreate.hpp"

void DungeonCreate::process(){

  //1マス置き柱を設置します。
  //ここでは、設置せず、selectWallに該当の柱ポジションを格納します。
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
        //1マス毎
        continue;
      }
      if(y % 2){
        //1マス毎
        continue;
      }
      selectWall.emplace_back(x,y);
    }
  }
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  //柱をシャッフルします。
  std::shuffle(selectWall.begin(), selectWall.end(), engine);
  //初期化終了

  buildStart();//生成開始
}
void DungeonCreate::build(Vector2 wall) {
  //いきなり壁にせず、設置中の壁にする(BUILDING_WALL)
  bitmap[(wall).y][(wall).x] = BitMapKind::BUILDING_WALL;
  //ランダムに4方向の配列を生成
  std::vector<Vector2> vectors = ShuffulDirections();
  auto next_check = wall;
  for (auto vector : vectors) {
    next_check = wall + vector;
    if (at(bitmap,next_check) == BitMapKind::BUILDING_WALL) {
      //一つ先のマスが設置中の壁ならスキップして次の方向へ、
      continue;
    }
    if (at(bitmap,next_check) == BitMapKind::ERR || at(bitmap,next_check + vector) == BitMapKind::ERR) {
      //一つ先とその先のマスがエラーなら終了
      //エラー：マップ外
      return;
    }
    if (at(bitmap,next_check) == BitMapKind::NONE && at(bitmap,next_check + vector) != BitMapKind::BUILDING_WALL) {
      //一つ先のマスが道、さらに先のマスが設置中の壁ではない場合、壁を伸ばす。
      bitmap[(next_check).y][(next_check).x] = BitMapKind::BUILDING_WALL;
      if (at(bitmap,next_check + vector) == BitMapKind::WALL || at(bitmap,next_check + vector) == BitMapKind::BUILDING_WALL) {
        //さらに先のマスが壁か設置中の壁の場合、打ち止め。
        bitmap[(next_check + vector).y][(next_check + vector).x] = BitMapKind::BUILDING_WALL;
        return;
      }
      bitmap[(next_check + vector).y][(next_check + vector).x] = BitMapKind::BUILDING_WALL;
      if (at(bitmap,next_check + vector) == BitMapKind::NONE) {
        //さらに先のマスが道なら再帰呼び出し。
        build(next_check + vector);
      }
    } else {
      continue;
    }
  }
}
void DungeonCreate::buildStart(){
  for(auto startWall:selectWall){
    //柱を一つ選びます。
    if(bitmap[startWall.y][startWall.x] == BitMapKind::WALL){
      //その柱がすでに壁なら次の柱へ、
      continue;
    }
    build(startWall);//再起的に柱から壁を伸ばします。
    //再起終了後、一旦設置中の壁は壁に昇格。
    for(auto by = bitmap.begin();by!=bitmap.end();by++){
      for(auto bx = by->begin();bx!=by->end();bx++){
        if(*bx == BitMapKind::BUILDING_WALL){
          *bx = BitMapKind::WALL;
        }
      }
    }
  }
  std::random_device random;
  for(int i=0;i<(random()%roomMax_+roomMin_);i++){//部屋をroomMin_以上適当に作ります。被ることもあり。
    std::mt19937 mt(random());
    auto x = mt() % (width_-1);
    int x_ = x+1;
    auto y = mt() % (height_-1);
    int y_ = y+1;
    int width = 2 + mt()%3;
    int height = 2 + mt()%3;
    for(int xx = x_ ; xx < x_+width && xx < width_-1 ; xx++){
      for(int yy = y_ ; yy < y_+height && yy < height_-1; yy++){
        bitmap[yy][xx] = NONE;
      }
    }
  }
}
DungeonCreate::DungeonCreate(int w, int h,int roomMin,int roomMax) : DungeonInterfece(w,h){
  roomMin_ = roomMin;
  roomMax_ = roomMax;

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
//  debug();
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
  return;
}