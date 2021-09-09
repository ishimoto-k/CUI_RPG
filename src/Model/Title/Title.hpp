//
// Created by IshimotoKiko on 2021/09/09.
//

#ifndef APPEAL_TITLE_HPP
#define APPEAL_TITLE_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Title {
  int cursor = 0;
  std::string frontView;
public:
  Title(){
    std::ifstream ifs(std::string(CURRENT_DIRECTORY)+"/assets/title");
    std::string text = std::string(std::istreambuf_iterator<char>(ifs),
                                   std::istreambuf_iterator<char>());
    frontView = text;
  }
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
  private:
    Kind kind;
  };
  std::vector<SelectList> selectList = {
      SelectList::START,
      SelectList::LOAD,
      SelectList::END,
  };
  void cursorUp(){
    cursor = cursor+1;
    if(selectList.size() == cursor)cursor = 0;
  }
  void cursorDown(){
    cursor = cursor-1;
    if(-1 == cursor)cursor = selectList.size()-1;
  }
  void view(){
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
