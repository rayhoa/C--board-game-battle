#pragma once
#include<string>
#include<vector>
using namespace std;
class MonsterSkill//怪物行動卡資訊
{
private:
	int agility;
	vector<string> skill;//技能
	vector<string> skillNum;//技能職
	char reshuffle;
public:
	void setAgility(int a);
	void setSkill(string a);
	void setSkillNum(string a);
	void setReshuffle(char a);
	int getAgility();
	vector<string>& getSkill();
	vector<string>& getSkillNum();
	char getReshuffle();
};