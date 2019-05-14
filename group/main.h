#pragma once

#include <DxLib.h>
#include <math.h>

//ﾃﾞﾊﾞｯｸ用メッセージ
#ifdef _DEBUG
#define AST() {\
	CHAR ast_mes[256];\
	wsprintf(ast_mes, "%s %d行目\0", __FILE__, __LINE__);\
	MessageBox(0, ast_mes, "ｱｻｰﾄ表示", MB_OK);\
	}
#else
#define AST()
#endif

#define PI 3.141592		//円周率

#define SCREEN_SIZE_X 960
#define SCREEN_SIZE_Y 640

#define ACC_G 10
#define INIT_VELOCITY 50		//初速度
#define SECOND_PER_FRAME 0.2	//1フレームの秒数

typedef struct {
	float x;
	float y;
}XY_F;

typedef struct {
	int x;
	int y;
}XY;

enum MOVE_DIR {
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT,
	DIR_MAX
};

typedef struct {
	MOVE_DIR movedir;	//向いている方向
	XY pos;				//キャラクタの位置(中心)
	XY move;
	XY size;			//キャラクタ画像のサイズ
	XY sizeOffset;		//キャラクタ中央からの左上位置
	XY hitPosS;			//当たり判定用の左上
	XY hitPosE;			//当たり判定用の右下
	bool runFlag;		//キャラクタの状態(走っているか)
	bool jumpFlag;		//キャラクタの状態(ジャンプしているか)
	bool shotFlag;		//キャラクタの状態(弾を撃っているか)
	bool damageFlag;	//キャラクタの状態(ダメージを受けているか)
	bool gFlag;
	bool xFlag;
	int moveSpeed;		//キャラクタの移動量
	int life;			//キャラクタの体力
	int lifeMax;		//キャラクタの体力最大
	int animCnt;		//キャラクタのアニメーション用カウンタ
	int imgLockCnt;		//キャラクタのイメージ固定用カウンタ
	int type;			//何らかの属性を格納できる
	bool flag;
	XY_F Velocity;
}CHARACTER;


int SystemInit(void);
void GameInit(void);
void GameTitle(void);
void GameTitleDraw(void);
void GameLife(void);
void GameLifeDraw(void);
void GameMain(void);
void GameMainDraw(void);
void GameSClear(void);
void GameClear(void);
void GameOver(void);
void GameOverDraw(void);
//void HitCheck(void);
bool FadeInScreen(int fadeIn);
bool FadeOutScreen(int fadeOut);

int GetStageCnt(void);