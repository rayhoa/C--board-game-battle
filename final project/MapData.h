#pragma once
#include"Monster.h"
#include"Character.h"
#include"point.h"
#include<vector>
using namespace std;
class MapData//�a�ϸ�T
{
public:
	vector<char> *_map;//�a��
	vector<Point2d>startPoint;//�_�l��m
	vector<Monster> monsters;//�Ǫ�
	int row;
	int column;
	int *doorOpen;//�����}��
	vector<Point2d> doorPosition;//������m
	vector<int> *room;//�a�����
	void updateStartPoint();//��l��m��s�ܦa�ϤW
	void updateCharacter(vector<Character>* characters);//�����m��s
	void updateMonster();//�Ǫ���m��s
	int printMap();//��X�a��
	int openDoor(Point2d startPoint);//�}���ж�
};