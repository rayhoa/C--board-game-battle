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
class Gloomhaven//��Ƹ��J�B�C����l�ơB�C���\���@�C
{
public:
	CharacterData characterd;//�Ҧ�������
	MonsterData monsterd;//�Ҧ�������
	MapData map;//�a��
	vector<Character> characters;//�ϥΨ���
	char *gamerole;//����P�Ǫ�����
	void loadSourceFile(string cF, string mF);//Ū������P�Ǫ��ɮ�
	int getInformation();//�}�l�C����Ū����T
	int loadCharacterFile(string cF);//Ū�������ɮ�
	int loadMonsterFile(string mF);//Ū���Ǫ��ɮ�
	int loadMapFile(string mapF);//Ū���a���ɮ�
	void choosePosition();//��ܨ���ҥܦ�m
	void characterPreparing();//����ǳƶ��q
	void monsterPreparing();//�Ǫ��ǳƶ��q
	void actionStage();//�ʧ@���q
	int endRound();//�^�X���ⶥ�q
};