#pragma once
#include"point.h"
#include<string>
#include"Header.h"
#include<cctype>
using namespace std;
class Action//四個技能敘述
{
	public:
		int attack(Point2d attackPosition, int *shield, int aDamage, int *hp, int range, char icon, char aIcon);//攻擊
		int move(Point2d* position, string moveAction, Point2d nowPositon, int stringPosition, int mode);//移動
		void heal(int *hp, int& maxHp, int increaseNum, char icon);//治癒
		void sheild(int *cardShield, int shieldnum, char icon);//護盾
};