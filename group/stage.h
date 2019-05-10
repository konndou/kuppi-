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

XY MapPosToIndex(XY pos);
XY MapIndexToPos(XY Index);
bool IsPass(XY pos);
bool IsGPass(XY pos);
bool IsGoalPass(XY pos);
bool IsNextPass(XY pos);
bool IsOverPass(XY pos);

XY GetMapPos(void);