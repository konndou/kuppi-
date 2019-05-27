#pragma once

#define EFFECT_MAX 20
#define BOSS_EFFECT_MAX 10
#define BLOCK_EFFECT_MAX 20

enum EFFECT_TYPE {
	EFFECT_T_BLOCK,
	EFFECT_T_MAX
};

//Ãﬂ€ƒ¿≤ÃﬂêÈåæ
void EffectSystemInit(void);
void EffectInit(void);
void EffectUpdata(void);
void EffectDraw(void);

void SetBlockEffect(XY pos);
void SetBlockBossEffect(XY pos, int i);