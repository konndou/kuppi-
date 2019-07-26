#include "main.h"
#include "enemy.h"
#include "player1.h"
#include "keyCheck.h"
#include "stage.h"
#include "shot.h"
#include "boss.h"
#include "item.h"
#include "effect.h"

CHARACTER boss;
int bossImage[2];	//�{�X�̃C���[�W
int bossdieImage;	//�{�X�̎��񂾎��̉摜
bool bossclearFlag;	//�{�X��|�������ǂ���
bool bossdieflag;

int bossdiese;		//������
int bossdse;		//�e������������

int effectcnt;
int bosscnt;

void BossSystemInit(void)
{
	LoadDivGraph("image/snakeboss1.png", 2, 2, 1, BOSS_SIZE_X, BOSS_SIZE_Y, bossImage);
	bossdieImage = LoadGraph("image/snakedie6.png", true);
	bossdiese = LoadSoundMem("bgm/explosion.mp3");
	bossdse = LoadSoundMem("bgm/shot2.mp3");
	ChangeVolumeSoundMem(255, bossdse);
}

//�{�X�̏���
void BossInit(void)
{
	boss.pos = { 9200,100 };
	boss.size = { 256,256 };
	boss.sizeOffset = { (boss.size.x / 2),(boss.size.y / 2) };
	boss.hitPosS = { 64, 128 };
	boss.hitPosE = { 64, 128 };
	boss.moveSpeed = 4;
	boss.Velocity = { 0,0 };
	boss.jumpFlag = true;
	boss.imgLockCnt = 30;
	boss.movedir = DIR_LEFT;
	boss.moveSpeed = 2;
	boss.flagcnt = 0;
	boss.lifeMax = 100;
	boss.life = boss.lifeMax;
	auto stagecnt = GetStageCnt();
	switch (stagecnt) {
	case 4:
		boss.flag = true;
		break;
	default:
		boss.flag = false;
		break;
	}
	effectcnt = 0;
	bosscnt = 0;
	bossclearFlag = false;
	bossdieflag = false;
}

//�{�X�̏���
void BossUpdate(void)
{
	if (boss.flag == true)
	{
		//�G�L������n�ʂɗ��Ƃ�

		boss.jumpFlag = true;

		if (boss.jumpFlag == true) {
			XY movedPos = boss.pos;
			XY movedHitCheck = movedPos;
			XY movedHitCheck2 = movedPos;
			XY movedHitCheck3 = movedPos;
			XY tmpIndex;
			XY tmpPos;

			movedPos.y -= boss.Velocity.y * SECOND_PER_FRAME;
			boss.Velocity.y -= ACC_G * SECOND_PER_FRAME;

			movedHitCheck.y = movedPos.y + boss.hitPosE.y;	//�����̍��W�v�Z
			//�����E��
			movedHitCheck2 = movedHitCheck;
			movedHitCheck2.x = movedPos.x + boss.hitPosE.x;
			//��������
			movedHitCheck3 = movedHitCheck;
			movedHitCheck3.x = movedPos.x - boss.hitPosE.x;

			//�����Ƀu���b�N�����邩�ǂ���
			//�ʂ�邩�ǂ���
			if (boss.Velocity.y < 0) {
				if (IsPass(movedHitCheck) && IsPass(movedHitCheck2) && IsPass(movedHitCheck3)) {
					boss.pos = movedPos;
				}
				else {
					tmpIndex = MapPosToIndex(movedHitCheck);	//�u���b�N�̏�̍��W���v�Z
																//	movedHitCheck.y / 32
					tmpPos = MapIndexToPos(tmpIndex);			//�����̂����W
																//	(movedHitCheck.y / 32) * 32
					boss.pos.y = tmpPos.y - boss.hitPosE.y;	//�������璆�S�����߂�
					boss.Velocity.y = 0;
					boss.jumpFlag = false;
				}
			}
		}

		//�G�L�����̕����]��
		if (boss.jumpFlag == false) {
			XY movedPos = boss.pos;
			XY movedHitCheck = movedPos;
			XY movedHitCheck2 = movedPos;
			XY movedHitCheck3 = movedPos;

			movedHitCheck.y = movedPos.y + boss.hitPosE.y;	//�����̍��W�v�Z
			//�����E��
			movedHitCheck2 = movedHitCheck;
			movedHitCheck2.x = movedPos.x + boss.hitPosE.x;
			//��������
			movedHitCheck3 = movedHitCheck;
			movedHitCheck3.x = movedPos.x - boss.hitPosE.x;

			//�ʂ�邩�ǂ���
			if ((IsEnemyPass(movedHitCheck) && IsEnemyPass(movedHitCheck2) && IsEnemyPass(movedHitCheck3)) == false) {
				switch (boss.movedir)
				{
				case DIR_LEFT:
					boss.movedir = DIR_RIGHT;
					break;
				case DIR_RIGHT:
					boss.movedir = DIR_LEFT;
					break;
				}
			}

			movedHitCheck.y = movedPos.y;	//�����̍��W�v�Z
			//�����E��
			movedHitCheck2 = movedHitCheck;
			movedHitCheck2.x = movedPos.x + boss.hitPosE.x;
			//��������
			movedHitCheck3 = movedHitCheck;
			movedHitCheck3.x = movedPos.x - boss.hitPosE.x;

			if ((IsPass(movedHitCheck) && IsPass(movedHitCheck2) && IsPass(movedHitCheck3)) == false) {
				switch (boss.movedir)
				{
				case DIR_LEFT:
					boss.movedir = DIR_RIGHT;
					break;
				case DIR_RIGHT:
					boss.movedir = DIR_LEFT;
					break;
				}
			}
		}

		//�G�L�����̈ړ�
		if (boss.jumpFlag == false)
		{
			switch (boss.movedir)
			{
			case DIR_LEFT:
				boss.pos.x -= boss.moveSpeed;
				break;
			case DIR_RIGHT:
				boss.pos.x += boss.moveSpeed;
				break;
			default:
				break;
			}
		}
	}

	//�V���b�g�̓����蔻��
	if (boss.flag == true) {
		if (shotHitCheck(boss.pos, boss.size) == true) {
			PlaySoundMem(bossdse, DX_PLAYTYPE_BACK, false);
			boss.life -= 5;
			XY shotTemp = GetShotPos();
			SetBlockEffect(shotTemp);
			Deleteshot();
		}
	}

	//���񂾂Ƃ�
	if (boss.life <= 0) {
		bosscnt++;
		boss.flag = false;
		bossdieflag = true;
		if (bosscnt == 1) {
			SetBlockBoss2Effect(boss.pos);
		}
		if(bosscnt > 60){
			bossclearFlag = true;
			for (int i = 0; i < BOSS_EFFECT_MAX; i++) {
				if (effectcnt < 200) {
					SetBlockBossEffect(boss.pos, i);
				}
			}
			PlaySoundMem(bossdiese, DX_PLAYTYPE_BACK, false);
			PlaySoundMem(bossdiese, DX_PLAYTYPE_LOOP, false);
		}
		
	}

}

//�`�揈��
void BossDraw(void)
{
	XY mapTemp = GetMapPos();

	int image = bossImage[boss.animCnt / 10 % 2];
	if (boss.flag == false) {
		image = bossdieImage;
	}

	boss.animCnt++;
	if (boss.flag == true)
	{
		if (boss.movedir == DIR_RIGHT) {
			DrawTurnGraph(boss.pos.x - boss.sizeOffset.x - mapTemp.x, boss.pos.y - boss.sizeOffset.y, image, true);
		}
		if (boss.movedir == DIR_LEFT) {
			DrawGraph(boss.pos.x - boss.sizeOffset.x - mapTemp.x, boss.pos.y - boss.sizeOffset.y, image, true);
		}
	}
	//�{�X�����񂾎��̉摜
	auto stagecnt = GetStageCnt();
	switch (stagecnt) {
	case 4:
		if (bossdieflag == true) {
			if (boss.flag == false)
			{
				if (boss.movedir == DIR_RIGHT) {
					DrawTurnGraph(boss.pos.x - boss.sizeOffset.x - mapTemp.x, boss.pos.y - boss.sizeOffset.y, image, true);
				}
				if (boss.movedir == DIR_LEFT) {
					DrawGraph(boss.pos.x - boss.sizeOffset.x - mapTemp.x, boss.pos.y - boss.sizeOffset.y, image, true);
				}
			}
		}
		break;
	default:
		break;
	}
}

bool BossHitCheck(XY sPos, XY sSize)
{
	if (boss.flag == true) {
		auto a = hypot(sPos.x - boss.pos.x, sPos.y - boss.pos.y);
		if (sSize.x / 2 + boss.size.x / 2 > a)
		{
			return true;
		}
		/*if (   (boss.pos.x - boss.size.x / 2 < sPos.x + sSize.x / 2)
			&& (boss.pos.x + boss.size.x / 2 > sPos.x - sSize.x / 2)
			&& (boss.pos.y - boss.size.y / 2 < sPos.y + sSize.y / 2)
			&& (boss.pos.y + boss.size.y / 2 > sPos.y - sSize.y / 2)) {
			
		}*/
	}
	return false;
}

//�N���A��ʂ܂�
bool BossClear(void)
{
	if (bossclearFlag == true) {
		effectcnt++;
		if (effectcnt > 200) {
			bossdieflag = false;
			StopSoundMem(bossdiese);
			return true;
		}
	}
	return false;
}