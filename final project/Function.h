#pragma once
#include"point.h"
#include<string>
#include"Action.h"
#include"Header.h"
#include<cmath>
int initializeInput();//��l�ƹC��
int positionCmp(Point2d a, Point2d b);//�y�Ф��
int positionCmp(Point2d a, Point2d b, int c);//�y�Ф���d��
int searchCharacter(vector<Character>& character, char a);//�M�䨤��
void charSwap(char *role,int a);//�r������
int findChooseCard(vector<int>& chooseCard, int a);//�b��ܥd�P���M��
void characterAction(CharacterData& characterd,Character *a,vector<Monster>& monsters,int& upDown,int& choosFirstCard);//����ޯ�ʧ@
int findMonster(vector<Monster>& monster, char a);//�Ǫ��M��
void updateMap();//�a�ϧ�s
float operator-(Point2d& a, Point2d& b); //a�Mb�������Z��
int checkRole(string a);//��X������T
int standOnDoor(int find);//�P�_�O�_�����⯸�b���W
int noMonster();//�P�_�O�_���Ǫ�
void reshuffleMonster();//���s�~�P
int characterDie();//�P�_�O�_���⦺�`
int inSight(Point2d& a, Point2d& b);//�����p��