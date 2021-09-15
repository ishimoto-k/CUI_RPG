//
// Created by IshimotoKiko on 2021/09/04.
//

#ifndef APPEAL_PLAYER_HPP
#define APPEAL_PLAYER_HPP

#include <Character.hpp>
#include <MapObjectInterface.hpp>
#include <iostream>

class Player :public MapObjectInterface,public Character{
  std::vector<Parameter> levelList;
  std::vector<std::shared_ptr<SkillInterface>> gotSkills;
public:
  Player(int x,int y,int exp):MapObjectInterface(x,y) {
    auto p = Parameter::loadFromExp(exp);//経験値からレベルとパラメーターを取得
    parameter = p;
    auto skillIds = Parameter::loadSkillFromLevel(p.level);//レベルから覚えているスキルIDを取得
    for(auto id:skillIds){
      auto s = SkillsCreate::createCommand(static_cast<TypeOfSkills>(id));//スキルIDからスキルの実体を生成しリスト化
      skill.push_back(s);
    }
  }
  std::string name() override {
    return "冒険者";
  }
  void view() override;
  std::vector<std::shared_ptr<SkillInterface>> getGotSkills(){
    return gotSkills;
  }
  bool move(const BitMap& bitMap,std::function<void(BitMapKind,Vector2,Vector2)> callback) override;
  bool move(const BitMap& bitMap,const Vector2& direction,std::function<void(BitMapKind,Vector2,Vector2)> callback) override;
  bool addExp(int exp) override {
    //経験値取得とレベルアップ処理
    parameter.EXP += exp;
//    std::cout << "EXP:" <<  parameter.EXP << " targetExp:" << Parameter::loadFromLevel(parameter.level).targetEXP << std::endl;
    if(parameter.EXP > Parameter::loadFromLevel(parameter.level).targetEXP){
      //目標経験値をオーバー
      if(parameter.level == Parameter::getLevelList().size()){
        //MAXレベルの場合、レベルアップなし
        return false;
      }
      auto tmp =  parameter.EXP;
      //レベルアップしたので、そのレベルのパラメータを取得
      parameter = Parameter::loadFromLevel(parameter.level+1);
      gotSkills.clear();
      for(auto id:parameter.skillIds){
        //獲得したスキルの生成
        auto s = SkillsCreate::createCommand(static_cast<TypeOfSkills>(id));
        skill.push_back(s);
        gotSkills.push_back(s);
      }
      std::sort(skill.begin(), skill.end());
      skill.erase(std::unique(skill.begin(), skill.end()), skill.end());
      //被ったスキルは削除
      parameter.EXP = tmp;
      //経験値を代入
      return true;
    }
    return false;
  }
  void initBattleBefore() override {
//    parameter.HP = parameter.maxHP;　バトル終了前に全回復するので削除
//    parameter.MP = parameter.maxMP;
    parameter.POW = parameter.maxPOW;
    parameter.DEX = parameter.maxDEX;
    parameter.status.clear();
    status.clear();
  }
};
#endif // APPEAL_PLAYER_HPP
