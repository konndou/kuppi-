#pragma once
#pragma once

enum KEY_MODE {
	P1_UP,
	P1_RIGHT,
	P1_DOWN,
	P1_LEFT,
	P1_A,
	P1_B,
	P1_PAUSE,
	P1_JUMP,

	P2_UP,
	P2_RIGHT,
	P2_DOWN,
	P2_LEFT,
	P2_A,
	P2_B,
	P2_PAUSE,
	P2_JUMP,

	KEY_START,
	KEY_MAX
};

//--------------ｸﾞﾛｰﾊﾞﾙ変数
extern bool newkey[KEY_MAX];	//今回ﾌﾚｰﾑでの入力状態
extern bool trgkey[KEY_MAX];	//ﾄﾘｶﾞｷｰの状態
extern bool upkey[KEY_MAX];		//ｱｯﾌﾟｷｰの状態
extern bool oldkey[KEY_MAX];	//ﾄﾘｶﾞｷｰ計算用

//--------------ﾌﾟﾛﾄﾀｲﾌﾟ宣言

//ketcheck.cpp

void KeyCheck(void);	//ｷｰ入力状態のチェック
void KeyCheckSystemInit(void);