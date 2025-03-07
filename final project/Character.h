#pragma once
#include"object.h"
#include<vector>
using namespace std;
class Character : public Object//角色基礎資訊、角色操作
{
private:
	vector<int> *choosrcard;//選擇卡牌
	int typeCharacter;//角色種類
public:
	void check(int a);//輸出角色相關資訊
	Character();
	int setChooseCard(int a, int b);
	vector<int>* getChooseCard();
	int getAgility(int a);
	void setTypeCharacter(int a);
	int getTypeCharacter();
	bool deleteAbandonCard(int a);//棄牌和洗牌
};