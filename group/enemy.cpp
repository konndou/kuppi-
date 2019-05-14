#include "main.h"
#include "enemy.h"
#include "player1.h"
#include "keyCheck.h"
#include "stage.h"



CHARACTER enemy1;
int enemy1Image[2];




void EnemySystemInit(void)
{
	LoadDivGraph("image/boar3.png", 2, 2, 1, ENEMY1_SIZE_X, ENEMY1_SIZE_Y, enemy1Image);

}

void EnemyInit(void)
{
	enemy1.pos = { 100,100 };
	enemy1.size = { 32,32 };
	enemy1.sizeOffset = { (enemy1.size.x / 2),(enemy1.size.y / 2) };
	enemy1.hitPosS = { 8, 15 };
	enemy1.hitPosE = { 8, 17 };
	enemy1.moveSpeed = 4;
	enemy1.Velocity = { 0,0 };
	enemy1.jumpFlag = false;
	enemy1.imgLockCnt = 30;
	enemy1.movedir = DIR_LEFT;
	enemy1.flag = true;


}

void EnemyUpdate(void)
{
	if (enemy1.flag == true)
	{
		enemy1.jumpFlag = true;
		//�v���C���[1�W�����v
		if (enemy1.jumpFlag == true) {
			XY movedPos = enemy1.pos;
			XY movedHitCheck = movedPos;
			XY movedHitCheck2 = movedPos;
			XY movedHitCheck3 = movedPos;
			XY tmpIndex;
			XY tmpPos;


			movedPos.y -= enemy1.Velocity.y * SECOND_PER_FRAME;
			enemy1.Velocity.y -= ACC_G * SECOND_PER_FRAME;

			movedHitCheck.y = movedPos.y - enemy1.hitPosS.y;	//����̍��W�v�Z
			//����̉E��
			movedHitCheck2 = movedHitCheck;
			movedHitCheck2.x = movedPos.x + enemy1.hitPosS.x;
			//����̍���
			movedHitCheck3 = movedHitCheck;
			movedHitCheck3.x = movedPos.x - enemy1.hitPosS.x;

			//����Ƀu���b�N�����邩�ǂ���
			//�ʂ�邩�ǂ���
			if (IsPass(movedHitCheck) && IsPass(movedHitCheck2) && IsPass(movedHitCheck3)) {
				enemy1.pos = movedPos;
			}
			else {
				tmpIndex = MapPosToIndex(movedHitCheck);
				//	movedHitCheck.y / 32
				tmpIndex.y++;
				tmpPos = MapIndexToPos(tmpIndex);
				//	(movedHitCheck.y / 32) * 32
				enemy1.pos.y = tmpPos.y + enemy1.hitPosS.y;	//���ォ�璆�S�����߂�
				enemy1.Velocity.y *= -0.5;

				movedPos = enemy1.pos;
			}
			

			movedHitCheck.y = movedPos.y + enemy1.hitPosE.y;	//�����̍��W�v�Z
			//�����E��
			movedHitCheck2 = movedHitCheck;
			movedHitCheck2.x = movedPos.x + enemy1.hitPosE.x;
			//��������
			movedHitCheck3 = movedHitCheck;
			movedHitCheck3.x = movedPos.x - enemy1.hitPosE.x;

			//�����Ƀu���b�N�����邩�ǂ���
			//�ʂ�邩�ǂ���
			if (enemy1.Velocity.y < 0) {
				if (IsPass(movedHitCheck) && IsPass(movedHitCheck2) && IsPass(movedHitCheck3)) {
					enemy1.pos = movedPos;
				}
				else {
					tmpIndex = MapPosToIndex(movedHitCheck);	//�u���b�N�̏�̍��W���v�Z
																//	movedHitCheck.y / 32
					tmpPos = MapIndexToPos(tmpIndex);			//�����̂����W
																//	(movedHitCheck.y / 32) * 32
					enemy1.pos.y = tmpPos.y - enemy1.hitPosE.y;	//�������璆�S�����߂�
					enemy1.Velocity.y = 0;
					enemy1.jumpFlag = false;
				}
			}
		}
		
		
	}
	
}

void EnemyDraw(void)
{

	int image = enemy1Image[enemy1.animCnt / 10 % 2];

	enemy1.animCnt++;
	if (enemy1.flag == true) 
	{
		if (enemy1.movedir == DIR_RIGHT) {
			
			DrawTurnGraph(enemy1.pos.x - enemy1.sizeOffset.x, enemy1.pos.y - enemy1.sizeOffset.y, image, true);
		}
		if (enemy1.movedir == DIR_LEFT) {
			
			DrawGraph(enemy1.pos.x - enemy1.sizeOffset.x, enemy1.pos.y - enemy1.sizeOffset.y, image, true);
		}
	}

	

	

}

CHARACTER GetEnemyPos(void)
{
	return enemy1;
}

//int GetStageCnt(void)
//{
//	return = stageCnt;
//}


