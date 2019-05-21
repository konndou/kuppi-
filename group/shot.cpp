
#include "main.h"
#include "shot.h"
#include "enemy.h"
#include "player1.h"
#include "keyCheck.h"
#include "stage.h"

CHARACTER shot[SHOT_MAX];
CHARACTER shot2[SHOT_MAX];
int shotImage;
int sdir;

void ShotSystemInit(void)
{
	shotImage = LoadGraph("image/bullet2.png");
}

//������
void ShotInit(void)
{
	for (int i = 0; i < SHOT_MAX; i++) {
		shot[i].pos = { 0,0 };
		shot[i].movedir = DIR_DOWN;
		shot[i].lifeMax = 60;
		shot[i].moveSpeed = 7;
		shot[i].size = { 16,16 };
		shot[i].sizeOffset = { shot[i].size.x / 2, shot[i].size.y / 2 };
		shot[i].flag = false;
	}
}

void ShotUpdate(void)
{
	for (int i = 0; i < SHOT_MAX; i++) {
		//�v���C���[1
		if (shot[i].flag == true) {
			switch (shot[i].movedir) {
			case DIR_RIGHT:
				shot[i].pos.x += shot[i].moveSpeed;
				break;
			case DIR_LEFT:
				shot[i].pos.x -= shot[i].moveSpeed;
				break;
			}
		}

		//�e���ǂɓ���������G�t�F�N�g��\������
		if (shot[i].flag == true) {
			if (IsPass(shot[i].pos) == false) {
				shot[i].flag = false;
			}
		}
		//��萔�s���ƒe��������
		if (shot[i].life < 0) {
			shot[i].flag = false;
		}

		
		if (EnemyHitCheck(shot[i].pos, shot[i].size) == true) {
			shot[i].flag = false;
		}
		
	}
}

void ShotDraw(void)
{
	XY mapTemp = GetMapPos();

	for (int i = 0; i < SHOT_MAX; i++) {
		if (shot[i].flag == true) {
			shot[i].life--;
			DrawGraph(shot[i].pos.x - shot[i].sizeOffset.x - mapTemp.x, shot[i].pos.y - shot[i].sizeOffset.y, shotImage, true);
		}
	}
}

//�v���C���[1�e����
void Shot(XY pos, MOVE_DIR dir)
{
	for (int i = 0; i < SHOT_MAX; i++) {
		if (shot[i].flag == false) {
			shot[i].life = shot[i].lifeMax;
			shot[i].pos = pos;
			shot[i].movedir = dir;
			shot[i].flag = true;
		}
	}
}

