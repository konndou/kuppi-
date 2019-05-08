
#include "main.h"
#include "player1.h"
#include "keyCheck.h"
#include "stage.h"


CHARACTER player1;
int player1Image[2];
int player1jumpImage[3];

void PlayerSystemInit(void)
{
  	LoadDivGraph("image/player1.png", 2, 2, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, player1Image);
	LoadDivGraph("image/player1jump.png", 3, 3, 1, PLAYER_SIZE_X * 2, 40, player1jumpImage);
}

void PlayerInit(void)
{
	//初期化
	player1.pos = { 5 * MAP_CHIP_SIZE_X, 8 * MAP_CHIP_SIZE_Y };
	player1.size = { 32, 32 };
	player1.sizeOffset = { (player1.size.x / 2), (player1.size.y / 2) };
	player1.hitPosS = { 8, 8 };
	player1.hitPosE = { 8, 16 };
	player1.moveSpeed = 4;
	player1.Velocity = { 0,0 };
	player1.damageFlag = false;
	player1.jumpFlag = false;
	player1.runFlag = false;
	player1.shotFlag = false;
	player1.movedir = DIR_RIGHT;
	player1.imgLockCnt = 30;
	player1.flag = true;
	player1.gFlag = false;
	player1.xFlag = false;
}

void PlayerUpdate(void)
{
	if (player1.flag == true) {
		//XY movedOffset = { 0, player1.pos.y - player1.sizeOffset.y / 2 };

		bool playerMoved = false;

		//右に走る
		player1.runFlag = false;
		if (newkey[P1_RIGHT]) {
			playerMoved = true;
			player1.runFlag = true;
			player1.movedir = DIR_RIGHT;
			player1.Velocity.x += ACC_RUN;
			if (player1.Velocity.x > VELOCITY_X_MAX)player1.Velocity.x = VELOCITY_X_MAX;
		}
		//左に走る
		if (newkey[P1_LEFT]) {
			playerMoved = true;
			player1.runFlag = true;
			player1.movedir = DIR_LEFT;
			player1.Velocity.x -= ACC_RUN;
			if (player1.Velocity.x < -VELOCITY_X_MAX)player1.Velocity.x = -VELOCITY_X_MAX;
		}

		if (player1.runFlag == false) {	//何もキー入力がない場合は、止まろうとする
			//段階的に速度を落とす
			if (player1.Velocity.x < 0) {
				player1.Velocity.x += ACC_STOP * 1;
				if (player1.Velocity.x > 0)player1.Velocity.x = 0;
			}
			else if (player1.Velocity.x > 0) {
				player1.Velocity.x -= ACC_STOP * 1;
				if (player1.Velocity.x < 0)player1.Velocity.x = 0;
			}
		}

		XY movedPos = player1.pos;
		XY movedHitCheck = movedPos;
		XY movedHitCheck2 = movedPos;
		XY movedHitCheck3 = movedPos;
		XY tmpIndex;
		XY tmpPos;

		movedPos.x += player1.Velocity.x * 1;

		if (player1.Velocity.x < 0) {
			movedHitCheck.x = movedPos.x - player1.hitPosS.x;
		}
		else if (player1.Velocity.x > 0) {
			movedHitCheck.x = movedPos.x + player1.hitPosE.x;
		}

		movedHitCheck2 = movedHitCheck;
		movedHitCheck2.y = movedPos.y + player1.hitPosS.y;

		movedHitCheck3 = movedHitCheck;
		movedHitCheck3.y = movedPos.y - player1.hitPosE.y;

		//通れるかどうか
		if (IsPass(movedHitCheck) && IsPass(movedHitCheck2) && IsPass(movedHitCheck3)) {
			player1.pos = movedPos;
		}
		else {
			tmpIndex = MapPosToIndex(movedHitCheck);	//ブロックの上の座標を計算
			if (player1.Velocity.x < 0) {
				tmpIndex.x++;
				tmpPos = MapIndexToPos(tmpIndex);			//足元のｙ座標
				player1.pos.x = tmpPos.x + player1.hitPosE.x;	//足元から中心を求める
			}
		}

		player1.jumpFlag = true;
		//プレイヤー1ジャンプ
		if (player1.jumpFlag == true) {
			XY movedPos = player1.pos;
			XY movedHitCheck = movedPos;
			XY movedHitCheck2 = movedPos;
			XY movedHitCheck3 = movedPos;
			XY tmpIndex;
			XY tmpPos;

			movedPos.y -= player1.Velocity.y * SECOND_PER_FRAME;
			player1.Velocity.y -= ACC_G * SECOND_PER_FRAME;

			movedHitCheck.y = movedPos.y - player1.hitPosS.y;	//頭上の座標計算
			//頭上の右上
			movedHitCheck2 = movedHitCheck;
			movedHitCheck2.x = movedPos.x + player1.hitPosS.x;
			//頭上の左上
			movedHitCheck3 = movedHitCheck;
			movedHitCheck3.x = movedPos.x - player1.hitPosS.x;
			//頭上にブロックがあるかどうか
			//通れるかどうか
			if (IsPass(movedHitCheck) && IsPass(movedHitCheck2) && IsPass(movedHitCheck3)) {
				player1.pos = movedPos;
			}
			else {
				tmpIndex = MapPosToIndex(movedHitCheck);
				//	movedHitCheck.y / 32
				tmpIndex.y++;
				tmpPos = MapIndexToPos(tmpIndex);
				//	(movedHitCheck.y / 32) * 32
				player1.pos.y = tmpPos.y + player1.hitPosS.y;	//頭上から中心を求める
				player1.Velocity.y *= -1;

				movedPos = player1.pos;
			}

			movedHitCheck.y = movedPos.y + player1.hitPosE.y;	//足元の座標計算
			//足元右下
			movedHitCheck2 = movedHitCheck;
			movedHitCheck2.x = movedPos.x + player1.hitPosE.x;
			//足元左下
			movedHitCheck3 = movedHitCheck;
			movedHitCheck3.x = movedPos.x - player1.hitPosE.x;

			//足元にブロックがあるかどうか
			//通れるかどうか
			if (player1.Velocity.y < 0) {
				if (IsPass(movedHitCheck) && IsPass(movedHitCheck2) && IsPass(movedHitCheck3)) {
					player1.pos = movedPos;
				}
				else {
					tmpIndex = MapPosToIndex(movedHitCheck);	//ブロックの上の座標を計算
																//	movedHitCheck.y / 32
					tmpPos = MapIndexToPos(tmpIndex);			//足元のｙ座標
																//	(movedHitCheck.y / 32) * 32
					player1.pos.y = tmpPos.y - player1.hitPosE.y;	//足元から中心を求める
					player1.Velocity.y = 0;
					player1.jumpFlag = false;
				}
			}
		}
		//ジャンプしていなかったらジャンプする
		if (player1.jumpFlag == false) {
			if (trgkey[P1_UP]) {
				player1.jumpFlag = true;
				player1.Velocity.y = INIT_VELOCITY;
			}
		}
	}

	//一定時間イメージの固定
	if (player1.imgLockCnt < 0) {
		player1.shotFlag = false;
		player1.damageFlag = false;
		player1.imgLockCnt = 30;
	}

	//移動制限
	if (player1.pos.x < player1.size.x) {
		player1.pos.x = player1.size.x;
	}
}

void PlayerDraw(void)
{
	int image = player1Image[player1.animCnt / 10 % 2];
	if (player1.jumpFlag == true)image = player1jumpImage[player1.animCnt / 7 % 3];

	XY mapTemp = GetMapPos();
	
	player1.animCnt++;
	if (player1.flag == true) {
		if (player1.movedir == DIR_RIGHT) {
			DrawGraph(player1.pos.x - player1.sizeOffset.x - mapTemp.x, player1.pos.y - player1.sizeOffset.y, image, true);
		}
		if (player1.movedir == DIR_LEFT) {
			DrawTurnGraph(player1.pos.x - player1.sizeOffset.x - mapTemp.x, player1.pos.y - player1.sizeOffset.y, image, true);
		}
	}
}

bool PlayerGoal(void)
{
	XY movedPos = player1.pos;
	XY movedHitCheck = movedPos;
	XY movedHitCheck2 = movedPos;
	XY movedHitCheck3 = movedPos;

	movedHitCheck.y = movedPos.y + player1.hitPosE.y;	//足元の座標計算
	//足元右下
	movedHitCheck2 = movedHitCheck;
	movedHitCheck2.x = movedPos.x + player1.hitPosE.x;
	//足元左下
	movedHitCheck3 = movedHitCheck;
	movedHitCheck3.x = movedPos.x - player1.hitPosE.x;

	//ゴールしたかどうか
	if (IsGoalPass(movedHitCheck) && IsGoalPass(movedHitCheck2) && IsGoalPass(movedHitCheck3)) {
		return false;
	}
	player1.jumpFlag = false;
	player1.gFlag = true;
	return true;
}

void PlayerGoalDraw(void)
{
	//プレイヤー1ジャンプ
	if (player1.jumpFlag == true) {
		XY movedPos = player1.pos;
		XY movedHitCheck = movedPos;
		XY movedHitCheck2 = movedPos;
		XY movedHitCheck3 = movedPos;
		XY tmpIndex;
		XY tmpPos;

		movedPos.y -= player1.Velocity.y * 0.05;
		player1.Velocity.y -= ACC_G * 0.05;

		movedHitCheck.y = movedPos.y - player1.hitPosS.y;	//頭上の座標計算
		//頭上の右上
		movedHitCheck2 = movedHitCheck;
		movedHitCheck2.x = movedPos.x + player1.hitPosS.x;
		//頭上の左上
		movedHitCheck3 = movedHitCheck;
		movedHitCheck3.x = movedPos.x - player1.hitPosS.x;
		//頭上にブロックがあるかどうか
		//通れるかどうか
		if (IsPass(movedHitCheck) && IsPass(movedHitCheck2) && IsPass(movedHitCheck3)) {
			player1.pos = movedPos;
		}
		else {
			tmpIndex = MapPosToIndex(movedHitCheck);
			//	movedHitCheck.y / 32
			tmpIndex.y++;
			tmpPos = MapIndexToPos(tmpIndex);
			//	(movedHitCheck.y / 32) * 32
			player1.pos.y = tmpPos.y + player1.hitPosS.y;	//頭上から中心を求める
			player1.Velocity.y *= -1;

			movedPos = player1.pos;
		}

		movedHitCheck.y = movedPos.y + player1.hitPosE.y;	//足元の座標計算
			//足元右下
		movedHitCheck2 = movedHitCheck;
		movedHitCheck2.x = movedPos.x + player1.hitPosE.x;
		//足元左下
		movedHitCheck3 = movedHitCheck;
		movedHitCheck3.x = movedPos.x - player1.hitPosE.x;

		//足元にブロックがあるかどうか
		//通れるかどうか
		if (player1.Velocity.y < 0) {
			if (IsPass(movedHitCheck) && IsPass(movedHitCheck2) && IsPass(movedHitCheck3)) {
				player1.pos = movedPos;
			}
			else {
				tmpIndex = MapPosToIndex(movedHitCheck);	//ブロックの上の座標を計算
															//	movedHitCheck.y / 32
				tmpPos = MapIndexToPos(tmpIndex);			//足元のｙ座標
															//	(movedHitCheck.y / 32) * 32
				player1.pos.y = tmpPos.y - player1.hitPosE.y;	//足元から中心を求める
				player1.Velocity.y = 0;
				player1.jumpFlag = false;
			}
		}
	}

	int image = player1Image[player1.animCnt / 10 % 2];
	if (player1.jumpFlag == true)image = player1jumpImage[player1.animCnt / 7 % 3];

	XY mapTemp = GetMapPos();

	player1.animCnt++;
	if (player1.flag == true) {
		if (player1.movedir == DIR_RIGHT) {
			DrawGraph(player1.pos.x - player1.sizeOffset.x - mapTemp.x, player1.pos.y - player1.sizeOffset.y, image, true);
		}
		if (player1.movedir == DIR_LEFT) {
			DrawTurnGraph(player1.pos.x - player1.sizeOffset.x - mapTemp.x, player1.pos.y - player1.sizeOffset.y, image, true);
		}
	}

	XY GoalPos = { 0, 32 * 11 };

	if (player1.gFlag == true) {
		if(player1.pos.y - player1.sizeOffset.y >= SCREEN_SIZE_Y - GoalPos.y) {
			player1.pos.y -= 2;
		}
	}

	if (player1.pos.y - player1.sizeOffset.y < SCREEN_SIZE_Y - GoalPos.y) {
		player1.xFlag = true;
		player1.jumpFlag = true;
		player1.gFlag = false;
	}

	if (player1.xFlag == true) {
		GoalPos.x++;
		if (GoalPos.x < 60) {
			player1.pos.x = player1.pos.x + GoalPos.x;
		}
		else {
			player1.xFlag = false;
		}
	}
}

bool PlayerNextStage(void)
{
	XY movedPos = player1.pos;

	//ゴールしたかどうか
	if (IsNextPass(movedPos)) {
		return false;
	}
	return true;
}

CHARACTER GetPlayerPos(void)
{
	return player1;
}