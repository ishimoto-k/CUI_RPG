//
// Created by IshimotoKiko on 2021/09/09.
//

#ifndef APPEAL_TITLE_HPP
#define APPEAL_TITLE_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <Defines.hpp>
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
        return "つづきから";
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
    //イベント通知のためのクラス
  public:
    SelectList selectList;
    EventBody(SelectList sel):selectList(sel){}
  };
  std::vector<SelectList> selectList = {
      SelectList::START,
      SelectList::LOAD,
      SelectList::END,
  };
  Title();
  void setCursor(SelectList list);
  void Up() override;
  void Down() override;
  void Right() override;
  void Left() override;
  void update() override;
  void Select() override;
  void Cancel() override;
  void Esc() override;
  void view() override;
};

#endif // APPEAL_TITLE_HPP
