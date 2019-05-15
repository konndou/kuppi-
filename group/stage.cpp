
#include "main.h"
#include "stage.h"
#include "keyCheck.h"
#include "player1.h"
#include "enemy.h"
#include <vector>

#define SEEK_TOP 0

XY mapPos;
XY move;
int stageCnt = 0;

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
	}

	//ファイルを開く
	FileRead_read(&header, sizeof(header), mapH);

	chipH = LoadGraph("image/mapchip2.png", true);

	FileRead_seek(mapH, 16, SEEK_TOP);

	mapData.resize(header.w * header.h);	//マップデータの配列数を確定
	FileRead_read(mapData.data(), mapData.size(), mapH);

	FileRead_close(mapH);

	mapPos = { 0,0 };
	move = { 0,0 };
}

void stageUpdate(void)
{

	//地図の操作
	CHARACTER playerTemp;
	playerTemp = GetPlayerPos();

	//マップの移動処理
	if (playerTemp.pos.x > mapPos.x + SCREEN_SIZE_X / 2) {
		move.x = + playerTemp.pos.x - SCREEN_SIZE_X / 2 - mapPos.x;
		mapPos.x = mapPos.x + move.x;
	}
	
	if (playerTemp.pos.x < mapPos.x + SCREEN_SIZE_X / 6) {
		move.x = + playerTemp.pos.x - SCREEN_SIZE_X / 6 - mapPos.x;
		mapPos.x = mapPos.x + move.x;
	}
	
	//移動制限
	if (mapPos.x < 0) {
		mapPos.x = 0;
	}
	
}

void stageDraw(void)
{
	
	for (int y = 0; y < header.h; y++) {
		for (int x = 0; x < header.w; x++) {
			auto idx = mapData[x + y * header.w];
			auto idxX = idx % 32;
			auto idxY = idx / 32;
			DrawRectGraph(x * header.cw - mapPos.x, y * header.ch, idxX * header.cw, idxY * header.ch, header.cw, header.ch, chipH, true, false, false);
		}
	}
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
	//通ってよいか
	switch (mapData[id]) {
	case 13:
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

void StageCntInit(void) {
	stageCnt = 0;
}

