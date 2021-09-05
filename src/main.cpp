#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <KeyBoardController.hpp>

#define STAGE       2      //ステージ数
#define MAZE_ROW    5      //迷路の行数
#define MAZE_COLUMN 5      //迷路の列数



#define GYO 10		/* 迷路の行数 */
#define RETU 10		/* 迷路の列数 */

/* 迷路データ */
int meiro[GYO][RETU] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int px, py;		/* プレイヤーのxy座標 */
int goal_count;	/* 塗りつぶすべき床の数 */
int count;		/* 塗りつぶした床の数 */

/* 最初の状態に戻る */
void play_start(void)
{
  int x, y;
  count = 0;
  px = 1;
  py = 1;
  for(y=0; y<GYO; y++)
    for(x=0; x<RETU; x++)
      if(meiro[y][x] == 2) meiro[y][x] = 0;	/* 塗りつぶし部分をもとに戻す */
}

/* 塗りつぶすべき床の数をカウントする */
void goal_count_check(void)
{
  int x, y;
  goal_count = 0;
  for(y=0; y<GYO; y++)
    for(x=0; x<RETU; x++)
      if(meiro[y][x] == 0) goal_count++;		/* 移動可能な床の数をカウント */
}

/* 迷路を描く */
void draw_meiro(void)
{
  int x, y;
  for(y=0; y<GYO; y++){
    for(x=0; x<RETU; x++){
      if(x == px && y == py){	/* プレイヤーの位置のとき */
        meiro[y][x] = 2;	/* 塗りつぶし済みにする */
        count ++;		/* 塗りつぶした数をカウント */
        printf("人");		/* プレイヤー */
      }
      else if(meiro[y][x] == 0)	/* 移動可能な床 */
        printf("\033[41m　\033[49m");	/* ← 注）全角スペース */
      else if(meiro[y][x] == 1)	/* 壁 */
        printf("　");
      else if(meiro[y][x] == 2)	/* 塗った床 */
        printf("ｘ");
    }
    printf("\n");
  }
  printf("move: ←↑→↓ restart: ESC\n");	/* 操作説明 */
}

/* キー入力判定 */
void key_input(void)
{
  int key;
  while (1) {	/* キーが押されるまで待つ */
    if ( KeyBoardController::checkInputKey() ){
      key = getchar();	/* 入力されたキー番号 */
      break ;
    }
  }
  if(key == 'w' && meiro[py-1][px] == 0)			/* ↑キー */
    py --;	/* 上に移動 */
  else if(key == 's' && meiro[py+1][px] == 0)		/* ↓キー */
    py ++;	/* 下に移動 */
  else if(key == 'a' && meiro[py][px-1] == 0)		/* ←キー */
    px --;	/* 左に移動 */
  else if(key == 'd' && meiro[py][px+1] == 0)		/* →キー */
    px ++;	/* 右に移動 */
  else if(key == 27)								/* ESCキー */
    play_start();	/* 最初の状態に戻る */
  else											/* 上記以外のキーの場合は */
    key_input();								/* 再度キー入力受付 */
}

int main(void)
{
  px = 1;				/* プレイヤーのx座標 */
  py = 1;				/* プレイヤーのy座標 */
  count = 0;			/* 塗りつぶした床の数 */

  goal_count_check();	/* 塗りつぶすべき床の数をカウントする */

  /* ゲームループ */
  while(1){
    printf( "\033[;H\033[2J" );

//    system("cls");	/* コンソール画面をクリア *
    draw_meiro();	/* 迷路を表示 */

    if(count == goal_count){	/* 床を全て塗りつぶしたかのチェック */
      printf("全て塗りました！\n");
      break;
    }

    key_input();		/* キー入力受付 */
  }

  return 0;
}