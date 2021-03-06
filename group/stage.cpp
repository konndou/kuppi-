
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
XY stagehaikeiPos[2];
int stageCnt;
int selectse;
int stagehaikeiImage[2];
int stagehaikei2Image[2];

struct Header {
	unsigned short w;	//マップの幅
	unsigned short h;	//マップの高さ
	unsigned short cw;	//チップの横
	unsigned short ch;	//チップの縦
	unsigned char layernum;	//レイヤの数
	unsigned char mode;	
};
Header header;

std::vector<unsigned char>mapData;
int chipH;
int mapH;

void stageSystemInit(void)
{
	stageCnt = 0;
	selectse = LoadSoundMem("bgm/select.mp3");
	stagehaikeiImage[0] = LoadGraph("image/haikei3.png");
	stagehaikeiImage[1] = LoadGraph("image/haikei3.png");

	stagehaikei2Image[0] = LoadGraph("image/haikei6.png");
	stagehaikei2Image[1] = LoadGraph("image/haikei6.png");
	
}

void stageInit(void)
{
	//マップデータのファイルを開く
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

	//ファイルを開く
	FileRead_read(&header, sizeof(header), mapH);

	chipH = LoadGraph("image/mapchip8.png", true);

	FileRead_seek(mapH, 16, SEEK_TOP);

	mapData.resize(header.w * header.h);	//マップデータの配列数を確定
	FileRead_read(mapData.data(), mapData.size(), mapH);

	FileRead_close(mapH);

	mapPos = { 0,0 };
	move = { 0,0 };
	stagehaikeiPos[0] = { 0,0 };
	stagehaikeiPos[1] = { 950,0 };
}

void stageScroll(void)
{
	//地図の操作
	CHARACTER playerTemp;
	playerTemp = GetPlayerPos();

	//マップの移動処理
	if (playerTemp.pos.x > mapPos.x + SCREEN_SIZE_X / 2) {
		move.x = playerTemp.pos.x - SCREEN_SIZE_X / 2 - mapPos.x;
		mapPos.x = mapPos.x + move.x;
	}

	if (playerTemp.pos.x < mapPos.x + SCREEN_SIZE_X / 6) {
		move.x = playerTemp.pos.x - SCREEN_SIZE_X / 6 - mapPos.x;
		mapPos.x = mapPos.x + move.x;
	}

	//移動制限
	if (mapPos.x < 0) {
		mapPos.x = 0;
	}

	if (mapPos.x > header.w * header.cw - SCREEN_SIZE_X) {
		mapPos.x = header.w * header.cw - SCREEN_SIZE_X;
	}
}

void stageUpdate(void)
{

	//地図の操作
	CHARACTER playerTemp;
	playerTemp = GetPlayerPos();

	//マップの移動処理
	if (playerTemp.pos.x > mapPos.x + SCREEN_SIZE_X / 2) {
		move.x = playerTemp.pos.x - SCREEN_SIZE_X / 2 - mapPos.x;
		mapPos.x = mapPos.x + move.x;
	}
	
	if (playerTemp.pos.x < mapPos.x + SCREEN_SIZE_X / 6) {
		move.x = playerTemp.pos.x - SCREEN_SIZE_X / 6 - mapPos.x;
		mapPos.x = mapPos.x + move.x;
	}

	if (mapPos.x < MAP_CHIP_X * MAP_CHIP_SIZE_X - SCREEN_SIZE_X)
	{
		if (playerTemp.pos.x > mapPos.x + SCREEN_SIZE_X / 2) {
			stagehaikeiPos[0].x = stagehaikeiPos[0].x - move.x / 2;
			stagehaikeiPos[1].x = stagehaikeiPos[1].x - move.x / 2;
		}
	}
	
	//移動制限
	if (mapPos.x < 0) {
		mapPos.x = 0;
	}

	if (mapPos.x > header.w * header.cw - SCREEN_SIZE_X) {
		mapPos.x = header.w * header.cw - SCREEN_SIZE_X;
	}

	for (int i = 0; i < 2; i++) {
		if (stagehaikeiPos[i].x <= -950) {
			stagehaikeiPos[i].x = 950;
		}
	}
	
}

void stageDraw(void)
{
	//マップデータのファイルを開く
	switch (stageCnt) {
	case 0:
	case 1:
	case 2:
	case 3:
		DrawGraph(stagehaikeiPos[0].x, stagehaikeiPos[0].y, stagehaikeiImage[0], true);
		DrawGraph(stagehaikeiPos[1].x, stagehaikeiPos[1].y, stagehaikeiImage[1], true);
		break;
	case 4:
		DrawGraph(stagehaikeiPos[0].x, stagehaikeiPos[0].y, stagehaikei2Image[0], true);
		DrawGraph(stagehaikeiPos[1].x, stagehaikeiPos[1].y, stagehaikei2Image[1], true);
		break;
	case 5:
		DrawGraph(stagehaikeiPos[0].x, stagehaikeiPos[0].y, stagehaikeiImage[0], true);
		DrawGraph(stagehaikeiPos[1].x, stagehaikeiPos[1].y, stagehaikeiImage[1], true);
		break;
	}
	
	for (int y = 0; y < header.h; y++) {
		for (int x = 0; x < header.w; x++) {
			auto idx = mapData[x + y * header.w];
			auto idxX = idx % 32;
			auto idxY = idx / 32;
			DrawRectGraph(x * header.cw - mapPos.x, y * header.ch, 
						 idxX * header.cw, idxY * header.ch, header.cw, header.ch, chipH, true, false, false);
		}
	}
	DrawFormatString(0, 100, 0x00ffff, "map %d", mapPos.x);
}

//マップのPosをindexに変える
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

//通れるか
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

	//通ってよいか
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

//ゴール演出中の足元
bool IsGPass(XY pos)
{
	bool ret = true;
	XY mapIndex;

	mapIndex = MapPosToIndex(pos);
	auto id = mapIndex.y * MAP_CHIP_X + mapIndex.x;
	if (id < 0)return ret;
	if (id > 6000)return ret;

	//通ってよいか
	switch (mapData[id]) {
	case 14:
	case 15:
	case 16:
		ret = false;
		break;
	}
	return ret;
}

//ゴールしているか
bool IsGoal2Pass(XY pos)
{
	bool ret = true;
	XY mapIndex;

	mapIndex = MapPosToIndex(pos);
	auto id = mapIndex.y * MAP_CHIP_X + mapIndex.x;
	if (id < 0)return ret;
	if (id > 6000)return ret;

	//通ってよいか
	switch (mapData[id]) {
	case 5:
		ret = false;
		break;
	}

	return ret;
}

//ゴールしているか
bool IsGoalPass(XY pos)
{
	bool ret = true;
	XY mapIndex;

	mapIndex = MapPosToIndex(pos);
	auto id = mapIndex.y * MAP_CHIP_X + mapIndex.x;
	if (id < 0)return ret;
	if (id > 6000)return ret;

	//通ってよいか
	switch (mapData[id]) {
	case 5:
	case 12:
		ret = false;
		break;
	}

	return ret;
}

//次のステージ
bool IsNextPass(XY pos)
{
	bool ret = true;
	XY mapIndex;

	mapIndex = MapPosToIndex(pos);
	auto id = mapIndex.y * MAP_CHIP_X + mapIndex.x;
	if (id < 0)return ret;
	if (id > 6000)return ret;

	//通ってよいか
	switch (mapData[id]) {
	case 21:
		ret = false;
		stageCnt = stageCnt + 1;
		break;
	}

	return ret;
}

//ゲームオーバー処理
bool IsOverPass(XY pos)
{
	bool ret = true;
	XY mapIndex;

	mapIndex = MapPosToIndex(pos);
	auto id = mapIndex.y * MAP_CHIP_X + mapIndex.x;
	if (id < 0)return ret;
	if (id > 6000)return ret;

	//通ってよいか
	switch (mapData[id]) {
	case 13:
	case 27:
		ret = false;
		break;
	}

	return ret;
 }

//敵キャラの方向転換
bool IsEnemyPass(XY pos)
{
	bool ret = true;
	XY mapIndex;
	mapIndex = MapPosToIndex(pos);

	auto id = mapIndex.y * MAP_CHIP_X + mapIndex.x;
	if (id < 0)return ret;
	if (id > 6000)return ret;

	//通ってよいか
	switch (mapData[id]) {
	case 0:
	case 22:
	case 24:
		ret = false;
		break;
	}
	return ret;
}

//アイテムの出現
bool ItemEvent(XY pos) 
{
	bool ret = true;
	XY mapIndex;
	mapIndex = MapPosToIndex(pos);

	auto id = mapIndex.y * MAP_CHIP_X + mapIndex.x;
	if (id < 0)return ret;
	if (id > 6000)return ret;

	//アイテムブロックがあるか
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
		PlaySoundMem(selectse, DX_PLAYTYPE_BACK, false);
		stageCnt++;
	}
	if (trgkey[P1_LEFT]) {
		PlaySoundMem(selectse, DX_PLAYTYPE_BACK, false);
		stageCnt--;
	}

	if (stageCnt <= 0) {
		stageCnt = 0;
	}
	if (stageCnt >= 5) {
		stageCnt = 5;
	}
}