#pragma once
#include"CharacterSkill.h"
#include<vector>
#include<string>
using namespace std;
class CharacterData//�Ҧ������Ʈw
{
public:
	vector<string> name;
	vector<int> hp;
	vector<int> holdCard;//����Ҧ��d�P��
	vector<CharacterSkill>*allCharacterSkill;//����Ҧ��ޯ�d
	void addCharacter(string a, int b, int c);
};