#pragma once
#include"CharacterData.h"
#include"MonsterData.h"
#include"MapData.h"
#include"Character.h"
#include<vector>
#include<string>
#include"object.h"
#include"Action.h"

using namespace std;
class Gloomhaven//資料載入、遊戲初始化、遊戲功能實作。
{
public:
	CharacterData characterd;//所有角色資料
	MonsterData monsterd;//所有角色資料
	MapData map;//地圖
	vector<Character> characters;//使用角色
	char *gamerole;//角色與怪物順序
	void loadSourceFile(string cF, string mF);//讀取角色與怪物檔案
	int getInformation();//開始遊戲時讀取資訊
	int loadCharacterFile(string cF);//讀取角色檔案
	int loadMonsterFile(string mF);//讀取怪物檔案
	int loadMapFile(string mapF);//讀取地圖檔案
	void choosePosition();//選擇角色啟示位置
	void characterPreparing();//角色準備階段
	void monsterPreparing();//怪物準備階段
	void actionStage();//動作階段
	int endRound();//回合結算階段
};