
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

int effectImage[EFFECT_IMAGE_MAX];		//�G�L������|�����Ƃ�
int bosseffectImage[EFFECT_IMAGE_MAX];	//�{�X��|�����Ƃ�
int playeraniImage[EFFECT_IMAGE_MAX];	//�A�C�e�����Ƃ������̃A�j���[�V����
int aboImage[EFFECT_IMAGE_MAX];

CHARACTER effect[EFFECT_MAX];
CHARACTER bosseffect[BOSS_EFFECT_MAX];
CHARACTER playerani[EFFECT_MAX];
CHARACTER abo[EFFECT_MAX];

void EffectSystemInit(void)
{
	LoadDivGraph("image/effect2.png", 10, 10, 1, 64, 64, effectImage, true);
	LoadDivGraph("image/bosseffect.png", 10, 10, 1, 128, 128, bosseffectImage, true);
	LoadDivGraph("image/aboani.png", 15, 15, 1, 64, 64, aboImage, true);
	LoadDivGraph("image/pani.png", 15, 15, 1, 64, 64, playeraniImage, true);
}

void EffectInit(void)
{
	for (int i = 0; i < EFFECT_MAX; i++) {
		effect[i].flag = false;
		effect[i].size = { 64,64 };
		effect[i].sizeOffset = { effect[i].size.x / 2, effect[i].size.y / 2 };
		effect[i].lifeMax = 10;
	}

	for (int i = 0; i < BOSS_EFFECT_MAX; i++) {
		bosseffect[i].flag = false;
		bosseffect[i].size = { 128,128 };
		bosseffect[i].sizeOffset = { bosseffect[i].size.x / 2, bosseffect[i].size.y / 2 };
		bosseffect[i].lifeMax = 30;
	}

	for (int i = 0; i < EFFECT_MAX; i++) {
		playerani[i].flag = false;
		playerani[i].size = { 64,64 };
		playerani[i].sizeOffset = { playerani[i].size.x / 2, playerani[i].size.y / 2 };
		playerani[i].lifeMax = 15;
	}

	for (int i = 0; i < EFFECT_MAX; i++) {
		abo[i].flag = false;
		abo[i].size = { 64,64 };
		abo[i].sizeOffset = { abo[i].size.x / 2, abo[i].size.y / 2 };
		abo[i].lifeMax = 15;
	}
}

void EffectUpdata(void)
{
	for (int i = 0; i < EFFECT_MAX; i++) {
		//���Ă𑝉������Ĉ��ȏ�ɂȂ������׸ނ�����
		if (effect[i].life < 0) {
			effect[i].flag = false;
		}
	}

	for (int i = 0; i < BOSS_EFFECT_MAX; i++) {
		//���Ă𑝉������Ĉ��ȏ�ɂȂ������׸ނ�����
		if (bosseffect[i].life < 0) {
			bosseffect[i].flag = false;
		}
	}

	for (int i = 0; i < EFFECT_MAX; i++) {
		//���Ă𑝉������Ĉ��ȏ�ɂȂ������׸ނ�����
		if (playerani[i].life < 0) {
			playerani[i].flag = false;
		}
	}

	for (int i = 0; i < EFFECT_MAX; i++) {
		//���Ă𑝉������Ĉ��ȏ�ɂȂ������׸ނ�����
		if (abo[i].life < 0) {
			abo[i].flag = false;
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

	for (int i = 0; i < BOSS_EFFECT_MAX; i++) {
		if (bosseffect[i].flag == true) {
			bosseffect[i].life--;
			bosseffect[i].animCnt++;
			DrawGraph(bosseffect[i].pos.x - bosseffect[i].sizeOffset.x - mapTemp.x, bosseffect[i].pos.y - bosseffect[i].sizeOffset.y, bosseffectImage[bosseffect[i].animCnt / 2 % 15], true);
		}
	}

	for (int i = 0; i < EFFECT_MAX; i++) {
		if (playerani[i].flag == true) {
			playerani[i].life--;
			playerani[i].animCnt++;
			DrawGraph(playerani[i].pos.x - playerani[i].sizeOffset.x - mapTemp.x, playerani[i].pos.y - playerani[i].sizeOffset.y, playeraniImage[playerani[i].animCnt % 15], true);
		}
	}

	for (int i = 0; i < EFFECT_MAX; i++) {
		if (abo[i].flag == true) {
			abo[i].life--;
			abo[i].animCnt++;
			DrawGraph(abo[i].pos.x - abo[i].sizeOffset.x - mapTemp.x, abo[i].pos.y - abo[i].sizeOffset.y, aboImage[abo[i].animCnt % 15], true);
		}
	}
}

//�G�L������|�����Ƃ�
void SetBlockEffect(XY pos)
{
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (effect[i].flag == false) {
			effect[i].life = effect[i].lifeMax;
			effect[i].animCnt = 0;
			//pos�����߂�
			effect[i].pos = pos;
			//�ݒ�̏�����
			effect[i].flag = true;
		}
	}
}

//�{�X��|�����Ƃ�
void SetBlockBossEffect(XY pos , int i)
{
	XY ranpos = { 0,0 };
	if (bosseffect[i].flag == false) {
		bosseffect[i].life = bosseffect[i].lifeMax;
		bosseffect[i].animCnt = 0;
		//pos�����߂�
		ranpos.x = (GetRand(180) - 90);
		ranpos.y = (GetRand(180) - 90);

		pos.x = pos.x + ranpos.x;
		pos.y = pos.y + ranpos.y;

		bosseffect[i].pos = pos;
		//�ݒ�̏�����
		bosseffect[i].flag = true;
	}	
}

//�A�C�e�����Ƃ������̃A�j���[�V����
void SetBlockPlayerEffect(XY pos)
{
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (playerani[i].flag == false) {
			playerani[i].life = playerani[i].lifeMax;
			playerani[i].animCnt = 0;
			//pos�����߂�
			playerani[i].pos = pos;
			//�ݒ�̏�����
			playerani[i].flag = true;
		}
	}
}

void SetBlockAboEffect(XY pos)
{
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (abo[i].flag == false) {
			abo[i].life = abo[i].lifeMax;
			abo[i].animCnt = 0;
			//pos�����߂�
			abo[i].pos = pos;
			//�ݒ�̏�����
			abo[i].flag = true;
		}
	}
}