#pragma once
#include"point.h"
#include<string>
#include"Header.h"
#include<cctype>
using namespace std;
class Action//�|�ӧޯ�ԭz
{
	public:
		int attack(Point2d attackPosition, int *shield, int aDamage, int *hp, int range, char icon, char aIcon);//����
		int move(Point2d* position, string moveAction, Point2d nowPositon, int stringPosition, int mode);//����
		void heal(int *hp, int& maxHp, int increaseNum, char icon);//�v¡
		void sheild(int *cardShield, int shieldnum, char icon);//�@��
};