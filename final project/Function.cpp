#include"Function.h"
#include<iostream>
using namespace std;
int initializeInput()
{
	if (game.characters.size() != 0)//round > 1�ɡA��l�Ƹ��
	{
		delete[] game.map._map;
		game.characters.erase(game.characters.begin(), game.characters.end());
		game.map.monsters.erase(game.map.monsters.begin(), game.map.monsters.end());
		MapData a;
		game.map = a;
	}
	if (game.getInformation() == 1)//�C���P�����T
	{
		return 1;
	}
	game.map.updateStartPoint();//��l��m��s��map�W
	game.map.updateMonster();//��s�Ǫ���m
	game.map.printMap();//��X�a��
	game.choosePosition();//��ܰ_�l��m
	return 0;
}
int positionCmp(Point2d a, Point2d b)
{
	if (a.x == b.x&&a.y == b.y)
	{
		return 1;
	}
	return 0;
}
int positionCmp(Point2d a, Point2d b, int c)
{
	if ((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) < c*c)
	{
		return 1;
	}
	else if ((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) > c*c)
	{
		return 2;
	}
	return 0;
}
int searchCharacter(vector<Character>& character, char a)
{
	int size = character.size();
	for (int i = 0; i < size; i++)
	{
		if (character[i].getIcon() == a)
		{
			if (*character[i].getHp() > 0)
			{
				return i;
			}
		}
	}
	return -1;
}
void charSwap(char *role, int a)
{
	int tempint = role[a];
	role[a] = role[a + 1];
	role[a + 1] = tempint;
}
int findChooseCard(vector<int>& chooseCard, int a)
{
	for (int i = 0; i < 2; i++)
	{
		if (chooseCard[i] == a)
		{
			return i;
		}
	}
	return -1;
}
void characterAction(CharacterData& characterd, Character *a, vector<Monster>& monsters, int& upDown, int& chooseFirstCard)
{
	for (int i = 0; i < 2; i++)//��i����d�ʧ@
	{
		vector<string> *actionName;
		CharacterSkill *skill = &characterd.allCharacterSkill[a->getTypeCharacter()][(*a->getChooseCard())[(chooseFirstCard + i) % 2]];
		Action action;
		vector<int> *actionNum;
		if ((i + upDown) % 2 == 0)//�W�U�b��
		{
			actionName = &skill->getUpSkill();
			actionNum = &skill->getUpSkillNum();
		}
		else
		{
			actionName = &skill->getDownSkill();
			actionNum = &skill->getDownSkillNum();
		}
		int size = actionName->size();
		for (int j = 0; j < size; j++)//�@�i�P�����ޯ�
		{
			if ((*actionName)[j] == "move")//����
			{
				string moveString;
				cout << "Enter w a s d to move:" << '\n';
				cin >> moveString;
				if (moveString[0] == 'e')//����
				{
					game.map.printMap();
					continue;
				}
				if (checkRole(moveString))//�ϥΪ̿�Jcheck
				{
					j--;
					continue;
				}
				if (moveString.size() > (*actionNum)[j])//���ʼƹL�h
				{
					cout << "error move!!!" << '\n';
					j--;
					continue;
				}
				Point2d pPosition;
				pPosition = (*a->getPosition());
				game.map._map[pPosition.y][pPosition.x] = MAPFLOOR;
				if (!action.move(a->getPosition(), moveString, (*a->getPosition()), 0, 0))//����
				{
					cout << "error move!!!" << '\n';
					a->setPosition(pPosition.x, pPosition.y);
					j--;
					continue;
				}
				updateMap();
			}
			else if ((*actionName)[j] == "attack")//����
			{
				int range = 0, find = 0;
				string monster;
				cout << "Choose a target which you want to attack:" << '\n';
				cin >> monster;
				if (monster[0] == '0')//������
				{
					continue;
				}
				if (checkRole(monster))//�ϥΪ̿�Jcheck
				{
					j--;
					continue;
				}
				find = findMonster(monsters, monster[0]);//�M��Ǫ� -1�Ǫ����s�b
				if (find == -1)
				{
					cout << "error target!!!" << '\n';
					j--;
					continue;
				}
				if (j + 1 == (*actionName).size())//�������̫�ޯ�
				{
					
				}
				else if ((*actionName)[j + 1] == "range")//�d��range
				{
					range = range + (*actionNum)[j + 1];
				}
				if (range == 0)
				{
					range = 1;
				}
				if (abs((*a->getPosition()).x - (*game.map.monsters[find].getPosition()).x) + abs((*a->getPosition()).y - (*game.map.monsters[find].getPosition()).y) > range)//�d�ݩǪ��O�_�b�d��
				{
					cout << "error target!!!" << '\n';
					j--;
					continue;
				}
				if (inSight((*a->getPosition()), (*game.map.monsters[find].getPosition())) == 0)
				{
					cout << "error target!!!" << '\n';
					j--;
					continue;
				}
				action.attack((*game.map.monsters[find].getPosition()), game.map.monsters[find].getShield(), (*actionNum)[j], game.map.monsters[find].getHp(), range, a->getIcon(), monster[0]);//����
				if (*game.map.monsters[find].getHp() <= 0)//�Ǫ����`
				{
					game.map.monsters[find].setMode(0);
					updateMap();
				}
			}
			else if ((*actionName)[j] == "heal")//�v��
			{
				action.heal(a->getHp(), game.characterd.hp[a->getTypeCharacter()], (*actionNum)[j], a->getIcon());
			}
			else if ((*actionName)[j] == "shield")//�@��
			{
				action.sheild(a->getShield(), (*actionNum)[j], a->getIcon());
			}
			else if ((*actionName)[j] == "range")
			{
				continue;
			}
		}
	}
}
int findMonster(vector<Monster>& monster, char a)
{
	for (int i = 0; i < MONSTERNUM; i++)
	{
		if (monster[i].getMode() != 0 && monster[i].getIcon() == a)
		{
			if (monster[i].getMode() != 0)
			{
				return i;
			}
		}
	}
	return -1;
}
void updateMap()
{
	game.map.updateCharacter(&game.characters);//��s�����m
	game.map.updateMonster();//��s�Ǫ���m
	game.map.printMap();//��X�a��
}
float operator-(Point2d& a, Point2d& b)
{
	float c = 0;
	c = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	if (c != (int)c)
	{
		c = (int)c + 1;
	}
	return c;
}
int checkRole(string a)
{
	if (a == "check")//��X������T
	{
		for (int k = 0; k < MONSTERNUM + CHARACTERNUM; k++)
		{
			if (isupper(game.gamerole[k]))
			{
				if (*(game.characters[game.gamerole[k] - 'A'].getHp()) <= 0)
				{
					continue;
				}
				game.characters[game.gamerole[k] - 'A'].check(1);
			}
			else
			{
				if (game.map.monsters[game.gamerole[k] - 'a'].getMode() == 0)
				{
					continue;
				}
				game.map.monsters[game.gamerole[k] - 'a'].check();
			}
		}
		return 1;
	}
	return 0;
}
int standOnDoor(int find)
{
	for (int i = find; i < CHARACTERNUM; i++)
	{
		for (int j = 0; j < DOORNUM; j++)
		{
			if (positionCmp(*game.characters[i].getPosition(), game.map.doorPosition[j]) == 1)
			{
				return j;
			}
		}
	}
	return -1;
}
int noMonster()
{
	for (int i = 0; i < MONSTERNUM; i++)
	{
		if (game.map.monsters[i].getMode() != 0)
		{
			return 0;
		}
	}
	return 1;
}
void reshuffleMonster()
{
	for (int i = 0; i < MONSTERNUM; i++)//�~�P
	{
		Monster *a = &game.map.monsters[i];
		if (a->getMode() != 0)
		{
			MonsterSkill *b = &game.monsterd.allMonsterSkill[a->getTypeMonster()][a->getChooseCard()];
			if (b->getReshuffle() == 'r')
			{
				a->shuffle();
				DEBUG[i] = 0;
			}
		}
	}
}
int characterDie()
{
	for (int i = 0; i < CHARACTERNUM; i++)
	{
		if ((*game.characters[i].getHp()) > 0)
		{
			return 0;
		}
	}
	return 1;
}
int inSight(Point2d& a, Point2d& b)
{
	double m = double(a.y - b.y) / double(a.x - b.x);
	double d = 0;
	double x = a.x;
	double y = a.y;
	if (abs(b.x - a.x) <= 1 && abs(b.y - a.y) <= 1)
	{
		return 1;
	}
	if (b.y - a.y > 0)
	{
		d = 1;
	}
	else if(b.y - a.y < 0)
	{
		d = -1;
	}
	else
	{
		d = 0;
	}
	for (double i = a.y + 0.5; i != b.y + 0.5 + 0.5 * d; i = i + d)
	{
		if (i == a.y + 0.5)
		{
			i = i + 0.5 * d;
		}
		x = (i - 0.5 - a.y) / m + (a.x + 0.5);
		if (x != int(x))
		{
			if (game.map._map[int(i)][int(x)] == MAPWALL)
			{
				return 0;
			}
			else if (game.map._map[int(i - 1)][int(x)] == MAPWALL)
			{
				return 0;
			}
		}
		else
		{
			if (game.map._map[int(i)][int(x)] == MAPWALL)
			{
				return 0;
			}
		}
	}
	if (b.x - a.x > 0)
	{
		d = 1;
	}
	else if (b.x - a.x < 0)
	{
		d = -1;
	}
	else
	{
		d = 0;
	}
	for (double i = a.x + 0.5; i != b.x + 0.5 + 0.5 * d; i = i + d)
	{
		if (i == a.x + 0.5)
		{
			i = i + 0.5 * d;
		}
		y = m * (i - (a.x + 0.5)) + a.y + 0.5;
		if (y != int(y))
		{
			if (game.map._map[int(y)][int(i)] == MAPWALL)
			{
				return 0;
			}
			else if (game.map._map[int(y)][int(i - 1)] == MAPWALL)
			{
				return 0;
			}
		}
		else
		{
			if (game.map._map[int(y)][int(i)] == MAPWALL)
			{
				return 0;
			}
		}
	}
	return 1;
}