//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_DUNGEONINTERFACE_HPP
#define APPEAL_DUNGEONINTERFACE_HPP


#include <iostream>
#include <vector>
#include <random>
#include <Vector2.hpp>
using namespace Vec;



//ダンジョンの基底クラス
//これを継承してダンジョン生成のアルゴリズム生成を行う
class DungeonInterfece{
protected:
  BitMap bitmap;
  int width_;
  int height_;
public:
  DungeonInterfece(int w,int h):width_(w),height_(h){}; //縦横の入力は必須
  virtual bool create() = 0;//ダンジョン生成開始
  virtual void debug() = 0;//デバッグ用
  const BitMap& getBitMap() {return bitmap;};
};


#endif // APPEAL_DUNGEONINTERFACE_HPP
