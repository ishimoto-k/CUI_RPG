//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_ESCAPE_HPP
#define APPEAL_ESCAPE_HPP

class Escape:public CommandInterface{
  std::string name(){
    return "逃げる";
  };
  std::string description(){
    return "戦闘から離脱します";
  };
  void select(){
     std::cout<<"戦闘から離脱します"<<std::endl;
  };
};

#endif // APPEAL_SKEILLSELECT_HPP
