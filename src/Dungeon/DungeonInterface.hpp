//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_DUNGEONINTERFACE_HPP
#define APPEAL_DUNGEONINTERFACE_HPP


#include <iostream>
#include <vector>
#include <random>

typedef std::vector<std::vector<int>> BitMap;
typedef std::pair<int, int> Vector2;

//ダンジョン生成で扱う一時的なパラメーター定数
const int ERR = -1;
const int WALL = 1;
const int NONE = 0;
const int BUILDING_WALL = 2;

//ダンジョンの基底クラス
//これを継承してダンジョン生成のアルゴリズム生成を行う
class DungeonInterfece{
protected:
  int width_;
  int height_;
public:
  DungeonInterfece(int w,int h):width_(w),height_(h){}; //縦横の入力は必須
  virtual BitMap create() = 0;
  virtual void debug() = 0;
};


#endif // APPEAL_DUNGEONINTERFACE_HPP
