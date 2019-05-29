
#include "main.h"
#include "keyCheck.h"
#include "player1.h"
#include "stage.h"
#include "enemy.h"
#include "shot.h"
#include "boss.h"
#include "item.h"
#include "effect.h"


typedef enum {
	GMODE_INIT,
	GMODE_TITLE,
	GMODE_SELECT,
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
int startcnt;

//タイトル
int titleImage;
int titleCnt;
int titlese;
int pauseFlag;
int startImage;
int playerstopImage2;
int playerstopImage3;
int selectImage;
int bossselectImage;
int stageclearImage;

//ゲームオーバー
int gameoverImage;
int gameoverse;

//クリア
int clearImage;

//ステージセレクト
int stageselectImage[6];
int stageselectImage2[6];
int selectImage2[6];

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
{ 14, 15, 15, 15, 15, 15,  15, 15, 15, 15, 15, 15,  15, 15, 15, 15, 15, 15,  15, 15, 15, 15, 15, 15,  15, 15, 15, 15, 15, 15},
{ 20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20},
{ 17, 18, 18, 18, 18, 18,  18, 18, 18, 18, 18, 18,  18, 18, 18, 18, 18, 18,  18, 18, 18, 18, 18, 18,  18, 18, 18, 18, 18, 18},
};

XY clearPos;
XY haikeiPos;
int lifeMax = 5;
int life;
int se[6];
int deathse;	//死んだときのサウンド
int cnt = 0;
int cnttime;	//ステージのタイム	

//ﾌﾟﾛﾄﾀｲﾌﾟ宣言
int SystemInit(void);
void GameInit(void);
void GameTitle(void);
void GameTitleDraw(void);
void GameSelect(void);
void GameSelectDraw(void);
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
			StopSoundMem(gameoverse);
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
					gameMode = GMODE_SELECT;
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

		case GMODE_SELECT:
			GameSelect();
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
			if (fadeIn) {
				if (!FadeInScreen(5)) {
					fadeIn = false;
				}
			}
			break;

		case GMODE_SCLEAR:
			GameSClear();
			break;

		case GMODE_CLEAR:
			GameClear();
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
	ItemSystemInit();
	BossSystemInit();
	EffectSystemInit();
	fadeIn = false;
	fadeOut = false;

	// ---------- グラフィックの登録 ----------- 
	titleImage = LoadGraph("image/titlekuppi-.png");
	gameoverImage = LoadGraph("image/gameover.png");
	clearImage = LoadGraph("image/flag.png");
	LoadDivGraph("image/mapchip7.png", 30, 30, 1, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, haikeiImage);
	pImage = LoadGraph("image/playerstop.png");
	startImage = LoadGraph("image/start.png");
	playerstopImage2 = LoadGraph("image/playerstop2.png");
	playerstopImage3 = LoadGraph("image/playerstop3.png");
	selectImage = LoadGraph("image/select.png");
	stageclearImage = LoadGraph("image/clear2.png");
	

	//ステージセレクト画像
	stageselectImage[0] = LoadGraph("image/stage1gazo.png", true);
	stageselectImage[1] = LoadGraph("image/stage2gazo.png", true);
	stageselectImage[2] = LoadGraph("image/stage3gazo.png", true);
	stageselectImage[3] = LoadGraph("image/stage4gazo.png", true);
	stageselectImage[4] = LoadGraph("image/stage5gazo.png", true);
	stageselectImage[5] = LoadGraph("image/stage6gazo.png", true);

	stageselectImage2[0] = LoadGraph("image/select1.png", true);
	stageselectImage2[1] = LoadGraph("image/select2.png", true);
	stageselectImage2[2] = LoadGraph("image/select3.png", true);
	stageselectImage2[3] = LoadGraph("image/select4.png", true);
	stageselectImage2[4] = LoadGraph("image/bossselect2.png", true);
	stageselectImage2[5] = LoadGraph("image/select6.png", true);

	//サウンド
	se[0] = LoadSoundMem("bgm/stage1.mp3");
	se[1] = LoadSoundMem("bgm/stage2.mp3");
	se[2] = LoadSoundMem("bgm/stage3.mp3");
	se[3] = LoadSoundMem("bgm/stage4.mp3");
	se[4] = LoadSoundMem("bgm/boss.mp3");
	se[5] = LoadSoundMem("bgm/stage5.mp3");
	for (int i = 0; i < 6; i++) {
		ChangeVolumeSoundMem(180, se[i]);
	}

	deathse = LoadSoundMem("bgm/death.mp3");
	titlese = LoadSoundMem("bgm/title.mp3");
	gameoverse = LoadSoundMem("bgm/gameover.mp3");
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

	
	PlayerInit();
	for (int i = 0; i < ENEMY_MAX; i++) {
		EnemyInit(i);
	}
	ShotInit();
	ItemInit();
	EffectInit();

	cnttime = 45000;
}

//タイトルの処理
void GameTitle(void)
{
	GameTitleDraw();
	PlaySoundMem(titlese, DX_PLAYTYPE_BACK, false);
	PlaySoundMem(titlese, DX_PLAYTYPE_LOOP, false);
}

void GameTitleDraw(void)
{
	XY titlePos = { SCREEN_SIZE_X/4-60,50 };
	
	DrawString(0, 0, "GameTitle", 0xffffff);
	for (int y = 0; y < MAP_CHIP_Y; y++) {
		for (int x = 0; x < 30; x++) {
			DrawGraph(MAP_CHIP_SIZE_X * x + haikeiPos.x, MAP_CHIP_SIZE_Y * y, haikeiImage[haikeiData[y][x]], true);
		}
	}


	DrawGraph(titlePos.x, titlePos.y, titleImage, true);

	startcnt++;
	if (startcnt / 24 % 3)
	{
		DrawGraph(SCREEN_SIZE_X / 2 - 150, 450, startImage, true);
		DrawGraph(SCREEN_SIZE_X / 2 - 182, 455, playerstopImage2, true);
		DrawTurnGraph(SCREEN_SIZE_X / 2 +150, 455, playerstopImage3, true);

	}
	
}

//ステージセレクト
void GameSelect(void)
{
	StopSoundMem(titlese);
	StageSelect();
	GameSelectDraw();
}

void GameSelectDraw(void)
{
	DrawGraph(0, 0, selectImage, true);

	auto stagecnt = GetStageCnt();
	switch (stagecnt) {
	case 0:
		DrawGraph(200, SCREEN_SIZE_Y / 4, stageselectImage[0], true);
		DrawGraph(200, SCREEN_SIZE_Y / 10 - 20, stageselectImage2[0], true);
		break;
	case 1:
		DrawGraph(200, SCREEN_SIZE_Y / 4, stageselectImage[1], true);
		DrawGraph(200, SCREEN_SIZE_Y / 10 - 20, stageselectImage2[1], true);
		break;
	case 2:
		DrawGraph(200, SCREEN_SIZE_Y / 4, stageselectImage[2], true);
		DrawGraph(200, SCREEN_SIZE_Y / 10 - 20, stageselectImage2[2], true);
		break;
	case 3:
		DrawGraph(200, SCREEN_SIZE_Y / 4, stageselectImage[3], true);
		DrawGraph(200, SCREEN_SIZE_Y / 10 - 20, stageselectImage2[3], true);
		break;
	case 4:
		DrawGraph(200, SCREEN_SIZE_Y / 4, stageselectImage[4], true);
		DrawGraph(200, SCREEN_SIZE_Y / 10 - 20, stageselectImage2[4], true);
		break;
	case 5:
		DrawGraph(200, SCREEN_SIZE_Y / 4, stageselectImage[5], true);
		DrawGraph(200, SCREEN_SIZE_Y / 10 - 20, stageselectImage2[5], true);
		break;
	}
	
}

//プレイヤーライフ
void GameLife(void)
{
	cnttime = 45000;
	stageInit();
	BossInit();
	GameLifeDraw();
}

void GameLifeDraw(void)
{
	DrawGraph(SCREEN_SIZE_X / 2 - 32, SCREEN_SIZE_Y / 2, pImage, true);
	DrawFormatString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 0xffffff, " x  %d", life);

	clearPos = { SCREEN_SIZE_X, SCREEN_SIZE_Y / 4 };
}

//ゲームのメイン処理
void GameMain(void)
{
	auto stagecnt = GetStageCnt();
	PlaySoundMem(se[stagecnt], DX_PLAYTYPE_BACK, false);
	PlaySoundMem(se[stagecnt], DX_PLAYTYPE_LOOP, false);

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
		auto stagecnt = GetStageCnt();
		switch (stagecnt) {
		case 0:
			for (int i = 0; i < 10; i++)
			{
				EnemyUpdate(i);
			}
			break;
		case 2:
			for (int i = 0; i < ENEMY_MAX; i++)
			{
				EnemyUpdate(i);
			}
			break;
		case 4:
			for (int i = 0; i < 20; i++)
			{
				EnemyUpdate(i);
			}
			break;
		default:
			break;
		}
		ShotUpdate();
		BossUpdate();
		ItemUpdate();
		EffectUpdata();
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
		PlaySoundMem(deathse, DX_PLAYTYPE_BACK, false);
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
				stageInit();
				ItemInit();
				gameMode = GMODE_LIFE;
			}
			else {
				life = lifeMax;
				auto stagecnt = GetStageCnt();
				StopSoundMem(se[stagecnt]);
				StageCntInit();
				gameMode = GMODE_OVER;
			}
		}
	}

	//タイムオーバー
	if (cnttime == 0) {
		cnttime = 0;
		cnt++;
		PlaySoundMem(deathse, DX_PLAYTYPE_BACK, false);
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
				stageInit();
				ItemInit();
				gameMode = GMODE_LIFE;
			}
			else {
				life = lifeMax;
				auto stagecnt = GetStageCnt();
				StopSoundMem(se[stagecnt]);
				StageCntInit();
				gameMode = GMODE_OVER;
			}
		}
	}
	else {
		cnttime -= 2;
	}
	
	//ボスを倒した後のクリア画面
	if (BossClear() == true) {
		gameMode = GMODE_CLEAR;
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
	BossDraw();
	ItemDraw();
	EffectDraw();
	
	auto stagecnt = GetStageCnt();
	DrawFormatString(0, 0, 0xffffff, "stage  =  %d", stagecnt);

	DrawFormatString(850, 0, 0xffffff, "time  %d", cnttime / 100);

}

//ステージクリア
void GameSClear(void)
{
	auto stagecnt = GetStageCnt();
	StopSoundMem(se[stagecnt]);

	stageDraw();

	stageUpdate();
	
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
		BossInit();
		ItemInit();
		life = 5;
		auto stageCnt = GetStageCnt();
		if (stageCnt > 5) {
			gameMode = GMODE_CLEAR;
		}
		else {
			gameMode = GMODE_LIFE;
		}

	}
}

//クリアー処理
void GameClear(void)
{
	auto stagecnt = GetStageCnt();
	StopSoundMem(se[stagecnt]);

	StageCntInit();
	//DrawString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, "CLEAR", 0xffffff, true);
	DrawGraph(0, 0, stageclearImage, true);
}

//ゲームオーバー処理
void GameOver(void)
{
	cnttime = 45000;
	GameOverDraw();
	PlaySoundMem(gameoverse, DX_PLAYTYPE_BACK, false);
	PlaySoundMem(gameoverse, DX_PLAYTYPE_LOOP, false);
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
