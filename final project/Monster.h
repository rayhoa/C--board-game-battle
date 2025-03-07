#pragma once
#include"object.h"
class Monster : public Object//怪物基礎資訊、怪物操作
{
private:
	int condition[3];//怪物所有模式 0不出現1普通2菁英
	int mode;//現在模式
	int attack;
	int range;
	int* chooseCard;//怪物選擇卡牌
	int typeMonster;//怪物種類
public:
	void setCondition(int a, int b, int c);
	void setMode(int a);
	int getCondition(int a);
	int getMode();
	void setAttack(int a);
	void setRange(int a);
	int getAttack();
	int getRange();
	void check();//輸出相關資訊
	Monster();
	int setChooseCard(int a);//設置選擇卡牌
	int getChooseCard();
	int getAgility();
	void setTypeMonster(int);
	int getTypeMonster();
	void shuffle();//洗牌
};