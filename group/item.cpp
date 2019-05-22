
#include "main.h"
#include "item.h"
#include "enemy.h"
#include "player1.h"
#include "keyCheck.h"
#include "stage.h"

CHARACTER itemtype[ITEM_TYPE_MAX];
CHARACTER item[ITEM_MAX];
int itemImage[ITEM_TYPE_MAX];

int cntitem = 0;
int itemnum;

void ItemSystemInit(void)
{
	itemImage[0] = LoadGraph("image/item1.png", true);
	itemImage[1] = LoadGraph("image/item2.png", true);
}

void ItemInit(void)
{
	for (int i = 0; i < ITEM_TYPE_MAX; i++) {
		itemtype[i].type = i;
		itemtype[i].moveSpeed = 2;
		itemtype[i].flag = false;
		itemtype[i].movedir = DIR_RIGHT;
		itemtype[i].jumpFlag = false;
		itemtype[i].hitPosS = { 8, 16 };
		itemtype[i].hitPosE = { 12, 16 };
		itemtype[i].pos = { 0,0 };
		itemtype[i].size = { ITEM_SIZE_X,ITEM_SIZE_Y };
		itemtype[i].sizeOffset = { itemtype[i].size.x / 2, itemtype[i].size.y / 2 };
	}

	for (int i = 0; i < ITEM_MAX; i++) {
		auto type = GetRand(1);

		item[i] = itemtype[type];
	}
}

void ItemUpdate(void)
{
	for (int i = 0; i < ITEM_MAX; i++) {
		if (item[i].flag == true) {
			if (item[i].movedir == DIR_RIGHT) {
				item[i].pos.x += item[i].moveSpeed;
			}
			if (item[i].movedir == DIR_LEFT) {
				item[i].pos.x -= item[i].moveSpeed;
			}

			item[i].jumpFlag = true;

			if (item[i].jumpFlag == true) {
				XY movedPos = item[i].pos;
				XY movedHitCheck = movedPos;
				XY movedHitCheck2 = movedPos;
				XY movedHitCheck3 = movedPos;
				XY tmpIndex;
				XY tmpPos;

				movedPos.y -= item[i].Velocity.y * SECOND_PER_FRAME;
				item[i].Velocity.y -= ACC_G * SECOND_PER_FRAME;

				movedHitCheck.y = movedPos.y + item[i].hitPosE.y;	//�����̍��W�v�Z
				//�����E��
				movedHitCheck2 = movedHitCheck;
				movedHitCheck2.x = movedPos.x + item[i].hitPosE.x;
				//��������
				movedHitCheck3 = movedHitCheck;
				movedHitCheck3.x = movedPos.x - item[i].hitPosE.x;

				//�����Ƀu���b�N�����邩�ǂ���
				//�ʂ�邩�ǂ���
				if (item[i].Velocity.y < 0) {
					if (IsPass(movedHitCheck) && IsPass(movedHitCheck2) && IsPass(movedHitCheck3)) {
						item[i].pos = movedPos;
					}
					else {
						tmpIndex = MapPosToIndex(movedHitCheck);	//�u���b�N�̏�̍��W���v�Z
																	//	movedHitCheck.y / 32
						tmpPos = MapIndexToPos(tmpIndex);			//�����̂����W
																	//	(movedHitCheck.y / 32) * 32
						item[i].pos.y = tmpPos.y - item[i].hitPosE.y;	//�������璆�S�����߂�
						item[i].Velocity.y = 0;
						item[i].jumpFlag = false;
					}
				}
			}

			//�G�L�����̕����]��
			if (item[i].jumpFlag == false) {
				XY movedPos = item[i].pos;
				XY movedHitCheck = movedPos;
				XY movedHitCheck2 = movedPos;
				XY movedHitCheck3 = movedPos;

				movedHitCheck.y = movedPos.y;	//�����̍��W�v�Z
							//�����E��
				movedHitCheck2 = movedHitCheck;
				movedHitCheck2.x = movedPos.x + item[i].hitPosE.x;
				//��������
				movedHitCheck3 = movedHitCheck;
				movedHitCheck3.x = movedPos.x - item[i].hitPosE.x;

				if ((IsPass(movedHitCheck) && IsPass(movedHitCheck2) && IsPass(movedHitCheck3)) == false) {
					switch (item[i].movedir)
					{
					case DIR_LEFT:
						item[i].movedir = DIR_RIGHT;
						break;
					case DIR_RIGHT:
						item[i].movedir = DIR_LEFT;
						break;
					}
				}
			}
		}
	}
}

void ItemDraw(void)
{
	XY mapTemp = GetMapPos();
	for (int i = 0; i < ITEM_MAX; i++) {
		if (item[i].flag == true) {
			switch (item[i].type) {
			case ITEM_TYPE_CHEESE:
				DrawGraph(item[i].pos.x - item[i].sizeOffset.x - mapTemp.x, item[i].pos.y - item[i].sizeOffset.y, itemImage[0], true);
				break;
			case ITEM_TYPE_ABOKADO:
				DrawGraph(item[i].pos.x - item[i].sizeOffset.x - mapTemp.x, item[i].pos.y - item[i].sizeOffset.y, itemImage[1], true);
				break;
			}
		}
	}
}

void ItemFlag(void)
{
	CHARACTER playerTemp = GetPlayerPos();

	if ( cntitem < ITEM_MAX) {
		if (item[cntitem].flag == false) {
			item[cntitem].pos = { playerTemp.pos.x, playerTemp.pos.y - 64 };
			item[cntitem].type = GetRand(1);
			switch (item[cntitem].type) {
			case ITEM_TYPE_CHEESE:
				item[cntitem].flag = true;
				cntitem = cntitem + 1;
				break;
			case ITEM_TYPE_ABOKADO:
				item[cntitem].flag = true;
				cntitem = cntitem + 1;
				break;
			}
		}
	}
}

bool ItemHitCheck(XY pPos, XY pSize)
{
	for (int i = 0; i < ITEM_MAX; i++) {
		if (item[i].flag == true) {
			if (   (item[i].pos.x - item[i].size.x / 2 < pPos.x + pSize.x / 2 - 16)
				&& (item[i].pos.x + item[i].size.x / 2 > pPos.x - pSize.x / 2 + 16)
				&& (item[i].pos.y - item[i].size.y / 2 < pPos.y + pSize.y / 2)
				&& (item[i].pos.y + item[i].size.y / 2 > pPos.y - pSize.y / 2)) {
				itemnum = i;
				return true;
			}
		}
	}
	return false;
}

CHARACTER GetItemPos(int i)
{
	return item[i];
}

int GetItemNum(void) 
{
	return itemnum;
}

void DeleteItem(int i) 
{
	item[i].flag = false;
}