#pragma once
#include"Monster.h"
#include"Character.h"
#include"point.h"
#include<vector>
using namespace std;
class MapData//地圖資訊
{
public:
	vector<char> *_map;//地圖
	vector<Point2d>startPoint;//起始位置
	vector<Monster> monsters;//怪物
	int row;
	int column;
	int *doorOpen;//門的開關
	vector<Point2d> doorPosition;//門的位置
	vector<int> *room;//地圖顯示
	void updateStartPoint();//初始位置更新至地圖上
	void updateCharacter(vector<Character>* characters);//角色位置更新
	void updateMonster();//怪物位置更新
	int printMap();//輸出地圖
	int openDoor(Point2d startPoint);//開門房間
};