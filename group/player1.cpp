
#include "main.h"
#include "player1.h"
#include "keyCheck.h"
#include "stage.h"
#include "enemy.h"
#include "shot.h"
#include "boss.h"
#include "item.h"
#include "effect.h"

CHARACTER player1;
int player1runImage[2];	//プレイヤーが走っているときの処理
int player1jumpImage[3];	//プレイヤージャンプ中の処理
int player1dImage[4];	//死んだ時の画像
int jumpse;	//ジャンプ時サウンド
int shotse;	//ショット時のサウンド
int itemse;	//アイテム取得時のサウンド
int image;	//イメージ
bool playerdrun;	//プレイヤーの移動を止める
int playerBigImage;
int player1BigrunImage[2];	//鶏時の走っているときの画像
int player1BigjumpImage[3];	//鶏時のジャンプ中の画像
bool player1Bigflag;

bool playerdamageFlag;

bool flag;	//アイテムで死んだ時用

int pclearImage;

auto anicnt = 0;
auto damagecnt = 0;

XY pclearPos;

void PlayerSystemInit(void)
{
	//プレイヤー状態ヒヨコ
  	LoadDivGraph("image/player2run2.png", 2, 2, 1, PLAYER_SIZE_X * 2, PLAYER_SIZE_Y, player1runImage);
	LoadDivGraph("image/player2jump3.png", 3, 3, 1, PLAYER_SIZE_X * 2, PLAYER_SIZE_Y, player1jumpImage);
	LoadDivGraph("image/playerd4.png", 4, 4, 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, player1dImage);

	//プレイヤー状態鶏
	//playerBigImage = LoadGraph("image/playerBig2.png", true);
	LoadDivGraph("image/playerBigrun2.png", 2, 2, 1, PLAYER_SIZE_X * 2, PLAYER_SIZE_Y, player1BigrunImage);
	LoadDivGraph("image/playerBigjump.png", 3, 3, 1, PLAYER_SIZE_X * 2, PLAYER_SIZE_Y, player1BigjumpImage);

	pclearImage = LoadGraph("image/clear.png");

	//サウンド
	jumpse = LoadSoundMem("bgm/jump2.mp3");
	ChangeVolumeSoundMem(150, jumpse);
	shotse = LoadSoundMem("bgm/shot.mp3");
	ChangeVolumeSoundMem(255, shotse);
	itemse = LoadSoundMem("bgm/item.mp3");
	ChangeVolumeSoundMem(255, itemse);

	player1Bigflag = false;
}

//プレイヤーの初期化
void PlayerInit(void)
{
	//初期化
	player1.pos = { 255 * MAP_CHIP_SIZE_X, 8 * MAP_CHIP_SIZE_Y };	//プレイヤーの初期位置
	player1.size = { 64, 32 };	//プレイヤーのサイズ
	player1.sizeOffset = { (player1.size.x / 2), (player1.size.y / 2) };
	player1.hitPosS = { 8, 15 };
	player1.hitPosE = { 8, 17 };
	player1.moveSpeed = 4;
	player1.Velocity = { 0,0 };
	player1.jumpFlag = false;
	player1.runFlag = false;
	player1.shotFlag = false;
	player1.movedir = DIR_RIGHT;
	player1.imgLockCnt = 30;
	player1.flag = true;
	player1.gFlag = false;	//ゴール演出中フラグ
	player1.xFlag = false;	//ゴール演出用フラグ(横移動)
	playerdrun = true;
	flag = false;

	pclearPos = { 330, -300 };
}

//プレイヤー処理
void PlayerUpdate(void)
{
	if (player1.flag == true) {
		bool playerMoved = false;

		if (playerdrun == true) {
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
		}

		if (player1.runFlag == false) {	//何もキー入力がない場合は、止まろうとする
			//段階的に速度を落とす
			if (player1.Velocity.x < 0) {
				player1.Velocity.x += ACC_STOP * 3;
				if (player1.Velocity.x > 0)player1.Velocity.x = 0;
			}
			else if (player1.Velocity.x > 0) {
				player1.Velocity.x -= ACC_STOP * 3;
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
		movedHitCheck2.y = movedPos.y + player1.hitPosS.y - 3;

		movedHitCheck3 = movedHitCheck;
		movedHitCheck3.y = movedPos.y - player1.hitPosE.y + 3;

		//通れるかどうか
		if (IsPass(movedHitCheck) && IsPass(movedHitCheck2) && IsPass(movedHitCheck3)) {
			player1.pos = movedPos;
		}
		else {
			tmpIndex = MapPosToIndex(movedHitCheck);	//ブロックの上の座標を計算
			player1.Velocity.x = 0;
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
				player1.Velocity.y *= -0.5;

				movedPos = player1.pos;
			}

			//アイテムの出現
			if ((ItemEvent(movedHitCheck) && ItemEvent(movedHitCheck2) && ItemEvent(movedHitCheck3)) == false) {
				ItemFlag();
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
				PlaySoundMem(jumpse, DX_PLAYTYPE_BACK, false);
				player1.jumpFlag = true;
				player1.Velocity.y = INIT_VELOCITY;
			}
		}

		//弾を撃つ
		if (trgkey[P2_B]) {
			PlaySoundMem(shotse, DX_PLAYTYPE_BACK, false);
			XY pshotPos = { 0, 0 };
			pshotPos.y = player1.pos.y;
			if (player1.movedir == DIR_RIGHT) {
				pshotPos.x = player1.pos.x + player1.sizeOffset.x;
			}
			else if (player1.movedir == DIR_LEFT) {
				pshotPos.x = player1.pos.x - player1.sizeOffset.x;
			}
			Shot(pshotPos, player1.movedir);
			player1.shotFlag = true;
		}
		//アイテムが当たった時
		if (ItemHitCheck(player1.pos, player1.size) == true) {
			int num = GetItemNum();
			CHARACTER itemTemp = GetItemPos(num);
			if (itemTemp.type == ITEM_TYPE_CHEESE) {
				if (player1Bigflag == false) {
					SetBlockPlayerEffect(player1.pos);
					PlaySoundMem(itemse, DX_PLAYTYPE_BACK, false);
				}
				player1Bigflag = true;
				image = player1BigrunImage[player1.animCnt / 10 % 2];
				DeleteItem(num);	//アイテムを消す
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

//プレイヤー描画
void PlayerDraw(void)
{
	//画像の入れ替え
	if (player1Bigflag == false) {	//ヒヨコの時
		image = player1runImage[player1.animCnt / 10 % 2];
		if (player1.jumpFlag == true)image = player1jumpImage[player1.animCnt / 7 % 3];
		if (player1.flag == false)image = player1dImage[player1.animCnt / 28 % 4];
	}

	if (player1Bigflag == true) {	//鶏の時
		image = player1BigrunImage[player1.animCnt / 10 % 2];
		if (player1.jumpFlag == true)image = player1BigjumpImage[player1.animCnt / 7 % 3];
	}

	XY mapTemp = GetMapPos();
	
	player1.animCnt++;
	if (playerdamageFlag == false) {
		if (player1.flag == true) {
			if (player1.movedir == DIR_RIGHT) {
				DrawGraph(player1.pos.x - player1.sizeOffset.x - mapTemp.x, player1.pos.y - player1.sizeOffset.y, image, true);
			}
			if (player1.movedir == DIR_LEFT) {
				DrawTurnGraph(player1.pos.x - player1.sizeOffset.x - mapTemp.x, player1.pos.y - player1.sizeOffset.y, image, true);
			}
		}
	}

	//プレイヤー無敵時間
	if (playerdamageFlag == true) {
		anicnt++;
		damagecnt++;
	}
	if (playerdamageFlag == true) {
		if ((anicnt / 7 % 3) == 1) {
			if (player1.flag == true) {
				if (player1.movedir == DIR_RIGHT) {
					DrawGraph(player1.pos.x - player1.sizeOffset.x - mapTemp.x, player1.pos.y - player1.sizeOffset.y, image, true);
				}
				if (player1.movedir == DIR_LEFT) {
					DrawTurnGraph(player1.pos.x - player1.sizeOffset.x - mapTemp.x, player1.pos.y - player1.sizeOffset.y, image, true);
				}
			}
		}
	}

	if (damagecnt > 75) {
		playerdamageFlag = false;
		anicnt = 0;
		damagecnt = 0;
	}

	//プレイヤーの死体表示
	if (player1.flag == false) {
		if (player1.movedir == DIR_RIGHT) {
			DrawGraph(player1.pos.x + 16 - player1.sizeOffset.x - mapTemp.x, player1.pos.y - player1.sizeOffset.y, image, true);
		}
		if (player1.movedir == DIR_LEFT) {
			DrawTurnGraph(player1.pos.x + 16 - player1.sizeOffset.x - mapTemp.x, player1.pos.y - player1.sizeOffset.y, image, true);
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
	player1.Velocity.y = 30;
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
			tmpIndex.y += 1;
			tmpPos = MapIndexToPos(tmpIndex);
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
			if (IsGPass(movedHitCheck) && IsGPass(movedHitCheck2) && IsGPass(movedHitCheck3)) {
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

	//画像の入れ替え
	if (player1Bigflag == false) {
		image = player1runImage[player1.animCnt / 10 % 2];
		if (player1.jumpFlag == true)image = player1jumpImage[player1.animCnt / 7 % 3];
	}
	if (player1Bigflag == true) {
		image = player1BigrunImage[player1.animCnt / 10 % 2];
		if (player1.jumpFlag == true)image = player1BigjumpImage[player1.animCnt / 7 % 3];
	}

	XY mapTemp = GetMapPos();
	player1.movedir = DIR_RIGHT;

	player1.animCnt++;
	if (player1.flag == true) {
		if (player1.movedir == DIR_RIGHT) {
			DrawGraph(player1.pos.x - player1.sizeOffset.x - mapTemp.x, player1.pos.y - player1.sizeOffset.y, image, true);
		}
		if (player1.movedir == DIR_LEFT) {
			DrawTurnGraph(player1.pos.x - player1.sizeOffset.x - mapTemp.x, player1.pos.y - player1.sizeOffset.y, image, true);
		}
	}

	//ゴール演出
	XY GoalPos = { 0, 0 };

	if (player1.gFlag == true) {
		XY movedPos = player1.pos;
		XY movedHitCheck = movedPos;
		XY movedHitCheck2 = movedPos;
		XY movedHitCheck3 = movedPos;

		movedHitCheck.y = movedPos.y + player1.sizeOffset.y;	//頭上の座標計算
		//頭上の右上
		movedHitCheck2 = movedHitCheck;
		movedHitCheck2.x = movedPos.x + player1.hitPosS.x;
		//頭上の左上
		movedHitCheck3 = movedHitCheck;
		movedHitCheck3.x = movedPos.x - player1.hitPosS.x;

		if (IsGoal2Pass(movedHitCheck) && IsGoal2Pass(movedHitCheck2) && IsGoal2Pass(movedHitCheck3) == true) {
			player1.pos.y -= 2;
		}
		else {
			player1.xFlag = true;
			player1.jumpFlag = true;
			player1.gFlag = false;
		}
	}

	if (player1.xFlag == true) {
		GoalPos.x += 2;
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

bool PlayerOver(void)
{
	XY movedPos = player1.pos;
	XY movedHitCheck = movedPos;
	XY movedHitCheck2 = movedPos;
	XY movedHitCheck3 = movedPos;

	movedHitCheck2 = movedHitCheck;
	movedHitCheck2.y = movedPos.y + player1.hitPosS.y;

	movedHitCheck3 = movedHitCheck;
	movedHitCheck3.y = movedPos.y - player1.hitPosE.y;

	if ((IsOverPass(movedHitCheck) && IsOverPass(movedHitCheck2) && IsOverPass(movedHitCheck3)) == false) {
		if (player1Bigflag == true) {
			image = player1runImage[player1.animCnt / 10 % 2];
			player1Bigflag = false;
			return false;
		}
		return true;
	}

	//敵キャラとの当たり判定
	if (playerdamageFlag == false) {
		if (EnemyHitCheck(player1.pos, player1.sizeOffset) == true) {
			if (player1Bigflag == true) {
				playerdamageFlag = true;
				player1Bigflag = false;
			}
			else if (player1Bigflag == false) {
				flag = true;
			}
		}
	}

	//ボスとの当たり判定
	if (playerdamageFlag == false) {
		if (BossHitCheck(player1.pos, player1.sizeOffset) == true) {
			if (player1Bigflag == true) {
				playerdamageFlag = true;
				player1Bigflag = false;
			}
			else if (player1Bigflag == false) {
				flag = true;
			}
		}
	}

	//アイテム(アボカド)を取った時
	if (ItemHitCheck(player1.pos, player1.size) == true) {
		int num = GetItemNum();
		CHARACTER itemTemp = GetItemPos(num);
		if (itemTemp.type == ITEM_TYPE_ABOKADO) {
			if (player1Bigflag == true) {
				player1Bigflag = false;
				DeleteItem(num);	//アイテムを消す
			}else if (player1Bigflag == false) {
				SetBlockAboEffect(player1.pos);
				flag = true;
				DeleteItem(num);	//アイテムを消す
			}
		}
	}
	if (flag == true) {
		return true;
	}
	return false;
}

//死んだ時の処理
void PlayerDEffect(void) {
	player1.animCnt = 0;
}

void PlayerDEffectDraw(void) {
	playerdrun = false;
	player1.flag = false;
	player1.Velocity = { 0,0 };
}

CHARACTER GetPlayerPos(void)
{
	return player1;
}

void PlayerBigFlagInit(void)
{
	player1Bigflag = false;
}

bool PlayerClearEffect(void)
{
	player1.jumpFlag = true;
	if (player1Bigflag == false) {	//ヒヨコの時
		if (player1.jumpFlag == true)image = player1jumpImage[player1.animCnt / 7 % 3];
	}

	if (player1Bigflag == true) {	//鶏の時
		if (player1.jumpFlag == true)image = player1BigjumpImage[player1.animCnt / 7 % 3];
	}

	if (player1.pos.x < MAP_CHIP_X * MAP_CHIP_SIZE_X - SCREEN_SIZE_X / 2) {
		player1.movedir = DIR_RIGHT;
		player1.pos.x++;
	}
	else if(player1.pos.x > MAP_CHIP_X * MAP_CHIP_SIZE_X - SCREEN_SIZE_X / 2){
		player1.movedir = DIR_LEFT;
		player1.pos.x--;
	}

	if (player1.pos.x == MAP_CHIP_X * MAP_CHIP_SIZE_X - SCREEN_SIZE_X / 2) {
		DrawGraph(pclearPos.x, pclearPos.y, pclearImage, true);
		if (pclearPos.y <= 200) {
			pclearPos.y += 4;
		}
		if (pclearPos.y == 200) {
			return true;
		}
	}
	return false;
}