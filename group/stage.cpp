
#include "main.h"
#include "stage.h"
#include "keyCheck.h"
#include "player1.h"
#include "enemy.h"
#include <vector>
#include "boss.h"
#include "item.h"

#define SEEK_TOP 0

XY mapPos;
XY move;
int stageCnt;

struct Header {
	unsigned short w;	//�}�b�v�̕�
	unsigned short h;	//�}�b�v�̍���
	unsigned short cw;	//�`�b�v�̉�
	unsigned short ch;	//�`�b�v�̏c
	unsigned char layernum;	//���C���̐�
	unsigned char mode;	
};
Header header;

std::vector<unsigned char>mapData;
int chipH;
int mapH;

void stageSystemInit(void)
{
	stageCnt = 0;
}

void stageInit(void)
{
	//�}�b�v�f�[�^�̃t�@�C�����J��
	switch (stageCnt) {
	case 0:
		mapH = FileRead_open("map1.map", true);
		break;
	case 1:
		mapH = FileRead_open("map2.map", true);
		break;
	case 2:
		mapH = FileRead_open("map3.map", true);
		break;
	case 3:
		mapH = FileRead_open("map4.map", true);
		break;
	case 4:
		mapH = FileRead_open("boss.map", true);
		break;
	case 5:
		mapH = FileRead_open("map5.map", true);
		break;
	}

	//�t�@�C�����J��
	FileRead_read(&header, sizeof(header), mapH);

	chipH = LoadGraph("image/mapchip7.png", true);

	FileRead_seek(mapH, 16, SEEK_TOP);

	mapData.resize(header.w * header.h);	//�}�b�v�f�[�^�̔z�񐔂��m��
	FileRead_read(mapData.data(), mapData.size(), mapH);

	FileRead_close(mapH);

	mapPos = { 0,0 };
	move = { 0,0 };
}

void stageUpdate(void)
{

	//�n�}�̑���
	CHARACTER playerTemp;
	playerTemp = GetPlayerPos();

	//�}�b�v�̈ړ�����
	if (playerTemp.pos.x > mapPos.x + SCREEN_SIZE_X / 2) {
		move.x = playerTemp.pos.x - SCREEN_SIZE_X / 2 - mapPos.x;
		mapPos.x = mapPos.x + move.x;
	}
	
	if (playerTemp.pos.x < mapPos.x + SCREEN_SIZE_X / 6) {
		move.x = playerTemp.pos.x - SCREEN_SIZE_X / 6 - mapPos.x;
		mapPos.x = mapPos.x + move.x;
	}
	
	//�ړ�����
	if (mapPos.x < 0) {
		mapPos.x = 0;
	}

	if (mapPos.x > header.w * header.cw - SCREEN_SIZE_X) {
		mapPos.x = header.w * header.cw - SCREEN_SIZE_X;
	}
	
}

void stageDraw(void)
{
	for (int y = 0; y < header.h; y++) {
		for (int x = 0; x < header.w; x++) {
			auto idx = mapData[x + y * header.w];
			auto idxX = idx % 32;
			auto idxY = idx / 32;
			DrawRectGraph(x * header.cw - mapPos.x, y * header.ch, 
						 idxX * header.cw, idxY * header.ch, header.cw, header.ch, chipH, true, false, false);
		}
	}
}

//�}�b�v��Pos��index�ɕς���
XY MapPosToIndex(XY pos)
{
	XY mapIndex;

	mapIndex = { pos.x / MAP_CHIP_SIZE_X, pos.y / MAP_CHIP_SIZE_Y };

	return mapIndex;
}

XY MapIndexToPos(XY Index)
{
	XY pos;

	pos = { Index.x * MAP_CHIP_SIZE_X, Index.y * MAP_CHIP_SIZE_Y };

	return pos;
}

//�ʂ�邩
bool IsPass(XY pos)
{
	bool ret = true;
	XY mapIndex;

	mapIndex = MapPosToIndex(pos);
	auto id = mapIndex.y * MAP_CHIP_X + mapIndex.x;
	if (id < 0)return ret;
	if (id > 6000)return ret;
	if (id >= mapData.size()) {
		return false;
	}

	//�ʂ��Ă悢��
	switch (mapData[id]) {
	case 2:
	case 3:
	case 4:
	case 8:
	case 9:
	case 10:
	case 11:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 23:
	case 25:
	case 26:
		ret = false;
		break;
	}

	return ret;
}

//�S�[�����o���̑���
bool IsGPass(XY pos)
{
	bool ret = true;
	XY mapIndex;

	mapIndex = MapPosToIndex(pos);
	auto id = mapIndex.y * MAP_CHIP_X + mapIndex.x;
	if (id < 0)return ret;
	if (id > 6000)return ret;

	//�ʂ��Ă悢��
	switch (mapData[id]) {
	case 14:
	case 15:
	case 16:
		ret = false;
		break;
	}
	return ret;
}

//�S�[�����Ă��邩
bool IsGoal2Pass(XY pos)
{
	bool ret = true;
	XY mapIndex;

	mapIndex = MapPosToIndex(pos);
	auto id = mapIndex.y * MAP_CHIP_X + mapIndex.x;
	if (id < 0)return ret;
	if (id > 6000)return ret;

	//�ʂ��Ă悢��
	switch (mapData[id]) {
	case 5:
		ret = false;
		break;
	}

	return ret;
}

//�S�[�����Ă��邩
bool IsGoalPass(XY pos)
{
	bool ret = true;
	XY mapIndex;

	mapIndex = MapPosToIndex(pos);
	auto id = mapIndex.y * MAP_CHIP_X + mapIndex.x;
	if (id < 0)return ret;
	if (id > 6000)return ret;

	//�ʂ��Ă悢��
	switch (mapData[id]) {
	case 5:
	case 12:
		ret = false;
		break;
	}

	return ret;
}

//���̃X�e�[�W
bool IsNextPass(XY pos)
{
	bool ret = true;
	XY mapIndex;

	mapIndex = MapPosToIndex(pos);
	auto id = mapIndex.y * MAP_CHIP_X + mapIndex.x;
	if (id < 0)return ret;
	if (id > 6000)return ret;

	//�ʂ��Ă悢��
	switch (mapData[id]) {
	case 21:
		ret = false;
		stageCnt = stageCnt + 1;
		break;
	}

	return ret;
}

//�Q�[���I�[�o�[����
bool IsOverPass(XY pos)
{
	bool ret = true;
	XY mapIndex;

	mapIndex = MapPosToIndex(pos);
	auto id = mapIndex.y * MAP_CHIP_X + mapIndex.x;
	if (id < 0)return ret;
	if (id > 6000)return ret;

	//�ʂ��Ă悢��
	switch (mapData[id]) {
	case 13:
	case 27:
		ret = false;
		break;
	}

	return ret;
 }

bool IsEnemyPass(XY pos)
{
	bool ret = true;
	XY mapIndex;
	mapIndex = MapPosToIndex(pos);

	auto id = mapIndex.y * MAP_CHIP_X + mapIndex.x;
	if (id < 0)return ret;
	if (id > 6000)return ret;

	//�ʂ��Ă悢��
	switch (mapData[id]) {
	case 0:
	case 22:
	case 24:
		ret = false;
		break;
	}
	return ret;
}

//�A�C�e���̏o��
bool ItemEvent(XY pos) 
{
	bool ret = true;
	XY mapIndex;
	mapIndex = MapPosToIndex(pos);

	auto id = mapIndex.y * MAP_CHIP_X + mapIndex.x;
	if (id < 0)return ret;
	if (id > 6000)return ret;

	//�A�C�e���u���b�N�����邩
	switch (mapData[id]) {
	case 2:
		mapData[id] = 9;
		ret = false;
		break;
	case 25:
		mapData[id] = 26;
		ret = false;
		break;
	}
	return ret;
}

XY GetMapPos(void) {
	return mapPos;
}

int GetStageCnt(void) 
{
	return stageCnt;
}

void StageCntInit(void) 
{
	stageCnt = 0;
}

void StageSelect(void) 
{
	if (trgkey[P1_RIGHT]) {
		stageCnt++;
	}
	if (trgkey[P1_LEFT]) {
		stageCnt--;
	}

	if (stageCnt <= 0) {
		stageCnt = 0;
	}
	if (stageCnt >= 5) {
		stageCnt = 5;
	}
}