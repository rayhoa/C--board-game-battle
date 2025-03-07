#pragma once
#include"point.h"
#include<string>
#include<vector>
using namespace std;
class Object
{
	protected:
		string name;
		Point2d position;
		char icon;
		int hp;
		int shield = 0;
		vector<int>card;
		vector<int> *abandonCard;
	public:
		void setName(string a);
		void setPosition(Point2d a);
		void setPosition(int x, int y);
		void setIcon(char a);
		void setHp(int a);
		string getName();
		Point2d* getPosition();
		char getIcon();
		int* getHp();
		void setShield(int a);
		int* getShield();
		void addCard(int a);//�s�W�d�P�ܤ�d
		bool deleteCard(int a);//�R����d
		vector<int>* getCard();
		vector<int>* getAbandonCard();
};