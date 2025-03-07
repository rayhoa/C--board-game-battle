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
int CHARACTERNUM = 0;//����ƶq
int MONSTERNUM = 0;//�Ǫ��ƶq
Gloomhaven game;
int DEBUGMODE = 0;
int *DEBUG;//debugmode��1�ɩǪ���P
int DOORNUM = 0;//�����ƶq
using namespace std;
int main(int argc, char *argv[])
{
	srand(time(NULL));
	int round = 2;
	game.loadSourceFile(argv[1], argv[2]);//���J�}��P�Ǫ��ɮ�
	DEBUGMODE = *argv[3] - '0';//�]�mdebugmode
	if (initializeInput() == 1)//��l�ơAinitializeinput()�^��1�h�N��ϥΪ̿�Jexit
	{
		return 0;
	}
	DEBUG = new int[MONSTERNUM];//debugmode��1�ɡA�Ҧ��Ǫ���P
	for (int i = 0; i < MONSTERNUM; i++)
	{
		DEBUG[i] = 0;
	}
	getchar();
	cout << "round 1:" << '\n';
	while (1)
	{
		game.characterPreparing();//����ǳƶ��q
		game.monsterPreparing();//�Ǫ��ǳƶ��q
		game.actionStage();//�ʧ@���q
		if (game.endRound() == 1)//�^�X����,�^��1�h�N��ϥΪ̿�Jexit
		{
			delete[] DEBUG;
			return 0;
		}
		getchar();
		cout << "round " << round << ":" << '\n';
		round = round + 1;
	}
}