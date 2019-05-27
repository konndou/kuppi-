
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

//�^�C�g��
int titleImage;
int titleCnt;
int pauseFlag;
int startImage;
int playerstopImage2;
int playerstopImage3;

int gameoverImage;

int clearImage;

int stageselectImage[6];

//�v���C���[
int pImage;

//�X�e�[�W
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
int se;
int deathse;	//���񂾂Ƃ��̃T�E���h
int cnt = 0;
auto cnttime = 30000;

//�������ߐ錾
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

// ========== WinMain�֐� 
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SystemInit();
	

	// ---------- �ް�ٰ�� 
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();	// ��ʏ��� 

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

		// Ҳݏ��� 
		ScreenFlip();		// ����ʂ�\��ʂɏu�Ժ�߰ 
	}
	gameMode = GMODE_INIT;

	DxLib_End();			// DXײ���؂̏I������ 
	return 0;				// ������۸��т̏I��
}

int SystemInit(void)
{
	// ---------- ���я��� 
	SetWindowText("Shooting_kadai");
	// ���я��� 
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 800�~600�ޯ�65536�FӰ�ނɐݒ� 
	ChangeWindowMode(true);		// true:window false:�ٽ�ذ�
	//ChangeWindowMode(false); 
	if (DxLib_Init() == -1) return -1;					// DXײ���؏��������� 
	SetDrawScreen(DX_SCREEN_BACK);					// �ЂƂ܂��ޯ��ޯ̧�ɕ`�� 

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

	// ---------- �O���t�B�b�N�̓o�^ ----------- 
	titleImage = LoadGraph("image/titlekuppi-.png");
	gameoverImage = LoadGraph("image/gameover.png");
	clearImage = LoadGraph("image/clear.png");
	LoadDivGraph("image/mapchip7.png", 30, 30, 1, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, haikeiImage);
	pImage = LoadGraph("image/playerstop.png");
	startImage = LoadGraph("image/start.png");
	playerstopImage2 = LoadGraph("image/playerstop2.png");
	playerstopImage3 = LoadGraph("image/playerstop3.png");


	//�T�E���h
	se = LoadSoundMem("bgm/stage1.mp3");
	ChangeVolumeSoundMem(180, se);
	deathse = LoadSoundMem("bgm/death.mp3");

	//�X�e�[�W�Z���N�g�摜
	stageselectImage[0] = LoadGraph("image/stage1gazo.png", true);
	stageselectImage[1] = LoadGraph("image/stage2gazo.png", true);
	stageselectImage[2] = LoadGraph("image/stage3gazo.png", true);
	stageselectImage[3] = LoadGraph("image/stage4gazo.png", true);
	stageselectImage[4] = LoadGraph("image/stage5gazo.png", true);
	stageselectImage[5] = LoadGraph("image/stage6gazo.png", true);
}

void GameInit(void)
{
	// ----------- �ϐ������� ---------- 
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
}

//�^�C�g���̏���
void GameTitle(void)
{
	GameTitleDraw();
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
	//DrawFormatString(SCREEN_SIZE_X / 2-100,450, 0xffffff, "P U S H   S P A C E K E Y", gameCounter);
	startcnt++;
	if (startcnt / 24 % 3)
	{
		DrawGraph(SCREEN_SIZE_X / 2 - 150, 450, startImage, true);
		DrawGraph(SCREEN_SIZE_X / 2 - 182, 455, playerstopImage2, true);
		DrawTurnGraph(SCREEN_SIZE_X / 2 +150, 455, playerstopImage3, true);

	}
	
}

//�X�e�[�W�Z���N�g
void GameSelect(void)
{
	StageSelect();
	GameSelectDraw();
}

void GameSelectDraw(void)
{
	auto stagecnt = GetStageCnt();
	switch (stagecnt) {
	case 0:
		DrawString(200, SCREEN_SIZE_Y / 4, "stage  =  map 1", 0xffffff, true);
		DrawGraph(200, SCREEN_SIZE_Y / 3, stageselectImage[0], true);
		break;
	case 1:
		DrawString(200, SCREEN_SIZE_Y / 4, "stage  =  map 2", 0xffffff, true);
		DrawGraph(200, SCREEN_SIZE_Y / 3, stageselectImage[1], true);
		break;
	case 2:
		DrawString(200, SCREEN_SIZE_Y / 4, "stage  =  map ENEMY", 0xffffff, true);
		DrawGraph(200, SCREEN_SIZE_Y / 3, stageselectImage[2], true);
		break;
	case 3:
		DrawString(200, SCREEN_SIZE_Y / 4, "stage  =  map HARD", 0xffffff, true);
		DrawGraph(200, SCREEN_SIZE_Y / 3, stageselectImage[3], true);
		break;
	case 4:
		DrawString(200, SCREEN_SIZE_Y / 4, "stage  =  map BOSS", 0xffffff, true);
		DrawGraph(200, SCREEN_SIZE_Y / 3, stageselectImage[4], true);
		break;
	case 5:
		DrawString(200, SCREEN_SIZE_Y / 4, "stage  =  map EX STAGE", 0xffffff, true);
		DrawGraph(200, SCREEN_SIZE_Y / 3, stageselectImage[5], true);
		break;
	}
	
}

//�v���C���[���C�t
void GameLife(void)
{
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

//�Q�[���̃��C������
void GameMain(void)
{
	//�|�[�Y����
	if (trgkey[P1_PAUSE]) {
		pauseFlag = !pauseFlag;	//0 = 1
	}
	if (pauseFlag) {	//1�̎��A�������s��
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

	if (pauseFlag) {	//1�̎��A�������s��
		SetDrawBright(255, 255, 255);
		DrawString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, "PAUSE", 0xfff00f);
	}

	if (!pauseFlag) {	//0�̎��A�������s��
		gameCounter++;
	}

	//�v���C���[���S�[��������
	if (PlayerGoal() == true) {
		gameMode = GMODE_SCLEAR;
	}

	//�v���C���[�����S����
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
				StageCntInit();
				gameMode = GMODE_OVER;
			}
		}
	}
	
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

	cnttime -= 2;
	DrawFormatString(850, 32, 0xff00ff, "time  %d", cnttime / 100);
}

//�X�e�[�W�N���A
void GameSClear(void)
{
	stageDraw();
	
	PlayerGoalDraw();
	
	//�N���A�摜�𓮂���
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
		gameMode = GMODE_LIFE;
	}
}

//�N���A�[����
void GameClear(void)
{
	StageCntInit();
	DrawString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, "CLEAR", 0xffffff, true);
}

//�Q�[���I�[�o�[����
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
		return true;	//���Ă���Ƃ�
	}
	else {
		SetDrawBright(255, 255, 255);
		fadeCnt = 0;
		return false;	//���Ă��Ȃ��Ƃ�
	}
}

bool FadeOutScreen(int fadeStep)
{
	fadeCnt += fadeStep;
	if (fadeCnt <= 255) {
		SetDrawBright(255 - fadeCnt, 255 - fadeCnt, 255 - fadeCnt);
		return true;	//���Ă���Ƃ�
	}
	else {
		SetDrawBright(0, 0, 0);
		fadeCnt = 0;
		return false;	//���Ă��Ȃ��Ƃ�
	}
}
