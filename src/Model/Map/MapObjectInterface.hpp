//
// Created by IshimotoKiko on 2021/09/03.
//

#ifndef APPEAL_MAPOBJECTINTERFACE_HPP
#define APPEAL_MAPOBJECTINTERFACE_HPP

#include <Vector2.hpp>
#include <Observer.hpp>

using namespace Vec;
using namespace Design;

//マップに配置するオブジェクトのインターフェース
class MapObjectInterface{
protected:
  Vector2 position_ = Vector2(0,0);
  int id_;
  typedef std::function<void()> Callback;
  Callback selectCallback; //選択されたときの処理
public:
  MapObjectInterface() = default;
  MapObjectInterface(int x,int y):position_(Vector2(x,y)){}
  virtual void view() = 0; //表示
  virtual void backViewStart(){} //背景色表示開始
  virtual void backViewEnd(){}  //背景色表示終了
  virtual void select(){selectCallback();}//選択されたときの処理
  void setOnSelectCallback(Callback callback){
    selectCallback = callback;
  }
  int id(){
    return id_;
  }
  void set(Vector2 position){
    position_ = position;
  }

  //アルゴリズムによってオブジェクトを移動したい場合
  virtual bool move(const BitMap& bitMap,std::function<void(BitMapKind,Vector2,Vector2)> callback) = 0;

  //座標を指定してオブジェクトを移動したい場合
  virtual bool move(const BitMap& bitMap,const Vector2& vector,std::function<void(BitMapKind,Vector2,Vector2)> callback) = 0;
  Vector2 position(){
    return position_;
  }
};

#endif // APPEAL_MAPOBJECTINTERFACE_HPP
