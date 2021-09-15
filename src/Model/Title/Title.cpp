//
// Created by IshimotoKiko on 2021/09/09.
//

#include "Title.hpp"
Title::Title(){
  //assets/titleを表示データを取得
  std::ifstream ifs(define::AssetsTitle());
  std::string text = std::string(std::istreambuf_iterator<char>(ifs),
                                 std::istreambuf_iterator<char>());
  frontView = text;
}
void Title::setCursor(SelectList list){
  auto itr = std::find_if(selectList.begin(),selectList.end(),[&](SelectList select){
    return list == select;
  });
  cursor = std::distance(selectList.begin(),itr);
}
void Title::Up() {
  cursor = cursor-1;
  if(-1 == cursor)cursor = selectList.size()-1;
}
void Title::Down()  {
  cursor = cursor+1;
  if(selectList.size() == cursor)cursor = 0;
}
void Title::Right() {
}
void Title::Left() {
}
void Title::update() {
}
void Title::Select() {
  auto body = std::make_shared<EventBody>(selectList[cursor]);
  notify(ObserverEventList::TITLE_SCENE_ON_SELECT, body);
}
void Title::Cancel() {
}
void Title::Esc() {
}
void Title::view() {
  std::cout << frontView << std::endl;
  for(int i=0;i<selectList.size();i++){
    if(i == cursor){
      std::cout << "＞";
    } else {
      std::cout << "　";
    }
    std::cout << selectList[i].toLabel() << std::endl;
  }
}