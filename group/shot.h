#pragma once

#define SHOT_MAX 1

//�v���g�^�C�v�錾
void ShotSystemInit(void);
void ShotInit(void);
void ShotUpdate(void);
void ShotDraw(void);

void Shot(XY pos, MOVE_DIR dir);