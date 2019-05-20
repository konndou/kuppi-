
#include "main.h"
#include "keyCheck.h"
#include "player1.h"
#include "stage.h"
#include "enemy.h"
#include "shot.h"
#include "boss.h"


typedef enum {
	GMODE_INIT,
	GMODE_TITLE,
	GMODE_LIFE,
	GMODE_GAME,
	GMODE_SCLEAR,
	GMODE_CLEAR,
	GMODE_OVER
}GAME_MODE;
GAME_MODE gameMode;

int gameCounter;
int fadeCnt;
bool fadeIn;
bool fadeOut;

//タイトル
int titleImage;
int titleCnt;
int pauseFlag;

int gameoverImage;

int clearImage;

//プレイヤー
int pImage;

//ステージ
int haikeiImage[35];
int haikeiData[20][30] = {
{ 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0},

{ 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0},

{ 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0},

{ 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0},
{ 14, 15, 15, 15, 15, 15,  15, 15, 15, 15, 15, 15,  15, 15, 15, 15, 15, 15,  15, 15, 15, 15, 15, 15,  15, 15, 15, 15, 15, 16},
{ 20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20},
{ 17, 18, 18, 18, 18, 18,  18, 18, 18, 18, 18, 18,  18, 18, 18, 18, 18, 18,  18, 18, 18, 18, 18, 18,  18, 18, 18, 18, 18, 19},
};

XY clearPos;
XY haikeiPos;
int lifeMax = 5;
int life;
int se;
int cnt = 0;

//ﾌﾟﾛﾄﾀｲﾌﾟ宣言
int SystemInit(void);
void GameInit(void);
void GameTitle(void);
void GameTitleDraw(void);
void GameMain(void);
void GameMainDraw(void);
void GameClear(void);
void GameOver(void);
void GameOverDraw(void);
//void HitCheck(void);
bool FadeInScreen(int fadeIn);
bool FadeOutScreen(int fadeOut);

// ========== WinMain関数 
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SystemInit();
	

	// ---------- ｹﾞｰﾑﾙｰﾌﾟ 
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();	// 画面消去 

		KeyCheck();

		switch (gameMode) {
		case GMODE_INIT:
			GameInit();
			gameMode = GMODE_TITLE;
			break;

		case GMODE_TITLE:
			GameTitle();
			if (fadeIn) {
				if (!FadeInScreen(5))fadeIn = false;
			}
			else if (fadeOut) {
				if (!FadeOutScreen(5)) {
					gameMode = GMODE_LIFE;
					fadeOut = false;
					fadeIn = true;
				}
			}
			else {
				if (trgkey[KEY_START]) {
					fadeOut = true;
				}
			}
			break;

		case GMODE_LIFE:
			GameLife();
			if (fadeIn) {
				if (!FadeInScreen(5))fadeIn = false;
			}
			else if (fadeOut) {
				if (!FadeOutScreen(5)) {
					gameMode = GMODE_GAME;
					fadeOut = false;
					fadeIn = true;
				}
			}
			else {
				if (trgkey[KEY_START]) {
					fadeOut = true;
				}
			}
			break;

		case GMODE_GAME:
			GameMain();
			PlaySoundMem(se, DX_PLAYTYPE_BACK, false);
			PlaySoundMem(se, DX_PLAYTYPE_LOOP, false);
			if (fadeIn) {
				if (!FadeInScreen(5)) {
					fadeIn = false;
				}
			}
			break;

		case GMODE_SCLEAR:
			StopSoundMem(se);
			GameSClear();
			break;

		case GMODE_CLEAR:
			GameClear();
			break;

		case GMODE_OVER:
			GameOver();
			if (fadeOut) {
				if (!FadeOutScreen(5)) {
					fadeOut = false;
					fadeIn = true;
					gameMode = GMODE_INIT;
				}
			}
			if (trgkey[KEY_START]) {
				fadeOut = true;
			}
			break;

		default:
			GameInit();
			break;
		}

		// ﾒｲﾝ処理 
		ScreenFlip();		// 裏画面を表画面に瞬間ｺﾋﾟｰ 
	}
	gameMode = GMODE_INIT;

	DxLib_End();			// DXﾗｲﾌﾞﾗﾘの終了処理 
	return 0;				// このﾌﾟﾛｸﾞﾗﾑの終了
}

int SystemInit(void)
{
	// ---------- ｼｽﾃﾑ処理 
	SetWindowText("Shooting_kadai");
	// ｼｽﾃﾑ処理 
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 800×600ﾄﾞｯﾄ65536色ﾓｰﾄﾞに設定 
	ChangeWindowMode(true);		// true:window false:ﾌﾙｽｸﾘｰﾝ
	//ChangeWindowMode(false); 
	if (DxLib_Init() == -1) return -1;					// DXﾗｲﾌﾞﾗﾘ初期化処理 
	SetDrawScreen(DX_SCREEN_BACK);					// ひとまずﾊﾞｯｸﾊﾞｯﾌｧに描画 

	KeyCheckSystemInit();
	stageSystemInit();
	PlayerSystemInit();
	EnemySystemInit();
	ShotSystemInit();

	fadeIn = false;
	fadeOut = false;

	// ---------- グラフィックの登録 ----------- 
	titleImage = LoadGraph("image/title.png");
	gameoverImage = LoadGraph("image/gameover.png");
	clearImage = LoadGraph("image/clear.png");
	LoadDivGraph("image/mapchip2.png", 30, 30, 1, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, haikeiImage);
	pImage = LoadGraph("image/playerstop.png");

	se = LoadSoundMem("bgm/stage1.mp3");
}

void GameInit(void)
{
	// ----------- 変数初期化 ---------- 
	titleCnt = 0;
	fadeCnt = 0;
	pauseFlag = false;
	life = lifeMax;

	haikeiPos = { 0,0 };
	clearPos = { SCREEN_SIZE_X, SCREEN_SIZE_Y / 4 };

	stageInit();
	PlayerInit();
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		EnemyInit(i);
	}
	ShotInit();
}

//タイトルの処理
void GameTitle(void)
{
	GameTitleDraw();
}

void GameTitleDraw(void)
{
	XY titlePos = { 0,0 };

	DrawString(0, 0, "GameTitle", 0xffffff);
	for (int y = 0; y < MAP_CHIP_Y; y++) {
		for (int x = 0; x < 30; x++) {
			DrawGraph(MAP_CHIP_SIZE_X * x + haikeiPos.x, MAP_CHIP_SIZE_Y * y, haikeiImage[haikeiData[y][x]], true);
		}
	}
	DrawGraph(titlePos.x, titlePos.y, titleImage, true);
	
}

void GameLife(void)
{
	GameLifeDraw();
}

void GameLifeDraw(void)
{
	DrawGraph(SCREEN_SIZE_X / 2 - 32, SCREEN_SIZE_Y / 2, pImage, true);
	DrawFormatString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 0xffffff, " x  %d", life);

	clearPos = { SCREEN_SIZE_X, SCREEN_SIZE_Y / 4 };

	/*cnt++;
	if (cnt > 150) {
		gameMode = GMODE_GAME;
	}*/
}

//ゲームのメイン処理
void GameMain(void)
{
	//ポーズ処理
	if (trgkey[P1_PAUSE]) {
		pauseFlag = !pauseFlag;	//0 = 1
	}
	if (pauseFlag) {	//1の時、処理を行う
		SetDrawBright(128, 128, 128);
	}
	else {
		stageUpdate();
		PlayerUpdate();
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			EnemyUpdate(i);
		}
		ShotUpdate();
		//HitCheck();
	}

	GameMainDraw();

	if (pauseFlag) {	//1の時、処理を行う
		SetDrawBright(255, 255, 255);
		DrawString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, "PAUSE", 0xfff00f);
	}

	if (!pauseFlag) {	//0の時、処理を行う
		gameCounter++;
	}

	//プレイヤーがゴールしたか
	if (PlayerGoal() == true) {
		gameMode = GMODE_SCLEAR;
	}

	//プレイヤーが死亡した
	if (PlayerOver() == true) {
		cnt++;
		if (cnt == 1) {
			PlayerDEffect();
		}
		if (cnt < 100) {
			PlayerDEffectDraw();
		}
		else {
			life--;
			cnt = 0;
			if (life >= 0) {
				PlayerInit();
				for (int i = 0; i < ENEMY_MAX; i++)
				{
					EnemyInit(i);
				}
				gameMode = GMODE_LIFE;
			}
			else {
				life = lifeMax;
				StageCntInit();
				gameMode = GMODE_OVER;
			}
		}
	}
	
}

void GameMainDraw(void)
{
	stageDraw();
	PlayerDraw();
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		EnemyDraw(i);
	}
	ShotDraw();
	DrawFormatString(0, 0, 0xffffff, "GameMain : %d", gameCounter);
	DrawFormatString(0, 32, 0xff00ff, "cnt : %d", cnt);
}

//ステージクリア
void GameSClear(void)
{
	stageDraw();
	
	PlayerGoalDraw();
	
	//クリア画像を動かす
	if (clearPos.x > SCREEN_SIZE_X / 2) {
		clearPos.x -= 5;
	}
	else {
		clearPos.x = SCREEN_SIZE_X / 2;
	}

	DrawGraph(clearPos.x, clearPos.y, clearImage, true);
	DrawString(0, 0, "GameSClear", 0xffffff);

	if (PlayerNextStage() == true) {
		stageInit();
		PlayerInit();
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			EnemyInit(i);
		}
		gameMode = GMODE_LIFE;
	}
}

//クリアー処理
void GameClear(void)
{

}

//ゲームオーバー処理
void GameOver(void)
{
	GameOverDraw();
}

void GameOverDraw(void)
{
	DrawGraph(0, 0, gameoverImage, true);
	DrawString(0, 0, "GAME OVER", 0xffffff, true);
}


bool FadeInScreen(int fadeStep)
{
	fadeCnt += fadeStep;
	if (fadeCnt <= 255) {
		SetDrawBright(fadeCnt, fadeCnt, fadeCnt);
		return true;	//しているとき
	}
	else {
		SetDrawBright(255, 255, 255);
		fadeCnt = 0;
		return false;	//していないとき
	}
}

bool FadeOutScreen(int fadeStep)
{
	fadeCnt += fadeStep;
	if (fadeCnt <= 255) {
		SetDrawBright(255 - fadeCnt, 255 - fadeCnt, 255 - fadeCnt);
		return true;	//しているとき
	}
	else {
		SetDrawBright(0, 0, 0);
		fadeCnt = 0;
		return false;	//していないとき
	}
}
