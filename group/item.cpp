
#include "main.h"
#include "item.h"
#include "enemy.h"
#include "player1.h"
#include "keyCheck.h"
#include "stage.h"

CHARACTER itemtype[ITEM_TYPE_MAX];
CHARACTER item[ITEM_TYPE_MAX];
int itemImage[ITEM_TYPE_MAX];

void ItemSystemInit(void)
{
	itemImage[0] = LoadGraph("image/item1.png", true);
	itemImage[1] = LoadGraph("image/item2.png", true);

	for (int i = 0; i < ITEM_TYPE_MAX; i++) {
		itemtype[i].type = i;
		itemtype[i].movedir = DIR_RIGHT;
		itemtype[i].pos = { 0,0 };
		itemtype[i].size = { 32,32 };
		itemtype[i].sizeOffset = { itemtype[i].size.x / 2, itemtype[i].size.y / 2 };
	}
}

void ItemInit(void)
{
	for (int i = 0; i < ITEM_TYPE_MAX; i++) {
		item[i] = itemtype[i];
	}
}

void ItemUpdate(void)
{

}

void ItemDraw(void)
{

}