#pragma once

#define PLAYER_SIZE_X 32
#define PLAYER_SIZE_Y 32

#define ACC_RUN 0.18	//��������x
#define ACC_STOP 0.10	//��܂�����x
#define VELOCITY_X_MAX 5//X�����̑��x�ő�

void PlayerSystemInit(void);
void PlayerInit(void);
void PlayerUpdate(void);
void PlayerDraw(void);
void PlayerGoalDraw(void);

//bool Player1HitCheck(XY sPos, XY sSize);
CHARACTER GetPlayerPos(void);

bool PlayerGoal(void);
bool PlayerNextStage(void);
bool PlayerOver(void);
void PlayerDEffect(void);
void PlayerDEffectDraw(void);
void PlayerBigFlagInit(void);