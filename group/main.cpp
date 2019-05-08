
#include "main.h"
#include "keyCheck.h"
#include "player1.h"
#include "stage.h"


typedef enum {
	GMODE_INIT,
	GMODE_TITLE,
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

//ステージ

int haikeiImage[35];
int haikeiData[20][30] = {
{ 9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9},
{ 9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9},
{ 9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9},
{ 9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9},
{ 9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9},

{ 9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9},
{ 9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9},
{ 9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9},
{ 9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9},
{ 9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9},

{ 9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9},
{ 9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9},
{ 9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9},
{ 9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9},
{ 9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9},

{ 9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9},
{ 9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9,  9, 9, 9, 9, 9, 9},
{ 14, 15, 15, 15, 15, 15,  15, 15, 15, 15, 15, 15,  15, 15, 15, 15, 15, 15,  15, 15, 15, 15, 15, 15,  15, 15, 15, 15, 15, 16},
{ 24, 24, 24, 24, 24, 24,  24, 24, 24, 24, 24, 24,  24, 24, 24, 24, 24, 24,  24, 24, 24, 24, 24, 24,  24, 24, 24, 24, 24, 24},
{ 21, 22, 22, 22, 22, 22,  22, 22, 22, 22, 22, 22,  22, 22, 22, 22, 22, 22,  22, 22, 22, 22, 22, 22,  22, 22, 22, 22, 22, 23},
};

XY haikeiPos;

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
			if (fadeIn) {
				if (!FadeInScreen(5)) {
					fadeIn = false;
				}
			}
			
			if (trgkey[KEY_START]) {
				gameMode = GMODE_OVER;
			}
			break;

		case GMODE_SCLEAR:
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

	fadeIn = false;
	fadeOut = false;

	// ---------- グラフィックの登録 ----------- 
	titleImage = LoadGraph("image/title.png");
	LoadDivGraph("image/mapchip.png", 28, 7, 4, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, haikeiImage);
}

void GameInit(void)
{
	// ----------- 変数初期化 ---------- 
	titleCnt = 0;
	fadeCnt = 0;
	pauseFlag = false;

	haikeiPos = { 0,0 };

	stageInit();
	PlayerInit();

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

	if (PlayerGoal() == true) {
		gameMode = GMODE_SCLEAR;
	}
}

void GameMainDraw(void)
{
	stageDraw();
	
	PlayerDraw();
	DrawFormatString(0, 0, 0xffffff, "GameMain : %d", gameCounter);
}

//ステージクリア
void GameSClear(void)
{
	stageDraw();
	
	PlayerGoalDraw();
	DrawString(0, 0, "GameSClear", 0xffffff);
	if (PlayerNextStage() == true) {
		stageInit();
		PlayerInit();
		gameMode = GMODE_GAME;
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
