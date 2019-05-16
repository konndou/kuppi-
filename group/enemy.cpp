#include "main.h"
#include "enemy.h"
#include "player1.h"
#include "keyCheck.h"
#include "stage.h"


CHARACTER enemy[ENEMY_MAX];
int enemyImage[2];

void EnemySystemInit(void)
{
	LoadDivGraph("image/boar3.png", 2, 2, 1, ENEMY1_SIZE_X, ENEMY1_SIZE_Y, enemyImage);

	//LoadDivGraph("image/icon4.png", 16, 4, 4, ENEMY1_SIZE_X, ENEMY1_SIZE_Y, enemy1Image);
}

void EnemyInit(void)
{

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		int type = GetRand(2);

		switch (type)
		{
		case ENEMY_TYPE_BOAR:
			enemy[i].type = ENEMY_TYPE_BOAR;
			enemy[i].pos = { 100,100 };
			enemy[i].size = { 32,32 };
			enemy[i].sizeOffset = { (enemy[i].size.x / 2),(enemy[i].size.y / 2) };
			enemy[i].hitPosS = { 8, 15 };
			enemy[i].hitPosE = { 8, 17 };
			enemy[i].moveSpeed = 4;
			enemy[i].Velocity = { 0,0 };
			enemy[i].jumpFlag = false;
			enemy[i].imgLockCnt = 30;
			enemy[i].movedir = DIR_LEFT;
			enemy[i].flag = false;
			enemy[i].moveSpeed = 2;
			default:
				break; 
		}
	}
}

void EnemyUpdate(int i)
{
	//�G�L�����̕\��
	auto flag = GetRand(300);
	if (flag == 25) {
		enemy[i].flag = true;
	}

	if (enemy[i].flag == true)
	{
		//�G�L������n�ʂɗ��Ƃ�
		enemy[i].jumpFlag = true;
		
		if (enemy[i].jumpFlag == true) {
			XY movedPos = enemy[i].pos;
			XY movedHitCheck = movedPos;
			XY movedHitCheck2 = movedPos;
			XY movedHitCheck3 = movedPos;
			XY tmpIndex;
			XY tmpPos;

			movedPos.y -= enemy[i].Velocity.y * SECOND_PER_FRAME;
			enemy[i].Velocity.y -= ACC_G * SECOND_PER_FRAME;

			
			

			movedHitCheck.y = movedPos.y + enemy[i].hitPosE.y;	//�����̍��W�v�Z
			//�����E��
			movedHitCheck2 = movedHitCheck;
			movedHitCheck2.x = movedPos.x + enemy[i].hitPosE.x;
			//��������
			movedHitCheck3 = movedHitCheck;
			movedHitCheck3.x = movedPos.x - enemy[i].hitPosE.x;

			//�����Ƀu���b�N�����邩�ǂ���
			//�ʂ�邩�ǂ���
			if (enemy[i].Velocity.y < 0) {
				if (IsPass(movedHitCheck) && IsPass(movedHitCheck2) && IsPass(movedHitCheck3)) {
					enemy[i].pos = movedPos;
				}
				else {
					tmpIndex = MapPosToIndex(movedHitCheck);	//�u���b�N�̏�̍��W���v�Z
																//	movedHitCheck.y / 32
					tmpPos = MapIndexToPos(tmpIndex);			//�����̂����W
																//	(movedHitCheck.y / 32) * 32
					enemy[i].pos.y = tmpPos.y - enemy[i].hitPosE.y;	//�������璆�S�����߂�
					enemy[i].Velocity.y = 0;
					enemy[i].jumpFlag = false;
				}
			}
		}



		if (enemy[i].jumpFlag == false)
		{
			switch (enemy[i].movedir)
			{
			case DIR_LEFT:
				enemy[i].pos.x -= enemy[i].moveSpeed;
				break;
			case DIR_RIGHT:
				enemy[i].pos.x += enemy[i].moveSpeed;
				break;
			default:
				break;
			}
		}


		
		
	}
}

void EnemyDraw(int i)
{
	int image = enemyImage[enemy[i].animCnt / 10 % 2];

	enemy[i].animCnt++;
	if (enemy[i].flag == true) 
	{
		if (enemy[i].movedir == DIR_RIGHT) {
			DrawTurnGraph(enemy[i].pos.x - enemy[i].sizeOffset.x, enemy[i].pos.y - enemy[i].sizeOffset.y, image, true);
		}
		if (enemy[i].movedir == DIR_LEFT) {
			DrawGraph(enemy[i].pos.x - enemy[i].sizeOffset.x, enemy[i].pos.y - enemy[i].sizeOffset.y, image, true);
		}
	}
}

CHARACTER GetEnemyPos(int i)
{
	
	return enemy[i];
	
}

//int GetStageCnt(void)
//{
//	return = stageCnt;
//}


