#pragma once
#include"object.h"
class Monster : public Object//�Ǫ���¦��T�B�Ǫ��ާ@
{
private:
	int condition[3];//�Ǫ��Ҧ��Ҧ� 0���X�{1���q2�׭^
	int mode;//�{�b�Ҧ�
	int attack;
	int range;
	int* chooseCard;//�Ǫ���ܥd�P
	int typeMonster;//�Ǫ�����
public:
	void setCondition(int a, int b, int c);
	void setMode(int a);
	int getCondition(int a);
	int getMode();
	void setAttack(int a);
	void setRange(int a);
	int getAttack();
	int getRange();
	void check();//��X������T
	Monster();
	int setChooseCard(int a);//�]�m��ܥd�P
	int getChooseCard();
	int getAgility();
	void setTypeMonster(int);
	int getTypeMonster();
	void shuffle();//�~�P
};