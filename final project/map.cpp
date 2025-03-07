#include"Header.h"
#include"Function.h"
#include"MapData.h"
#include<iostream>
using namespace std;
void MapData::updateCharacter(vector<Character>* characters)
{
	for (int i = 0; i < DOORNUM; i++)//更新門的icon
	{
		if (doorOpen[i] == 0)
		{
			_map[doorPosition[i].y][doorPosition[i].x] = MAPDOOR;
		}
	}
	int cSize = characters->size();
	for (int i = 0; i < cSize; i++)//更新角色位置
	{
		_map[(*(*characters)[i].getPosition()).y][(*(*characters)[i].getPosition()).x] = (*characters)[i].getIcon();
	}
}
int MapData::printMap()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (room[i][j] == 1)
			{
				if (_map[i][j] == MAPWALL)
				{
					cout << ' ';
				}
				else
				{
					cout << _map[i][j];
				}
			}
			else
			{
				cout << ' ';
			}
		}
		cout << '\n';
	}
	return 1;
}
void MapData::updateStartPoint()
{
	int sSize = startPoint.size();
	for (int i = 0; i < sSize; i++)
	{
		if (i == 3)
		{
			_map[startPoint[i].y][startPoint[i].x] = MAPNOWPOSITION;
			openDoor(startPoint[i]);
			break;
		}
		_map[startPoint[i].y][startPoint[i].x] = MAPCHOOSEPLACE;
	}
}
void MapData::updateMonster()
{
	int msize = monsters.size();
	for (int i = 0; i < msize; i++)
	{
		if (monsters[i].getMode() == 0)//0 怪物不出現
		{
			
		}
		else
		{
			_map[(*monsters[i].getPosition()).y][(*monsters[i].getPosition()).x] = monsters[i].getIcon();
		}
	}
}
int MapData::openDoor(Point2d startPoint)
{
	for (int i = 0; i < 4; i++)
	{
		Point2d point = startPoint;
		switch (i)
		{
			case 0:
				point.y = startPoint.y + 1;
				break;
			case 1:
				point.x = startPoint.x - 1;
				break;
			case 2:
				point.x = startPoint.x + 1;
				break;
			case 3:
				point.y = startPoint.y - 1;
				break;
		}
		if (_map[point.y][point.x] == MAPWALL || room[point.y][point.x] == 1)
		{
			continue;
		}
		if (_map[point.y][point.x] == MAPDOOR)
		{
			room[point.y][point.x] = 1;
			return 0;
		}
		room[point.y][point.x] = 1;
		for (int j = 0; j < MONSTERNUM; j++)
		{
			if (positionCmp(point,(*monsters[j].getPosition())) == 1)
			{
				monsters[j].setMode(monsters[j].getCondition(CHARACTERNUM - 2));
			}
		}
		openDoor(point);
	}
	return 0;
}