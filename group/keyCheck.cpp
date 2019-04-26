#include "main.h"
#include "KeyCheck.h"

bool newkey[KEY_MAX];	//newｷｰ(今回ﾌﾚｰﾑのｷｰ入力状況)
bool trgkey[KEY_MAX];	//trgｷｰ(前回押してなくて今回押したかの状況)
bool upkey[KEY_MAX];	//upｷｰ(前回押していて今回押していないかの状況)
bool oldkey[KEY_MAX];	//oldｷｰ(今回の入力状態を次回の判断用に保存)

void KeyCheckSystemInit(void)
{
	for (int i = 0; i < KEY_MAX; i++) {
		newkey[i] = false;		//全部押していないことにする
		trgkey[i] = false;		//全部押していないことにする
		upkey[i] = false;		//全部押していないことにする
		oldkey[i] = false;
	}
}

void KeyCheck(void)
{
	//--------始めの準備
	for (int i = 0; i < KEY_MAX; i++) {
		newkey[i] = false;		//全部押していないことにする
		trgkey[i] = false;		//全部押していないことにする
		upkey[i] = false;		//全部押していないことにする
	}

	//-------newｷｰ(今回押したかどうかの判断)
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