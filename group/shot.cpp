
#include "main.h"
#include "shot.h"
#include "enemy.h"
#include "player1.h"
#include "keyCheck.h"
#include "stage.h"
#include "boss.h"
#include "item.h"
#include "effect.h"

CHARACTER shot;
int shotImage;
int sdir;

void ShotSystemInit(void)
{
	shotImage = LoadGraph("image/bullet2.png");
}

//初期化
void ShotInit(void)
{
	shot.pos = { 0,0 };
	shot.movedir = DIR_DOWN;
	shot.lifeMax = 60;
	shot.moveSpeed = 7;
	shot.size = { 16,16 };
	shot.sizeOffset = { shot.size.x / 2, shot.size.y / 2 };
	shot.flag = false;
}

void ShotUpdate(void)
{
	//プレイヤー1
	if (shot.flag == true) {
		switch (shot.movedir) {
		case DIR_RIGHT:
			shot.pos.x += shot.moveSpeed;
			break;
		case DIR_LEFT:
			shot.pos.x -= shot.moveSpeed;
			break;
		}
	}

	if (shot.flag == true) {
		if (IsPass(shot.pos) == false) {
			shot.flag = false;
		}
	}
	//一定数行くと弾が消える
	if (shot.life < 0) {
		shot.flag = false;
	}

	//当たり判定
	if ((EnemyHitCheck(shot.pos, shot.size)) == true) {
		shot.flag = false;
	}
}

void ShotDraw(void)
{
	XY mapTemp = GetMapPos();
	
	if (shot.flag == true) {
		shot.life--;
		DrawGraph(shot.pos.x - shot.sizeOffset.x - mapTemp.x, shot.pos.y - shot.sizeOffset.y, shotImage, true);
	}
}

//プレイヤー1弾撃ち
void Shot(XY pos, MOVE_DIR dir)
{
	if (shot.flag == false) {
		shot.life = shot.lifeMax;
		shot.pos = pos;
		shot.movedir = dir;
		shot.flag = true;
	}
}

bool shotHitCheck(XY bPos, XY bSize)
{
	if (shot.flag == true) {
		if ((shot.pos.x - shot.size.x / 2 < bPos.x + bSize.x / 2)
			&& (shot.pos.x + shot.size.x / 2 > bPos.x - bSize.x / 2)
			&& (shot.pos.y - shot.size.y / 2 < bPos.y + bSize.y / 2)
			&& (shot.pos.y + shot.size.y / 2 > bPos.y - bSize.y / 2)) {
			return true;
		}
	}
	return false;
}

XY GetShotPos(void)
{
	return shot.pos;
}

void Deleteshot(void)
{
	shot.flag = false;
}