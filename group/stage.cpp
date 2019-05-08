
#include "main.h"
#include "stage.h"
#include "keyCheck.h"
#include "player1.h"
#include <vector>

#define N 300
#define Row 20
#define SEEK_TOP 0

int mapImage[35];

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
	LoadDivGraph("image/mapchip.png", 35, 7, 5, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, mapImage);
}

void stageInit(void)
{
	switch (stageCnt) {
	case 0:
		mapH = FileRead_open("maptest.map", true);
		break;
	case 1:
		mapH = FileRead_open("map1.map", true);
		break;
	}

	FileRead_read(&header, sizeof(header), mapH);

	chipH = LoadGraph("image/mapchip2.png", true);

	FileRead_seek(mapH, 16, SEEK_TOP);

	mapData.resize(header.w * header.h);
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

			//DrawFormatString(x * header.cw, y * header.ch, 0xffffff, "%d", mapData[x + y * header.w]);
		}
	}

	/*
	for (int y = 0; y < MAP_CHIP_Y; y++) {
		for (int x = 0; x < MAP_CHIP_X; x++) {
			DrawGraph(MAP_CHIP_SIZE_X * x - mapPos.x, MAP_CHIP_SIZE_Y * y, mapImage[mapData[y][x]], true);
		}
	}

	for (int y = 0; y < MAP_CHIP_Y; y++) {
		for (int x = 0; x < MAP_CHIP_X; x++) {
			//DrawBox(MAP_CHIP_SIZE_X * x, MAP_CHIP_SIZE_Y * y, MAP_CHIP_SIZE_X * (x + 1), MAP_CHIP_SIZE_Y * (y + 1), 0x00ffff, false);
		}
	}
	DrawFormatString(32, 32, 0x000fff, "%d", mapPos.x);
	*/
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

/*
XY MapPosToMoveIndexPos(XY pos, MOVE_DIR dir)
{
	XY mapIndex;
}
*/

//通れるか
bool IsPass(XY pos)
{
	bool ret = true;
	XY mapIndex;

	mapIndex = MapPosToIndex(pos);
	auto id = mapIndex.y * 300 + mapIndex.x;
	if (id >= mapData.size()) {
		return false;
	}

	//通ってよいか
	switch (mapData[id]) {
	case 0:
	case 1:
	case 2:
	case 14:
	case 15:
	case 16:
	case 20:
	case 21:
	case 23:
	case 24:
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
	auto id = mapIndex.y * 300 + mapIndex.x;
	if (id >= mapData.size()) {
		return false;
	}

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
	auto id = mapIndex.y * 300 + mapIndex.x;
	if (id >= mapData.size()) {
		return false;
	}

	//通ってよいか
	switch (mapData[id]) {
	case 30:
		ret = false;
		stageCnt = stageCnt + 1;
		break;
	}

	return ret;
}

XY GetMapPos(void) {
	return mapPos;
}