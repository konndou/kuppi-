#pragma once

#define ITEM_MAX 2

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