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

//--------------��۰��ٕϐ�
extern bool newkey[KEY_MAX];	//�����ڰтł̓��͏��
extern bool trgkey[KEY_MAX];	//�ض޷��̏��
extern bool upkey[KEY_MAX];		//���߷��̏��
extern bool oldkey[KEY_MAX];	//�ض޷��v�Z�p

//--------------�������ߐ錾

//ketcheck.cpp

void KeyCheck(void);	//�����͏�Ԃ̃`�F�b�N
void KeyCheckSystemInit(void);