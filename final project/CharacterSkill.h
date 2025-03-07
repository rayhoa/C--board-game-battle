#pragma once
#include<vector>
#include<string>
using namespace std;
class CharacterSkill//角色技能卡資訊
{
private:
	int agility;
	vector<string> upSkill;
	vector<int> upSkillNum;
	vector<string> downSkill;
	vector<int> downSkillNum;
public:
	void setAgilicy(int a);
	void setUpSkill(string a);
	void setUpSkillNum(int a);
	void setDownSkill(string a);
	void setDownSkillNum(int a);
	int getAgility();
	vector<string>& getUpSkill();
	vector<int>& getUpSkillNum();
	vector<string>& getDownSkill();
	vector<int>& getDownSkillNum();
};