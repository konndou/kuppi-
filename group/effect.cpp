
#include "main.h"
#include "effect.h"
#include "shot.h"
#include "enemy.h"
#include "player1.h"
#include "keyCheck.h"
#include "stage.h"
#include "boss.h"
#include "item.h"

#define EFFECT_IMAGE_MAX 10
#define TOBITIRI_MAX 6

int effectImage[EFFECT_IMAGE_MAX];

CHARACTER effect[EFFECT_MAX];

void EffectSystemInit(void)
{
	LoadDivGraph("image/effect2.png", 10, 10, 1, 64, 64, effectImage, true);
}

void EffectInit(void)
{
	for (int i = 0; i < EFFECT_MAX; i++) {
		effect[i].flag = false;
		effect[i].size = { 64,64 };
		effect[i].sizeOffset = { effect[i].size.x / 2, effect[i].size.y / 2 };
		effect[i].lifeMax = 10;
	}
}

void EffectUpdata(void)
{
	for (int i = 0; i < EFFECT_MAX; i++) {
		//ｶｳﾝﾄを増加させて一定以上になったらﾌﾗｸﾞを消す
		if (effect[i].life < 0) {
			effect[i].flag = false;
		}
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
}

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