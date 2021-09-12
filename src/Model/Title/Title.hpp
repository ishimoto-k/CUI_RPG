//
// Created by IshimotoKiko on 2021/09/09.
//

#ifndef APPEAL_TITLE_HPP
#define APPEAL_TITLE_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../GameSceneInterface.hpp"

class Title : public GameSceneInterface{
  int cursor = 0;
  std::string frontView;
public:
  class SelectList{
  public:
    enum Kind{
      START,
      LOAD,
      END,
    };
    SelectList(Kind k):kind(k){};
    std::string toLabel(){
      switch (kind){
      case START:
        return "はじめから";
      case LOAD:
        return "続きから";
      case END:
        return "終了";
      }
    }
    bool operator ==(Kind k){ return k == kind;}
    bool operator ==(SelectList k){ return k.kind == kind;}
  private:
    Kind kind;
  };
  class EventBody : public SubjectDataBody{
  public:
    SelectList selectList;
    EventBody(SelectList sel):selectList(sel){}
  };
  Title(){
    std::ifstream ifs("assets/title");
    std::string text = std::string(std::istreambuf_iterator<char>(ifs),
                                   std::istreambuf_iterator<char>());
    frontView = text;
  }

  std::vector<SelectList> selectList = {
      SelectList::START,
      SelectList::LOAD,
      SelectList::END,
  };
  void setCursor(SelectList list){
    auto itr = std::find_if(selectList.begin(),selectList.end(),[&](SelectList select){
      return list == select;
    });
    cursor = std::distance(selectList.begin(),itr);
  }
  void Up() override {
    cursor = cursor-1;
    if(-1 == cursor)cursor = selectList.size()-1;
  }
  void Down() override {
    cursor = cursor+1;
    if(selectList.size() == cursor)cursor = 0;
  }
  void Right() override {
  }
  void Left() override {
  }
  void update() override {
  }
  void Select() override {
    auto body = std::make_shared<EventBody>(selectList[cursor]);
    notify(ObserverEventList::TITLE_SCENE_ON_SELECT, body);
  }
  void Cancel() override {
  }
  void Esc() override{
  }
  void view() override {
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
};

#endif // APPEAL_TITLE_HPP
