#pragma once
#include"CharacterSkill.h"
#include<vector>
#include<string>
using namespace std;
class CharacterData//所有角色資料庫
{
public:
	vector<string> name;
	vector<int> hp;
	vector<int> holdCard;//角色所有卡牌數
	vector<CharacterSkill>*allCharacterSkill;//角色所有技能卡
	void addCharacter(string a, int b, int c);
};