
#include "main.h"
#include "keyCheck.h"
#include "player1.h"
#include "stage.h"
#include "enemy.h"
#include "shot.h"


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

//�^�C�g��
int titleImage;
int titleCnt;
int pauseFlag;

int gameoverImage;

int clearImage;

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
{ 14, 15, 15, 15, 15, 15,  15, 15, 15, 15, 15, 15,  15, 15, 15, 15, 15, 15,  15, 15, 15, 15, 15, 15,  15, 15, 15, 15, 15, 16},
{ 20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20},
{ 17, 18, 18, 18, 18, 18,  18, 18, 18, 18, 18, 18,  18, 18, 18, 18, 18, 18,  18, 18, 18, 18, 18, 18,  18, 18, 18, 18, 18, 19},
};

XY clearPos;
XY haikeiPos;
int life = 3;
int se;
int cnt = 0;

//�������ߐ錾
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

	fadeIn = false;
	fadeOut = false;

	// ---------- �O���t�B�b�N�̓o�^ ----------- 
	titleImage = LoadGraph("image/title.png");
	gameoverImage = LoadGraph("image/gameover.png");
	clearImage = LoadGraph("image/clear.png");
	LoadDivGraph("image/mapchip2.png", 30, 30, 1, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, haikeiImage);
	pImage = LoadGraph("image/playerstop.png");

	se = LoadSoundMem("bgm/stage1.mp3");
}

void GameInit(void)
{
	// ----------- �ϐ������� ---------- 
	titleCnt = 0;
	fadeCnt = 0;
	pauseFlag = false;

	haikeiPos = { 0,0 };
	clearPos = { SCREEN_SIZE_X, SCREEN_SIZE_Y / 4 };

	stageInit();
	PlayerInit();
	EnemyInit();
}

//�^�C�g���̏���
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

	/*cnt++;
	if (cnt > 150) {
		gameMode = GMODE_GAME;
	}*/
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
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			EnemyUpdate(i);
		}
		//HitCheck();
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
				EnemyInit();
				gameMode = GMODE_LIFE;
			}
			else {
				life = 3;
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
	DrawFormatString(0, 0, 0xffffff, "GameMain : %d", gameCounter);
	DrawFormatString(0, 32, 0xff00ff, "cnt : %d", cnt);
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
		EnemyInit();
		gameMode = GMODE_LIFE;
	}
}

//�N���A�[����
void GameClear(void)
{

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
