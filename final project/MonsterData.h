#pragma once
#include"MonsterSkill.h"
#include<vector>
using namespace std;
class MonsterData//�Ҧ��Ǫ���Ʈw
{
public:
	vector<string> name;
	vector<int> normalHp;
	vector<int> normalAttack;
	vector<int> normalRange;
	vector<int> eliteHp;
	vector<int> eliteAttack;
	vector<int> eliteRange;
	vector<MonsterSkill> *allMonsterSkill;//�Ǫ��ޯ�d�P
	void addMonster(string aName, int anormalHp, int anormalAttack, int aNormalRange, int aeliteHp, int aeliteAttack, int aEliteRange);
};