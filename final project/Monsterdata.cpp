#include"Header.h"
#include"MonsterSkill.h"
#include"Monster.h"
#include"MonsterData.h"
#include<iostream>
using namespace std;
void MonsterSkill::setAgility(int a)
{
	agility = a;
}
void MonsterSkill::setSkill(string a)
{
	skill.push_back(a);
}
void MonsterSkill::setSkillNum(string a)
{
	skillNum.push_back(a);
}
void MonsterSkill::setReshuffle(char a)
{
	reshuffle = a;
}
int MonsterSkill::getAgility()
{
	return agility;
}
vector<string>& MonsterSkill::getSkill()
{
	return skill;
}
vector<string>& MonsterSkill::getSkillNum()
{
	return skillNum;
}
char MonsterSkill::getReshuffle()
{
	return reshuffle;
}
void Monster::setCondition(int a, int b, int c)
{
	condition[0] = a;
	condition[1] = b;
	condition[2] = c;
}
void Monster::setMode(int a)
{
	mode = a;
}
int Monster::getCondition(int a)
{
	return condition[a];
}
int Monster::getMode()
{
	return mode;
}
void Monster::setAttack(int a)
{
	attack = a;
}
void Monster::setRange(int a)
{
	range = a;
}
int Monster::getAttack()
{
	return attack;
}
int Monster::getRange()
{
	return range;
}
void Monster::check()
{
	cout << icon << "-hp: " << hp << " , shield: " << shield << '\n';
}
void MonsterData::addMonster(string aname, int anormalHp, int anormalAttack, int anormalRange, int aeliteHp, int aeliteAttack, int aeliteRange)
{
	name.push_back(aname);
	normalHp.push_back(anormalHp);
	normalAttack.push_back(anormalAttack);
	normalRange.push_back(anormalRange);
	eliteHp.push_back(aeliteHp);
	eliteAttack.push_back(aeliteAttack);
	eliteRange.push_back(aeliteRange);
}
Monster::Monster()
{
	abandonCard = new vector<int>;
	chooseCard = new int;
}
int Monster::setChooseCard(int a)
{
	delete chooseCard;
	chooseCard = new int;
	if (a == -1)//ªø¥ð
	{
		*chooseCard = -1;
	}
	int size = card.size(), n = 0;
	for (int j = 0; j < size; j++)
	{
		if (a == card[j])
		{
			n = -1;
		}
	}
	if (n == 0)
	{
		return 0;
	}
	deleteCard(a);
	*chooseCard = a;
}
int Monster::getChooseCard()
{
	return *chooseCard;
}
int Monster::getAgility()
{
	if (*chooseCard != -1)
	{
		return game.monsterd.allMonsterSkill[typeMonster][*chooseCard].getAgility();
	}
	return -1;
}
void Monster::setTypeMonster(int a)
{
	typeMonster = a;
}
int Monster::getTypeMonster()
{
	return typeMonster;
}
void Monster::shuffle()
{
	int size = abandonCard->size();
	for (int i = 0; i < size; i++)
	{
		card.push_back((*abandonCard)[i]);
	}
	delete abandonCard;
	abandonCard = new vector<int>;
}