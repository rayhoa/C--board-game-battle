#pragma once
#include"object.h"
#include<vector>
using namespace std;
class Character : public Object//�����¦��T�B����ާ@
{
private:
	vector<int> *choosrcard;//��ܥd�P
	int typeCharacter;//�������
public:
	void check(int a);//��X���������T
	Character();
	int setChooseCard(int a, int b);
	vector<int>* getChooseCard();
	int getAgility(int a);
	void setTypeCharacter(int a);
	int getTypeCharacter();
	bool deleteAbandonCard(int a);//��P�M�~�P
};