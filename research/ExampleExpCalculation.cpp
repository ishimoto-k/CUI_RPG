//
// Created by IshimotoKiko on 2021/09/08.
//

#include <iostream>
#include <math.h>
//参考 https://qiita.com/yuji_yasuhara/items/83a67a784d4d6152a2de

//int main(){
//  double needEnemyKill = 5;
//  double alpha = 1.5;
//  double firstNeedExp = 12;
//  const int maxLevel = 30;
//
//  double needNextLevelExp = 0;
//
//  for(int level=1;level <= maxLevel;level++){
//    needNextLevelExp = firstNeedExp*pow(alpha,level-1);
//    int enemyExp = firstNeedExp*pow(alpha,level-1)/needEnemyKill; //記事の式が間違い。
//    std::cout << "level:" << level << "Exp:" << enemyExp << " needExp" << needNextLevelExp << std::endl;
//  }
//}

int main(){
  double needEnemyKill = 5;
  double alpha = 1.22;
  double firstNeedExp = 35;
  const int maxLevel = 30;

  double needNextLevelExp = 0;
  double allExp = 0;
  for(int level=1;level <= maxLevel;level++){
    needNextLevelExp = firstNeedExp*pow(alpha,level-1);
    int enemyExp = firstNeedExp*pow(alpha,level-1)/needEnemyKill;
    allExp += needNextLevelExp;
    std::cout << "level:" << level << "Exp:\t" << enemyExp << " needExp:\t" << needNextLevelExp << " allExp:\t" << allExp<< std::endl;
  }
}