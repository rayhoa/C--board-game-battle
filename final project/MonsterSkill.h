#pragma once
#include<string>
#include<vector>
using namespace std;
class MonsterSkill//�Ǫ���ʥd��T
{
private:
	int agility;
	vector<string> skill;//�ޯ�
	vector<string> skillNum;//�ޯ�¾
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