#include"Action.h"
#include"Function.h"
#include<iostream>
using namespace std;
int Action::attack(Point2d attackPosition, int *shield, int aDamage, int *hp, int range, char icon, char aIcon)
{
	cout << icon << " attack " << aIcon << " " << aDamage << " damage, " << aIcon << " shield " << *shield << "," << ' ';
	if (aDamage - *shield < 0)
	{
		aDamage = 0;
	}
	else
	{
		aDamage = aDamage - *shield;
	}
	*hp = *hp - aDamage;
	cout << aIcon << " remain " << *hp << " hp" << '\n';
	if (*hp <= 0)//死亡
	{
		cout << aIcon << " is killed!! " << '\n';
		game.map._map[attackPosition.y][attackPosition.x] = MAPFLOOR;
	}
	return 1;
}
int Action::move(Point2d* position, string moveAction, Point2d nowPosition, int stringPosition, int mode)
{
	if (stringPosition == moveAction.size())
	{
		if (game.map._map[nowPosition.y][nowPosition.x] != MAPFLOOR)
		{
			if (mode == 0 && game.map._map[nowPosition.y][nowPosition.x] == MAPDOOR)//角色移動到門上
			{
				return 1;
			}
			if (mode == 0)
			{
				return 0;//錯誤移動
			}
			return 2;//移動到障礙物
		}
		(*position) = nowPosition;
		return 1;
	}
	else
	{
		vector<char> *map = game.map._map;
		int errorInput = 0;
		switch (moveAction[stringPosition])
		{
			case 'a':
				nowPosition.x = nowPosition.x - 1;
				break;
			case 's':
				nowPosition.y = nowPosition.y + 1;
				break;
			case 'w':
				nowPosition.y = nowPosition.y - 1;
				break;
			case 'd':
				nowPosition.x = nowPosition.x + 1;
				break;
			default:
				return 0;//錯誤移動
		}
		if (mode == 1)//怪獸移動
		{
			if (map[nowPosition.y][nowPosition.x] != MAPFLOOR && !islower(map[nowPosition.y][nowPosition.x]))
			{
				return 2;//移動到障礙物
			}
			errorInput = move(position, moveAction, nowPosition, stringPosition + 1, mode);
			if (errorInput == 2)
			{
				if (map[nowPosition.y][nowPosition.x] != MAPFLOOR)
				{
					return 2;//移動到障礙物
				}
				(*position) = nowPosition;
				return 1;
			}
			else if (errorInput == 0)
			{
				return 0;//錯誤移動
			}
		}
		else if (mode == 0)//角色移動
		{
			if (map[nowPosition.y][nowPosition.x] == MAPWALL || islower(map[nowPosition.y][nowPosition.x]) || map[nowPosition.y][nowPosition.x] == MAPOBSTACLE)//移動到障礙物
			{
				if (stringPosition == moveAction.size() - 1)
				{

				}
				else
				{
					nowPosition = (*position);
				}
			}
			(*position) = nowPosition;
			errorInput = move(position, moveAction, nowPosition, stringPosition + 1, mode);
			if (errorInput == 0)
			{
				return 0;//錯誤移動
			}
		}
		return 1;
	}
}
void Action::heal(int *hp, int& maxHp, int increaseNum, char icon)
{
	if (*hp + increaseNum > maxHp)//超過血量最大值
	{
		*hp = maxHp;
	}
	else
	{
		*hp = *hp + increaseNum;
	}
	cout << icon << " heal " << increaseNum << ", now hp is " << *hp << '\n';
}
void Action::sheild(int *cardShield, int shieldnum, char icon)
{
	*cardShield = shieldnum;
	cout << icon << " shield " << shieldnum << " this turn" << '\n';
}