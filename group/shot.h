#pragma once

#define SHOT_MAX 2

//プロトタイプ宣言
void ShotSystemInit(void);
void ShotInit(void);
void ShotUpdate(void);
void ShotDraw(void);

void Shot(XY pos, MOVE_DIR dir);