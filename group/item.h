#pragma once

#define ITEM_MAX 100
#define ITEM_SIZE_X 32
#define ITEM_SIZE_Y 32

enum ITEM_TYPE
{
	ITEM_TYPE_CHEESE,
	ITEM_TYPE_ABOKADO,
	ITEM_TYPE_MAX
};

void ItemSystemInit(void);
void ItemInit(void);
void ItemUpdate(void);
void ItemDraw(void);

void ItemFlag(void);

bool ItemHitCheck(XY pPos, XY pSize);

CHARACTER GetItemPos(int i);

int GetItemNum(void);

void DeleteItem(int i);