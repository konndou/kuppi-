
#include "main.h"
#include "item.h"
#include "enemy.h"
#include "player1.h"
#include "keyCheck.h"
#include "stage.h"

CHARACTER item[ITEM_MAX];
int cheeseImage;
int abokadoImage;

void ItemSystemInit(void)
{
	cheeseImage = LoadGraph("image/item1.png", true);
	abokadoImage = LoadGraph("image/item2.png", true);
}

void ItemInit(void)
{
	for (int i = 0; i < ITEM_MAX; i++) {
		item[i].pos = { 0,0 };
		item[i].movedir = DIR_RIGHT;
		item[i].moveSpeed = 2;
		item[i].size = { 32,32 };
		item[i].sizeOffset = { item[i].size.x / 2, item[i].size.y / 2 };
		item[i].flag = false;
	}
}

void ItemUpdate(void)
{

}

void ItemDraw(void)
{

}