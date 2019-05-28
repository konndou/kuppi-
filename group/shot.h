#pragma once

#define SHOT_MAX 1

//プロトタイプ宣言
void ShotSystemInit(void);
void ShotInit(void);
void ShotUpdate(void);
void ShotDraw(void);

void Deleteshot(void);

XY GetShotPos(void);

void Shot(XY pos, MOVE_DIR dir);

bool shotHitCheck(XY bPos, XY bSize);