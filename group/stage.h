#pragma once

#define MAP_CHIP_X 300
#define MAP_CHIP_Y 20

#define MAP_CHIP_SIZE_X 32
#define MAP_CHIP_SIZE_Y 32

//プロトタイプ宣言
void stageSystemInit(void);
void stageInit(void);
void stageUpdate(void);
void stageDraw(void);

void StageCntInit(void);
void StageSelect(void);
XY MapPosToIndex(XY pos);
XY MapIndexToPos(XY Index);
bool IsPass(XY pos);
bool IsGPass(XY pos);
bool IsGoalPass(XY pos);
bool IsGoal2Pass(XY pos);
bool IsNextPass(XY pos);
bool IsOverPass(XY pos);
bool IsEnemyPass(XY pos);
bool ItemEvent(XY pos);

XY GetMapPos(void);