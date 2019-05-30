
#include "main.h"
#include "effect.h"
#include "shot.h"
#include "enemy.h"
#include "player1.h"
#include "keyCheck.h"
#include "stage.h"
#include "boss.h"
#include "item.h"

#define EFFECT_IMAGE_MAX 15
#define TOBITIRI_MAX 6

int effectImage[10];		//敵キャラを倒したとき
int bosseffectImage[EFFECT_IMAGE_MAX];	//ボスを倒したとき
int bosseffect2Image[EFFECT_IMAGE_MAX];	//ボスを倒したとき
int playeraniImage[EFFECT_IMAGE_MAX];	//アイテムをとった時のアニメーション
int aboImage[EFFECT_IMAGE_MAX];

CHARACTER effect[EFFECT_MAX];
CHARACTER bosseffect[BOSS_EFFECT_MAX];
CHARACTER bosseffect2;
CHARACTER playerani;
CHARACTER abo;

void EffectSystemInit(void)
{
	LoadDivGraph("image/effect2.png", 10, 10, 1, 64, 64, effectImage, true);
	LoadDivGraph("image/bosseffect.png", 15, 15, 1, 128, 128, bosseffectImage, true);
	LoadDivGraph("image/bossboss.png", 15, 15, 1, 512, 512, bosseffect2Image, true);
	LoadDivGraph("image/aboani.png", 15, 15, 1, 64, 64, aboImage, true);
	LoadDivGraph("image/pani.png", 15, 15, 1, 64, 64, playeraniImage, true);
}

void EffectInit(void)
{
	//敵キャラのエフェクト
	for (int i = 0; i < EFFECT_MAX; i++) {
		effect[i].flag = false;
		effect[i].size = { 64,64 };
		effect[i].sizeOffset = { effect[i].size.x / 2, effect[i].size.y / 2 };
		effect[i].lifeMax = 10;
	}

	//ボスのエフェクト
	for (int i = 0; i < BOSS_EFFECT_MAX; i++) {
		bosseffect[i].flag = false;
		bosseffect[i].size = { 128,128 };
		bosseffect[i].sizeOffset = { bosseffect[i].size.x / 2, bosseffect[i].size.y / 2 };
		bosseffect[i].lifeMax = 30;
	}

	bosseffect2.flag = false;
	bosseffect2.size = { 512,512 };
	bosseffect2.sizeOffset = { bosseffect2.size.x / 2, bosseffect2.size.y / 2 };
	bosseffect2.lifeMax = 55;
	
	//アイテムのエフェクト
	playerani.flag = false;
	playerani.size = { 64,64 };
	playerani.sizeOffset = { playerani.size.x / 2, playerani.size.y / 2 };
	playerani.lifeMax = 15;
	
	abo.flag = false;
	abo.size = { 64,64 };
	abo.sizeOffset = { abo.size.x / 2, abo.size.y / 2 };
	abo.lifeMax = 15;
	
}

void EffectUpdata(void)
{
	for (int i = 0; i < EFFECT_MAX; i++) {
		//ｶｳﾝﾄを増加させて一定以上になったらﾌﾗｸﾞを消す
		if (effect[i].life < 0) {
			effect[i].flag = false;
		}
	}

	for (int i = 0; i < BOSS_EFFECT_MAX; i++) {
		//ｶｳﾝﾄを増加させて一定以上になったらﾌﾗｸﾞを消す
		if (bosseffect[i].life < 0) {
			bosseffect[i].flag = false;
		}
	}

	//ｶｳﾝﾄを増加させて一定以上になったらﾌﾗｸﾞを消す
	if (bosseffect2.life < 0) {
		bosseffect2.flag = false;
	}
	
	//ｶｳﾝﾄを増加させて一定以上になったらﾌﾗｸﾞを消す
	if (playerani.life < 0) {
		playerani.flag = false;
	}
	
	//ｶｳﾝﾄを増加させて一定以上になったらﾌﾗｸﾞを消す
	if (abo.life < 0) {
		abo.flag = false;
	}
	
}

void EffectDraw(void)
{
	XY mapTemp = GetMapPos();
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (effect[i].flag == true) {
			effect[i].life--;
			effect[i].animCnt++;
			DrawGraph(effect[i].pos.x - effect[i].sizeOffset.x - mapTemp.x, effect[i].pos.y - effect[i].sizeOffset.y, effectImage[effect[i].animCnt % 10], true);
		}
	}

	for (int i = 0; i < BOSS_EFFECT_MAX; i++) {
		if (bosseffect[i].flag == true) {
			bosseffect[i].life--;
			bosseffect[i].animCnt++;
			DrawGraph(bosseffect[i].pos.x - bosseffect[i].sizeOffset.x - mapTemp.x, bosseffect[i].pos.y - bosseffect[i].sizeOffset.y, bosseffectImage[bosseffect[i].animCnt / 2 % 15], true);
		}
	}

	
	if (bosseffect2.flag == true) {
		bosseffect2.life--;
		bosseffect2.animCnt++;
		DrawGraph(bosseffect2.pos.x - bosseffect2.sizeOffset.x - mapTemp.x, bosseffect2.pos.y - bosseffect2.sizeOffset.y, bosseffect2Image[bosseffect2.animCnt / 4 % 15], true);
	}
	
	
	if (playerani.flag == true) {
		playerani.life--;
		playerani.animCnt++;
		DrawGraph(playerani.pos.x - playerani.sizeOffset.x - mapTemp.x, playerani.pos.y - playerani.sizeOffset.y, playeraniImage[playerani.animCnt % 15], true);
	}

	
	if (abo.flag == true) {
		abo.life--;
		abo.animCnt++;
		DrawGraph(abo.pos.x - abo.sizeOffset.x - mapTemp.x, abo.pos.y - abo.sizeOffset.y, aboImage[abo.animCnt % 15], true);
	}
	
}

//敵キャラを倒したとき
void SetBlockEffect(XY pos)
{
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (effect[i].flag == false) {
			effect[i].life = effect[i].lifeMax;
			effect[i].animCnt = 0;
			//posを求める
			effect[i].pos = pos;
			//設定の初期化
			effect[i].flag = true;
		}
	}
}

//ボスを倒したとき
void SetBlockBossEffect(XY pos , int i)
{
	XY ranpos = { 0,0 };
	if (bosseffect[i].flag == false) {
		bosseffect[i].life = bosseffect[i].lifeMax;
		bosseffect[i].animCnt = 0;
		//posを求める
		ranpos.x = (GetRand(180) - 90);
		ranpos.y = (GetRand(180) - 90);

		pos.x = pos.x + ranpos.x;
		pos.y = pos.y + ranpos.y;

		bosseffect[i].pos = pos;
		//設定の初期化
		bosseffect[i].flag = true;
	}	
}

void SetBlockBoss2Effect(XY pos)
{
	if (bosseffect2.flag == false) {
		bosseffect2.life = bosseffect2.lifeMax;
		bosseffect2.animCnt = 0;
		//posを求める
		bosseffect2.pos = pos;
		//設定の初期化
		bosseffect2.flag = true;
	}
}

//アイテムをとった時のアニメーション
void SetBlockPlayerEffect(XY pos)
{
	
	if (playerani.flag == false) {
		playerani.life = playerani.lifeMax;
		playerani.animCnt = 0;
		//posを求める
		playerani.pos = pos;
		//設定の初期化
		playerani.flag = true;
	}
	
}

void SetBlockAboEffect(XY pos)
{
	
	if (abo.flag == false) {
		abo.life = abo.lifeMax;
		abo.animCnt = 0;
		//posを求める
		abo.pos = pos;
		//設定の初期化
		abo.flag = true;
	}
	
}