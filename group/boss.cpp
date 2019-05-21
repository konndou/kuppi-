#include "main.h"
#include "enemy.h"
#include "player1.h"
#include "keyCheck.h"
#include "stage.h"
#include "boss.h"
#include "item.h"

CHARACTER boss;
int bossImage[2];

void BossSystemInit(void)
{
	LoadDivGraph("image/snake.png", 2, 2, 1, BOSS_SIZE_X, BOSS_SIZE_Y, bossImage);
}

void BossInit(void)
{
	//boss.poscnt = GetRand(220);
	boss.pos = { 32 * (boss.poscnt + 10) + 16, 0 };
	boss.size = { 128,64 };
	boss.sizeOffset = { (boss.size.x / 2),(boss.size.y / 2) };
	boss.hitPosS = { 32, 32 };
	boss.hitPosE = { 32, 32 };
	boss.moveSpeed = 4;
	boss.Velocity = { 0,0 };
	boss.jumpFlag = true;
	boss.imgLockCnt = 30;
	boss.movedir = DIR_LEFT;
	boss.flag = true;
	boss.moveSpeed = 2;
	boss.flagcnt = 0;

}

void BossUpdate(void)
{

	auto stagecnt = GetStageCnt();
	if (stagecnt == 0) {
		boss.flag = true;
	}

	if (boss.flag == true)
	{
		//敵キャラを地面に落とす

		boss.jumpFlag = true;

		if (boss.jumpFlag == true) {
			XY movedPos = boss.pos;
			XY movedHitCheck = movedPos;
			XY movedHitCheck2 = movedPos;
			XY movedHitCheck3 = movedPos;
			XY tmpIndex;
			XY tmpPos;

			movedPos.y -= boss.Velocity.y * SECOND_PER_FRAME;
			boss.Velocity.y -= ACC_G * SECOND_PER_FRAME;

			movedHitCheck.y = movedPos.y + boss.hitPosE.y;	//足元の座標計算
			//足元右下
			movedHitCheck2 = movedHitCheck;
			movedHitCheck2.x = movedPos.x + boss.hitPosE.x;
			//足元左下
			movedHitCheck3 = movedHitCheck;
			movedHitCheck3.x = movedPos.x - boss.hitPosE.x;

			//足元にブロックがあるかどうか
			//通れるかどうか
			if (boss.Velocity.y < 0) {
				if (IsPass(movedHitCheck) && IsPass(movedHitCheck2) && IsPass(movedHitCheck3)) {
					boss.pos = movedPos;
				}
				else {
					tmpIndex = MapPosToIndex(movedHitCheck);	//ブロックの上の座標を計算
																//	movedHitCheck.y / 32
					tmpPos = MapIndexToPos(tmpIndex);			//足元のｙ座標
																//	(movedHitCheck.y / 32) * 32
					boss.pos.y = tmpPos.y - boss.hitPosE.y;	//足元から中心を求める
					boss.Velocity.y = 0;
					boss.jumpFlag = false;
				}
			}
		}

		//敵キャラの方向転換
		if (boss.jumpFlag == false) {
			XY movedPos = boss.pos;
			XY movedHitCheck = movedPos;
			XY movedHitCheck2 = movedPos;
			XY movedHitCheck3 = movedPos;

			movedHitCheck.y = movedPos.y + boss.hitPosE.y;	//足元の座標計算
			//足元右下
			movedHitCheck2 = movedHitCheck;
			movedHitCheck2.x = movedPos.x + boss.hitPosE.x;
			//足元左下
			movedHitCheck3 = movedHitCheck;
			movedHitCheck3.x = movedPos.x - boss.hitPosE.x;

			//通れるかどうか
			if ((IsEnemyPass(movedHitCheck) && IsEnemyPass(movedHitCheck2) && IsEnemyPass(movedHitCheck3)) == false) {
				switch (boss.movedir)
				{
				case DIR_LEFT:
					boss.movedir = DIR_RIGHT;
					break;
				case DIR_RIGHT:
					boss.movedir = DIR_LEFT;
					break;
				}
			}

			movedHitCheck.y = movedPos.y;	//足元の座標計算
			//足元右下
			movedHitCheck2 = movedHitCheck;
			movedHitCheck2.x = movedPos.x + boss.hitPosE.x;
			//足元左下
			movedHitCheck3 = movedHitCheck;
			movedHitCheck3.x = movedPos.x - boss.hitPosE.x;

			if ((IsPass(movedHitCheck) && IsPass(movedHitCheck2) && IsPass(movedHitCheck3)) == false) {
				switch (boss.movedir)
				{
				case DIR_LEFT:
					boss.movedir = DIR_RIGHT;
					break;
				case DIR_RIGHT:
					boss.movedir = DIR_LEFT;
					break;
				}
			}
		}

		//敵キャラの移動
		if (boss.jumpFlag == false)
		{
			switch (boss.movedir)
			{
			case DIR_LEFT:
				boss.pos.x -= boss.moveSpeed;
				break;
			case DIR_RIGHT:
				boss.pos.x += boss.moveSpeed;
				break;
			default:
				break;
			}
		}
	}


}

void BossDraw(void)
{

	XY mapTemp = GetMapPos();

	int image = bossImage[boss.animCnt / 10 % 2];

	boss.animCnt++;
	if (boss.flag == true)
	{
		if (boss.movedir == DIR_RIGHT) {
			DrawTurnGraph(boss.pos.x - boss.sizeOffset.x - mapTemp.x, boss.pos.y - boss.sizeOffset.y, image, true);
		}
		if (boss.movedir == DIR_LEFT) {
			DrawGraph(boss.pos.x - boss.sizeOffset.x - mapTemp.x, boss.pos.y - boss.sizeOffset.y, image, true);
		}
	}

}