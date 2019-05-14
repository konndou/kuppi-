#include "main.h"
#include "enemy.h"
#include "player1.h"
#include "keyCheck.h"
#include "stage.h"



CHARACTER enemy1;
int enemy1Image[2];




void EnemySystemInit(void)
{
	LoadDivGraph("image/boar2.png", 2, 2, 1, ENEMY1_SIZE_X, ENEMY1_SIZE_Y, enemy1Image);

}

void EnemyInit(void)
{
	enemy1.pos = { 0,0 };
	enemy1.size = { 64,64 };
	enemy1.sizeOffset = { (enemy1.size.x / 2),(enemy1.size.y / 2) };
	enemy1.imgLockCnt = 30;

}

void EnemyUpdate(void)
{
	if (enemy1.flag == true)
	{
		
		
	}
	
}

void EnemyDraw(void)
{

	int image = enemy1Image[enemy1.animCnt / 10 % 2];

	/*enemy1.animCnt++;
	if (enemy1.flag == true) 
	{
		if (enemy1.movedir == DIR_RIGHT) {
			DrawGraph(enemy1.pos.x - enemy1.sizeOffset.x, enemy1.pos.y - enemy1.sizeOffset.y, image, true);
		}
		if (enemy1.movedir == DIR_LEFT) {
			DrawTurnGraph(enemy1.pos.x - enemy1.sizeOffset.x, enemy1.pos.y - enemy1.sizeOffset.y, image, true);
		}
	}*/

	DrawGraph(0, 100, image, true);

}

CHARACTER GetEnemyPos(void)
{
	return enemy1;
}

//int GetStageCnt(void)
//{
//	return = stageCnt;
//}


