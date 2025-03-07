#include"Header.h"
#include"CharacterSkill.h"
#include"CharacterData.h"
#include"Character.h"
#include<iostream>
using namespace std;
void CharacterSkill::setAgilicy(int a)
{
	agility = a;
}
void CharacterSkill::setUpSkill(string a)
{
	upSkill.push_back(a);
}
void CharacterSkill::setUpSkillNum(int a)
{
	upSkillNum.push_back(a);
}
void CharacterSkill::setDownSkill(string a)
{
	downSkill.push_back(a);
}
void CharacterSkill::setDownSkillNum(int a)
{
	downSkillNum.push_back(a);
}
int CharacterSkill::getAgility()
{
	return agility;
}
vector<string>& CharacterSkill::getUpSkill()
{
	return upSkill;
}
vector<int>& CharacterSkill::getUpSkillNum()
{
	return upSkillNum;
}
vector<string>& CharacterSkill::getDownSkill()
{
	return downSkill;
}
vector<int>& CharacterSkill::getDownSkillNum()
{
	return downSkillNum;
}
void CharacterData::addCharacter(string a, int b, int c)
{
	name.push_back(a);
	hp.push_back(b);
	holdCard.push_back(c);
}
void Character::check(int a)
{
	if (a == 0)
	{
		int cardNum = card.size();
		cout << "hand:";
		for (int i = 0; i < cardNum; i++)//輸出card
		{
			cout << " " << card[i];
			if (i == cardNum - 1)
			{
				cout << ';';
			}
			else
			{
				cout << ',';
			}
		}
		cardNum = abandonCard->size();
		cout << " discard:";
		for (int i = 0; i < cardNum; i++)//輸出discard
		{
			cout << " " << (*abandonCard)[i];
			if (i == cardNum - 1)
			{
				
			}
			else
			{
				cout << ',';
			}
		}
		cout << '\n';
	}
	else if (a == 1)
	{
		cout << icon << "-hp: " << hp << " , shield: " << shield << '\n';
	}
}
Character::Character()
{
	abandonCard = new vector<int>;
	choosrcard = new vector<int>;

}
int Character::setChooseCard(int a, int b)
{
	delete choosrcard;
	choosrcard = new vector<int>;
	if (a == -1)//長休
	{
		choosrcard->push_back(a);
		return 1;
	}
	int size = card.size(), nA = 0,nB = 0;
	for (int j = 0; j < size; j++)//尋找卡片
	{
		if (a == card[j])
		{
			nA = -1;
		}
	}
	if (nA == 0)
	{
		return 0;
	}
	for (int j = 0; j < size; j++)//尋找卡片
	{
		if (b == card[j])
		{
			nB = -1;
		}
	}
	if (nB == 0)
	{
		return 0;
	}
	sort((*abandonCard).begin(), (*abandonCard).end());
	choosrcard->push_back(a);
	choosrcard->push_back(b);
	return 1;
}
vector<int>* Character::getChooseCard()
{
	return choosrcard;
}
int Character::getAgility(int a)
{
	if (hp <= 0)//死亡角色
	{
		return 100;
	}
	if ((*choosrcard)[0] == -1)//長休角色
	{
		return 99;
	}
	return game.characterd.allCharacterSkill[typeCharacter][(*choosrcard)[a - 1]].getAgility();
}
void Character::setTypeCharacter(int a)
{
	typeCharacter = a;
}
int Character::getTypeCharacter()
{
	return typeCharacter;
}
bool Character::deleteAbandonCard(int a)
{
	int find = 0;
	for (int i = 0; i < abandonCard->size(); i++)//丟棄卡牌
	{
		if ((*abandonCard)[i] == a)
		{
			(*abandonCard).erase((*abandonCard).begin() + i);
			find = 1;
		}
	}
	if (find == 0)
	{
		return false;
	}
	for (int i = 0; i < abandonCard->size(); i++)//放回card中
	{
		card.push_back((*abandonCard)[i]);
	}
	sort(card.begin(), card.end());
	delete abandonCard;
	abandonCard = new vector<int>;
	return true;
}