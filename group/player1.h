#pragma once

#define PLAYER_SIZE_X 32
#define PLAYER_SIZE_Y 32

#define ACC_RUN 0.18	//ëñÇÈâ¡ë¨ìx
#define ACC_STOP 0.10	//í‚Ç‹ÇÈâ¡ë¨ìx
#define VELOCITY_X_MAX 5//Xï˚å¸ÇÃë¨ìxç≈ëÂ

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