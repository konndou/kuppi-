#pragma once

#include <DxLib.h>
#include <math.h>

//���ޯ��p���b�Z�[�W
#ifdef _DEBUG
#define AST() {\
	CHAR ast_mes[256];\
	wsprintf(ast_mes, "%s %d�s��\0", __FILE__, __LINE__);\
	MessageBox(0, ast_mes, "���ĕ\��", MB_OK);\
	}
#else
#define AST()
#endif

#define PI 3.141592		//�~����

#define SCREEN_SIZE_X 960
#define SCREEN_SIZE_Y 640

#define ACC_G 10
#define INIT_VELOCITY 50		//�����x
#define SECOND_PER_FRAME 0.2	//1�t���[���̕b��

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

<<<<<<< HEAD


=======
>>>>>>> 089080dbbb8f5c2118173d5d57ae01c516ede1df
typedef struct {
	MOVE_DIR movedir;	//�����Ă������
	XY pos;				//�L�����N�^�̈ʒu(���S)
	XY move;
	XY size;			//�L�����N�^�摜�̃T�C�Y
	XY sizeOffset;		//�L�����N�^��������̍���ʒu
	XY hitPosS;			//�����蔻��p�̍���
	XY hitPosE;			//�����蔻��p�̉E��
	int flagcnt;
	bool runFlag;		//�L�����N�^�̏��(�����Ă��邩)
	bool jumpFlag;		//�L�����N�^�̏��(�W�����v���Ă��邩)
	bool shotFlag;		//�L�����N�^�̏��(�e�������Ă��邩)
	bool damageFlag;	//�L�����N�^�̏��(�_���[�W���󂯂Ă��邩)
	bool gFlag;			//�S�[���������̉��o�p�t���O
	bool xFlag;			//�S�[���������̉��o�p�t���O
	int moveSpeed;		//�L�����N�^�̈ړ���
	int life;			//�L�����N�^�̗̑�
	int lifeMax;		//�L�����N�^�̗͍̑ő�
	int animCnt;		//�L�����N�^�̃A�j���[�V�����p�J�E���^
	int imgLockCnt;		//�L�����N�^�̃C���[�W�Œ�p�J�E���^
	int type;			//���炩�̑������i�[�ł���
	int poscnt;
	bool flag;			//�L�����N�^�[�̃t���O
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