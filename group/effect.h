#pragma once

#define EFFECT_MAX 20
#define BLOCK_EFFECT_MAX 20

enum EFFECT_TYPE {
	EFFECT_T_BLOCK,
	EFFECT_T_MAX
};

//�������ߐ錾
void EffectSystemInit(void);
void EffectInit(void);
void EffectUpdata(void);
void EffectDraw(void);

void SetBlockEffect(XY pos);