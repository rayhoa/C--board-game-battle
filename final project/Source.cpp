#include<iostream>
#include"Header.h"
#include"point.h"
#include"Function.h"
#include<time.h>
#include<stdlib.h>
#include"Gloomhaven.h"
using namespace std;
const char MAPFLOOR = '1';
const char MAPWALL = '0';
const char MAPOBSTACLE = '2';
const char MAPDOOR = '3';
const char MAPCHOOSEPLACE = '_';
const char MAPNOWPOSITION = '*';
int CHARACTERNUM = 0;//角色數量
int MONSTERNUM = 0;//怪物數量
Gloomhaven game;
int DEBUGMODE = 0;
int *DEBUG;//debugmode為1時怪物手牌
int DOORNUM = 0;//門的數量
using namespace std;
int main(int argc, char *argv[])
{
	srand(time(NULL));
	int round = 2;
	game.loadSourceFile(argv[1], argv[2]);//載入腳色與怪物檔案
	DEBUGMODE = *argv[3] - '0';//設置debugmode
	if (initializeInput() == 1)//初始化，initializeinput()回傳1則代表使用者輸入exit
	{
		return 0;
	}
	DEBUG = new int[MONSTERNUM];//debugmode為1時，所有怪物手牌
	for (int i = 0; i < MONSTERNUM; i++)
	{
		DEBUG[i] = 0;
	}
	getchar();
	cout << "round 1:" << '\n';
	while (1)
	{
		game.characterPreparing();//角色準備階段
		game.monsterPreparing();//怪物準備階段
		game.actionStage();//動作階段
		if (game.endRound() == 1)//回合結算,回傳1則代表使用者輸入exit
		{
			delete[] DEBUG;
			return 0;
		}
		getchar();
		cout << "round " << round << ":" << '\n';
		round = round + 1;
	}
}