#include "main.h"
#include "KeyCheck.h"

bool newkey[KEY_MAX];	//new��(�����ڰт̷����͏�)
bool trgkey[KEY_MAX];	//trg��(�O�񉟂��ĂȂ��č��񉟂������̏�)
bool upkey[KEY_MAX];	//up��(�O�񉟂��Ă��č��񉟂��Ă��Ȃ����̏�)
bool oldkey[KEY_MAX];	//old��(����̓��͏�Ԃ�����̔��f�p�ɕۑ�)

void KeyCheckSystemInit(void)
{
	for (int i = 0; i < KEY_MAX; i++) {
		newkey[i] = false;		//�S�������Ă��Ȃ����Ƃɂ���
		trgkey[i] = false;		//�S�������Ă��Ȃ����Ƃɂ���
		upkey[i] = false;		//�S�������Ă��Ȃ����Ƃɂ���
		oldkey[i] = false;
	}
}

void KeyCheck(void)
{
	//--------�n�߂̏���
	for (int i = 0; i < KEY_MAX; i++) {
		newkey[i] = false;		//�S�������Ă��Ȃ����Ƃɂ���
		trgkey[i] = false;		//�S�������Ă��Ȃ����Ƃɂ���
		upkey[i] = false;		//�S�������Ă��Ȃ����Ƃɂ���
	}

	//-------new��(���񉟂������ǂ����̔��f)
	if (CheckHitKey(KEY_INPUT_UP)) newkey[P1_UP] = true;
	if (CheckHitKey(KEY_INPUT_RIGHT)) newkey[P1_RIGHT] = true;
	if (CheckHitKey(KEY_INPUT_DOWN)) newkey[P1_DOWN] = true;
	if (CheckHitKey(KEY_INPUT_LEFT)) newkey[P1_LEFT] = true;
	if (CheckHitKey(KEY_INPUT_LSHIFT)) newkey[P1_A] = true;
	if (CheckHitKey(KEY_INPUT_RCONTROL)) newkey[P1_B] = true;
	if (CheckHitKey(KEY_INPUT_B)) newkey[P1_PAUSE] = true;
	if (CheckHitKey(KEY_INPUT_E)) newkey[P1_JUMP] = true;

	if (CheckHitKey(KEY_INPUT_W)) newkey[P2_UP] = true;
	if (CheckHitKey(KEY_INPUT_D)) newkey[P2_RIGHT] = true;
	if (CheckHitKey(KEY_INPUT_S)) newkey[P2_DOWN] = true;
	if (CheckHitKey(KEY_INPUT_A)) newkey[P2_LEFT] = true;
	if (CheckHitKey(KEY_INPUT_RSHIFT)) newkey[P2_A] = true;
	if (CheckHitKey(KEY_INPUT_LCONTROL)) newkey[P2_B] = true;
	if (CheckHitKey(KEY_INPUT_V)) newkey[P2_PAUSE] = true;
	if (CheckHitKey(KEY_INPUT_M)) newkey[P2_JUMP] = true;

	if (CheckHitKey(KEY_INPUT_SPACE))newkey[KEY_START] = true;
	//---------trgkey & upkey & oldkey
	for (int i = 0; i < KEY_MAX; i++) {
		trgkey[i] = newkey[i] & ~oldkey[i];	//trgkey
		upkey[i] = ~newkey[i] & oldkey[i];	//upkey
		oldkey[i] = newkey[i];				//oldkey
	}
}