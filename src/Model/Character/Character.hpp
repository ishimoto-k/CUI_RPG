//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_CHARACTER_HPP
#define APPEAL_CHARACTER_HPP
#include "Command/CommandInterface.hpp"
#include "Parameter.hpp"
#include <Status/StatusCreate.hpp>
#include <Skill/SkillsCreate.hpp>

//キャラクタークラス
//継承することで、バトルに参加できる
class Character {
public:
  Parameter parameter;//キャラクターのパラメータ
  virtual std::string frontView(){ return "";}//バトル中のキャラクター表示 //エネミーのみ
  virtual std::string name() = 0; //キャラクターの名前
  std::vector<std::shared_ptr<SkillInterface>> skill; //取得しているスキルの実体
  std::vector<std::shared_ptr<StatusInterface>> status; //取得している状態異常の実体
  virtual void initBattleBefore(){} //バトル開始直前の初期処理
  virtual void initTurnBefore(){ //バトルのターン開始の初期処理
    parameter.DEX = parameter.maxDEX;
    parameter.POW = parameter.maxPOW;
  };
  virtual bool addExp(int exp){return false;};//経験値獲得 ///プレイヤーのみ
  virtual void battleTurnStart(std::shared_ptr<Character> toChara,std::vector<std::string> &log){
    //ターン開始時の処理
    //かぶっている状態異常を削除
    std::sort(parameter.status.begin(), parameter.status.end());
    parameter.status.erase(std::unique(parameter.status.begin(), parameter.status.end()), parameter.status.end());
    for(auto st : parameter.status){
      auto createSt = StatusCreate::createStatus(st);
      auto ans = std::find_if(status.begin(),status.end(),[createSt](std::shared_ptr<StatusInterface> st_){
        return st_->id() == createSt->id();
      });
      if(ans == status.end()){
        //被っていない状態異常を生成して、
        //リストに追加
        status.push_back(createSt);
      }
    }
    for(auto st=status.begin(); st!=status.end();){
      if((*st)->update(name(), toChara->name(), parameter, toChara->parameter, &log)){//状態異常の効果を発動
        //trueの場合は、ステータスを除去
        //例：3ターン経った場合など
        for(auto p_st=parameter.status.begin();p_st!=parameter.status.end();){
          if(static_cast<int>(*p_st) == (*st)->id()){
            //parameter.statusも削除
            p_st = parameter.status.erase(p_st);
          }else{
            ++p_st;
          }
        }
        //実体も除去
        st = status.erase(st);
      }else{
        ++st;
      }
    }
  }
};

#endif // APPEAL_CHARACTER_HPP
