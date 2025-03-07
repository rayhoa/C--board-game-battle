#include"Header.h"
#include"Gloomhaven.h"
#include"Monster.h"
#include<fstream>
#include<iostream>
#include<sstream>
#include<cctype>
#include<stdlib.h>
#include<cmath>
#include"Function.h"
using namespace std;
void Gloomhaven::loadSourceFile(string cf, string mf)
{
	string input;
	if (!loadCharacterFile(cf))//載入角色檔案
	{
		cout << "Can't open character file." << '\n';
		return ;
	}
	if (!loadMonsterFile(mf))//載入怪物檔案
	{
		cout << "Can't open monster file." << '\n';
		return ;
	}
	return ;
}
int Gloomhaven::loadCharacterFile(string cF)
{
	fstream cFile;
	int kind = 0, hp = 0, card = 0, cardNum;
	string information;
	cFile.open(cF, ios::in);
	if (!cFile.is_open())
	{
		return 0;
	}
	cFile >> kind;
	characterd.allCharacterSkill = new vector<CharacterSkill>[kind];//設置角色種類
	for (int i = 0; i < kind; i++)//讀取每種角色資料
	{
		cFile >> information;
		cFile >> hp;
		cFile >> card;
		characterd.addCharacter(information,hp,card);
		cFile >> cardNum;
		for (int j = 0; j < cardNum; j++)
		{
			CharacterSkill aCharacSkill;
			int no = 0, cAgility = 0;
			cFile >> no;
			cFile >> cAgility;
			aCharacSkill.setAgilicy(cAgility);
			cFile >> information;
			while (information != "-")
			{
				aCharacSkill.setUpSkill(information);
				int skillNum = 0;
				cFile >> skillNum;
				aCharacSkill.setUpSkillNum(skillNum);
				cFile >> information;
			}
			getline(cFile, information);
			stringstream sInform;
			string skill;
			int skillNum = 0;
			sInform << information;
			while (sInform >> skill)
			{
				sInform >> skillNum;
				aCharacSkill.setDownSkill(skill);
				aCharacSkill.setDownSkillNum(skillNum);
			}
			characterd.allCharacterSkill[i].push_back(aCharacSkill);
		}
	}
	return 1;
}
int Gloomhaven::loadMonsterFile(string mF)
{
	fstream mFile;
	int kind = 0, normalHp = 0, normalAttack = 0, normalRange = 0, eliteHp = 0, eliteAttack = 0, eliteRange = 0, cardnum = 0;
	string information;
	mFile.open(mF, ios::in);
	if (!mFile.is_open())
	{
		return 0;
	}
	mFile >> kind;
	monsterd.allMonsterSkill = new vector<MonsterSkill>[kind];//設置怪物種類
	for (int i = 0; i < kind; i++)//讀取每種怪物資料
	{
		mFile >> information;
		mFile >> normalHp;
		mFile >> normalAttack;
		mFile >> normalRange;
		mFile >> eliteHp;
		mFile >> eliteAttack;
		mFile >> eliteRange;
		monsterd.addMonster(information, normalHp, normalAttack, normalRange, eliteHp, eliteAttack, eliteRange);
		for (int j = 0; j < 6; j++)
		{
			MonsterSkill aMonsterSkill;
			int no = 0, magility = 0;
			mFile >> information;
			mFile >> no;
			mFile >> magility;
			aMonsterSkill.setAgility(magility);
			mFile >> information;
			while (information != "d" && information != "r")
			{
				aMonsterSkill.setSkill(information);
				string skillNum;
				mFile >> skillNum;
				aMonsterSkill.setSkillNum(skillNum);
				mFile >> information;
			}
			aMonsterSkill.setReshuffle(information[0]);
			monsterd.allMonsterSkill[i].push_back(aMonsterSkill);
		}
	}
	return 1;
}
int Gloomhaven::loadMapFile(string mapF)
{
	fstream mapFile;
	string information;
	char mapNum;
	int Mrow = 0, mColumn = 0, x = 0, y = 0, monCount = 0, conditionA = 0, conditionB = 0, conditionC = 0;
	mapFile.open(mapF, ios::in);
	if (!mapFile.is_open())
	{
		return 0;
	}
	mapFile >> Mrow;
	mapFile >> mColumn;
	map.row = Mrow;
	map.column = mColumn;
	map._map = new vector<char>[Mrow];
	map.room = new vector<int>[Mrow];
	for (int i = 0; i < Mrow; i++)
	{
		for (int j = 0; j < mColumn; j++)
		{
			mapFile >> mapNum;
			map._map[i].push_back(mapNum);
			map.room[i].push_back(0);
			if (mapNum == MAPDOOR)
			{
				Point2d a(j, i);
				map.doorPosition.push_back(a);
			}
		}
	}
	DOORNUM = map.doorPosition.size();//設置門數量
	mapFile.get();
	getline(mapFile, information);
	stringstream str;
	str << information;
	while (str >> x >> y)
	{
		Point2d ap(x,y);
		map.startPoint.push_back(ap);
	}
	mapFile >> monCount;
	MONSTERNUM = monCount;
	for (int i = 0; i < monCount; i++)
	{
		Monster mon;
		mapFile >> information;
		mon.setName(information);
		mapFile >> x;
		mapFile >> y;
		mon.setPosition(x, y);
		mon.setIcon('a' + i);
		mapFile >> conditionA;
		mapFile >> conditionB;
		mapFile >> conditionC;
		mon.setCondition(conditionA, conditionB, conditionC);
		map.monsters.push_back(mon);
	}
	map.doorOpen = new int[DOORNUM];
	for (int i = 0; i < DOORNUM; i++)//設置門為全部關閉
	{
		map.doorOpen[i] = 0;//0為關閉
	}
	return 1;
}
int Gloomhaven::getInformation()
{
	string input, name, mapF;
	int no = 0, card = 0;
	cout << "Enter play to start playing:" << '\n';
	cin >> input;
	if (input == "play")//輸入play開始遊玩
	{
		cout << "Enter the quantity of characters" << '\n';
		cin >> CHARACTERNUM;//輸入角色數量
		cout << "Enter the name of characters and the represented number of cards(example:name 1 2 3 4 5):" << '\n';
		for (int i = 0; i < CHARACTERNUM; i++)
		{
			Character character;
			cin >> name;
			character.setName(name);
			character.setIcon('A' + i);
			for (int characterKind = 0; characterKind < characterd.name.size(); characterKind++)//設置地圖內角色資料
			{
				if (name == characterd.name[characterKind])
				{
					no = characterKind;
					character.setHp(characterd.hp[characterKind]);
					character.setTypeCharacter(characterKind);
					break;
				}
			}
			for (int cardCount = 0; cardCount < characterd.holdCard[no]; cardCount++)//讀取角色的卡牌
			{
				cin >> card;
				character.addCard(card);
			}
			characters.push_back(character);
		}
		cout << "Enter the name of map file:" << '\n';//選擇地圖檔案
		cin >> mapF;
		if (!loadMapFile(mapF))//讀取地圖檔案
		{
			cout << "Can't open map file." << '\n';
			return 1;
		}
		int msize = map.monsters.size();
		for (int i = 0; i < msize; i++)//設置地圖內怪物資料
		{
			int size = monsterd.name.size();
			for (int j = 0; j < size; j++)
			{
				if (map.monsters[i].getName() == monsterd.name[j])
				{
					map.monsters[i].setTypeMonster(j);
					map.monsters[i].setMode(map.monsters[i].getCondition(CHARACTERNUM - 2));
					int skillSize = monsterd.allMonsterSkill[map.monsters[i].getTypeMonster()].size();
					for (int k = 0; k < skillSize; k++)
					{
						map.monsters[i].addCard(k);
					}
					if (map.monsters[i].getMode() == 1)
					{
						map.monsters[i].setHp(monsterd.normalHp[map.monsters[i].getTypeMonster()]);
						map.monsters[i].setAttack(monsterd.normalAttack[map.monsters[i].getTypeMonster()]);
						map.monsters[i].setRange(monsterd.normalRange[map.monsters[i].getTypeMonster()]);
					}
					else if (map.monsters[i].getMode() == 2)
					{
						map.monsters[i].setHp(monsterd.eliteHp[map.monsters[i].getTypeMonster()]);
						map.monsters[i].setAttack(monsterd.eliteAttack[map.monsters[i].getTypeMonster()]);
						map.monsters[i].setRange(monsterd.eliteRange[map.monsters[i].getTypeMonster()]);
					}
				}
			}
		}
		for (int i = 0; i < MONSTERNUM; i++)//將所有怪物模式設置為0
		{
			map.monsters[i].setMode(0);
		}
	}
	else if (input == "exit")//使用者輸入exit結束遊戲
	{
		return 1;
	}
	return 0;
}
void Gloomhaven::choosePosition()
{
	string move;
	int characterSize = characters.size(), mx = 0, my = 0,startPointsize = map.startPoint.size();
	for (int i = 0; i < characterSize; i++)//選擇每隻角色啟示位置
	{
		cout << "Choose a position of the characters:" << '\n';
		cin >> move;
		int length = move.size(), x = map.startPoint[map.startPoint.size() - 1].x, y = map.startPoint[map.startPoint.size() - 1].y;
		for (int j = 0; j < length; j++)
		{
			switch (move[j])
			{
				case 'a':
					mx = x - 1;
					my = y;
					break;
				case 's':
					mx = x;
					my = y + 1;
					break;
				case 'w':
					mx = x;
					my = y - 1;
					break;
				case 'd':
					mx = x + 1;
					my = y;
					break;
				case 'e':
					mx = x;
					my = y;
					break;
				default:
					mx = x;
					my = y;
					break;
			}
			if (map._map[my][mx] != MAPWALL && map._map[my][mx] != MAPFLOOR)
			{
				x = mx;
				y = my;
			}
			if (move[j] == 'e')//輸入e時，角色位置為*位置
			{
				break;
			}
		}
		if (map._map[y][x] != MAPCHOOSEPLACE && map._map[y][x] != MAPNOWPOSITION)
		{
			cout << "Error" << '\n';
			i--;
			continue;
		}
		characters[i].setPosition(x, y);
		map._map[y][x] = characters[i].getIcon();
		if (i < characters.size() - 1)
		{
			map.printMap();//顯示地圖
		}
	}
	for (int i = 0; i < startPointsize; i++)//將沒選到的位置全設為地板
	{
		if (map._map[map.startPoint[i].y][map.startPoint[i].x] == MAPCHOOSEPLACE || map._map[map.startPoint[i].y][map.startPoint[i].x] == MAPNOWPOSITION)
		{
			map._map[map.startPoint[i].y][map.startPoint[i].x] = MAPFLOOR;
		}
	}
	map.printMap();
}
void Gloomhaven::characterPreparing()
{
	for (int i = 0; i < CHARACTERNUM; i++)//每隻角色準備階段
	{
		string input, characterIcon ,inputA;
		int numA = 0,searchNum = 0,numB = 0;
		stringstream str;
		if (*(characters[i].getHp()) <= 0)//角色已死亡
		{
			cout << characters[i].getIcon() << " is killed!! " << '\n';
			continue;
		}
		cout << "Choose skill cards or -1:" << '\n';
		getline(cin, input);
		str << input;
		str >> characterIcon;
		searchNum = searchCharacter(characters, characterIcon[0]);//尋找角色
		if (searchNum == -1)//角色錯誤
		{
			cout << "Error" << '\n';
			i--;
			continue;
		}
		if (*(characters[searchNum].getHp()) <= 0)//選擇角色已死亡
		{
			cout << characters[searchNum].getIcon() << "is killed" << '\n';
			i--;
			continue;
		}
		if (!(str >> numA))
		{
			str.clear();
			str >> inputA;
			i--;
			if (inputA != "check")
			{
				cout << "Error" << '\n';
				continue;
			}
			characters[searchNum].check(0);//輸出check
			continue;
		}
		if (numA == -1)//長休
		{
			characters[searchNum].setChooseCard(-1, 0);
			continue;
		}
		if (!(str >> numB))
		{
			cout << "Error" << '\n';
			i--;
			continue;
		}
		if (!characters[searchNum].setChooseCard(numA, numB))//設置輸入卡牌
		{
			cout << "Error" << '\n';
			i--;
			continue;
		}
	}
}
void Gloomhaven::monsterPreparing()
{
	int size = map.monsters.size();
	for (int i = 0; i < size; i++)//快物抽卡
	{
		if (map.monsters[i].getMode() != 0)
		{
			if (DEBUGMODE == 1)//debugmode為1，按順序出牌
			{
				map.monsters[i].setChooseCard(DEBUG[i]);
				DEBUG[i] = DEBUG[i] + 1;
			}
			else if (DEBUGMODE == 0)
			{
				map.monsters[i].setChooseCard((*(map.monsters[i].getCard()))[rand() % map.monsters[i].getCard()->size()]);
			}
		}
		else
		{
			map.monsters[i].setChooseCard(-1);
		}
	}
	gamerole = new char[size + CHARACTERNUM];
	for (int i = 0; i < size + CHARACTERNUM; i++)
	{
		if (i < size)
		{
			gamerole[i] = 'a' + i;
		}
		else
		{
			gamerole[i] = 'A' + i - size;
		}
	}
	for (int i = 0; i < size + CHARACTERNUM - 1; i++)//使用氣泡排序法進行排序
	{
		for (int j = 0; j < size + CHARACTERNUM - 1; j++)
		{
			int agilityA = 0, agilityB = 0;
			if (isupper(gamerole[j]))
			{
				agilityA = characters[gamerole[j] - 'A'].getAgility(1);
			}
			else
			{
				agilityA = map.monsters[gamerole[j] - 'a'].getAgility();
			}
			if (isupper(gamerole[j + 1]))
			{
				agilityB = characters[gamerole[j + 1] - 'A'].getAgility(1);
			}
			else
			{
				agilityB = map.monsters[gamerole[j + 1] - 'a'].getAgility();
			}
			if (agilityA > agilityB)
			{
				charSwap(gamerole, j);
			}
			else if (agilityA == agilityB && agilityA != -1)
			{
				if (isupper(gamerole[i]) && isupper(gamerole[i + 1]))
				{
					if (characters[gamerole[i] - 'A'].getAgility(2) > characters[gamerole[i + 1] - 'A'].getAgility(2))
					{
						charSwap(gamerole, j);
						continue;
					}
				}
				if (gamerole[i] > gamerole[i + 1])
				{
					charSwap(gamerole, j);
				}
			}
		}
	}
	for (int i = 0; i < size + CHARACTERNUM; i++)//輸出排序結果
	{
		if (isupper(gamerole[i]))
		{
			Character *a = &characters[gamerole[i] - 'A'];
			if (*(a->getHp()) <= 0)
			{
				continue;
			}
			cout << gamerole[i] << " " << a->getAgility(1) << " ";
			for (int j = 0; j < 2; j++)
			{
				cout << (*a->getChooseCard())[j] << " ";
				if ((*a->getChooseCard())[0] == -1)
				{
					break;
				}
			}
		}
		else
		{
			Monster *a = &map.monsters[gamerole[i] - 'a'];
			if (a->getAgility() == -1)
			{
				continue;
			}
			int skillSize = monsterd.allMonsterSkill[a->getTypeMonster()][a->getChooseCard()].getSkill().size();
			cout << a->getName() << " " << map.monsters[gamerole[i] - 'a'].getAgility() << " ";
			for (int j = 0; j < skillSize; j++)
			{
				cout << monsterd.allMonsterSkill[a->getTypeMonster()][a->getChooseCard()].getSkill()[j] << " ";
				cout << monsterd.allMonsterSkill[a->getTypeMonster()][a->getChooseCard()].getSkillNum()[j] << " ";
			}
		}
		cout << '\n';
	}
}
void Gloomhaven::actionStage()
{
	int turnEnd = -1;
	for (int i = 0; i < MONSTERNUM + CHARACTERNUM; i++)//每隻怪物和角色動作
	{
		if (isupper(gamerole[i]))//角色
		{
			Character *a = &characters[gamerole[i] - 'A'];
			if (*a->getHp() < 1)
			{
				cout << a->getIcon() << " is killed!! " << '\n';
				continue;
			}
			CharacterData *b = &characterd;
			if (turnEnd != i)//只在第一次進入i時才顯示
			{
				cout << a->getIcon() << "'s turn: card" << ' ';
				turnEnd = i;
			}
			if ((*a->getChooseCard())[0] == -1)//角色長休
			{
				Action action;
				char inputCard;
				cout << "-1" << '\n';
				cout << "Enter a card which you want to throw away:" << '\n';
				cin >> inputCard;
				if (!a->deleteAbandonCard(inputCard - '0'))
				{
					cout << "Error" << '\n';
					i--;
					continue;
				}
				action.heal(a->getHp(), b->hp[a->getTypeCharacter()], 2, a->getIcon());
				cout << "remove card: " << inputCard << '\n';
			}
			else//動作
			{
				string inputAction;
				int chooseFirstCard = 0,upDown = 0;
				cout << (*a->getChooseCard())[0] << " " << (*a->getChooseCard())[1] << '\n';
				a->deleteCard((*a->getChooseCard())[0]);
				a->deleteCard((*a->getChooseCard())[1]);
				sort((*a->getAbandonCard()).begin(), (*a->getAbandonCard()).end());
				for (int j = 0; j < 1; j++)
				{
					cout << "Choose skill:" << '\n';
					cin >> inputAction;
					if (checkRole(inputAction))
					{
						j--;
						continue;
					}
					chooseFirstCard = findChooseCard((*a->getChooseCard()), inputAction[0] - '0');//尋找卡
					if (chooseFirstCard == -1)//卡片是否存在
					{
						cout << "try again" << '\n';
						j--;
						continue;
					}
					if (inputAction[1] != 'u' && inputAction[1] != 'd')//輸入是否正確
					{
						cout << "try again" << '\n';
						j--;
						continue;
					}
				}
				/*
				如果選擇u，則updown=1
				如果選擇d，則updown=0
				*/
				upDown = abs(inputAction[1] - 'u') / ('u' - 'd');
				characterAction(characterd, a, map.monsters, upDown, chooseFirstCard);//動作
			}
		}
		else//怪物動作
		{
			Monster *a = &map.monsters[gamerole[i] - 'a'];
			if (a->getMode() == 0)//跳過mode=0
			{
				continue;
			}
			MonsterSkill *actionSkill = &monsterd.allMonsterSkill[a->getTypeMonster()][a->getChooseCard()];
			Action action;
			for (int j = 0; j < actionSkill->getSkill().size(); j++)//執行skill
			{
				if (actionSkill->getSkill()[j] == "move")//移動
				{
					game.map._map[(*a->getPosition()).y][(*a->getPosition()).x] = MAPFLOOR;
					action.move(a->getPosition(), actionSkill->getSkillNum()[j], (*a->getPosition()), 0, 1);
					updateMap();
				}
				else if (actionSkill->getSkill()[j] == "attack")//攻擊
				{
					int range = 0, find = 0, aDamage = 0;
					stringstream str;
					if (j + 1 == actionSkill->getSkill().size())
					{

					}
					else if (actionSkill->getSkill()[j + 1] == "range")
					{
						str << actionSkill->getSkillNum()[j + 1];
						str >> aDamage;
						range = range + aDamage;
					}
					range = range + a->getRange();
					if (range == 0)
					{
						range = 1;
					}
					for (find = 0; find < MONSTERNUM + CHARACTERNUM; find++)//是否在範圍內
					{
						if (isupper(gamerole[find]))
						{
							Character *b = &characters[gamerole[find] - 'A'];
							if (*b->getHp() > 0)
							{
								if (abs((*a->getPosition()).x - (*b->getPosition()).x) + abs((*a->getPosition()).y - (*b->getPosition()).y) <= range)
								{
									if (inSight((*a->getPosition()), (*b->getPosition())) == 0)
									{
										continue;
									}
									cout << a->getIcon() << " lock " << b->getIcon() << " in distance " << *a->getPosition() - *b->getPosition() << '\n';
									str << actionSkill->getSkillNum()[j];
									str >> aDamage;
									aDamage = aDamage + a->getAttack();
									action.attack(*b->getPosition(), b->getShield(), aDamage, b->getHp(), range, a->getIcon(), b->getIcon());
									if (*b->getHp() <= 0)
									{
										updateMap();
									}
									break;
								}
							}
						}
					}
					if (find >= MONSTERNUM + CHARACTERNUM)
					{
						cout << "no one lock" << '\n';
					}
				}
				else if (actionSkill->getSkill()[j] == "heal")//治癒
				{
					int maxHp = 0, aheal = 0;
					stringstream str;
					if (a->getMode() == 1)
					{
						maxHp = monsterd.normalHp[a->getTypeMonster()];
					}
					else
					{
						maxHp = monsterd.eliteHp[a->getTypeMonster()];
					}
					str << actionSkill->getSkillNum()[j];
					str >> aheal;
					action.heal(a->getHp(), maxHp, aheal, a->getIcon());
				}
				else if (actionSkill->getSkill()[j] == "shield")//護盾
				{
					int ashield = 0;
					stringstream str;
					str << actionSkill->getSkillNum()[j];
					str >> ashield;
					action.sheild(a->getShield(), ashield, a->getIcon());
				}
				else if (actionSkill->getSkill()[j] == "range")
				{
					continue;
				}
				if (DEBUGMODE == 1)
				{

				}
				else if (DEBUGMODE == 0)
				{
					cout << "輸入任意字元繼續....." << '\n';
					getchar();
				}
			}
		}
	}
}
int Gloomhaven::endRound()
{
	reshuffleMonster();
	for (int i = 0; i < MONSTERNUM + CHARACTERNUM; i++)//重製shield
	{
		if (isupper(gamerole[i]))
		{
			if ((*characters[gamerole[i] - 'A'].getHp()) <= 0)
			{
				continue;
			}
			characters[gamerole[i] - 'A'].setShield(0);
		}
		else
		{
			if (map.monsters[gamerole[i] - 'a'].getMode() == 0)
			{
				continue;
			}
			map.monsters[gamerole[i] - 'a'].setShield(0);
		}
	}
	int find;
	find = 0;
	for (int i = 0; i < CHARACTERNUM; i++)
	{
		find = standOnDoor(find);
		if (find != -1 && noMonster() == 1)//是否開門
		{
			game.map.doorOpen[find] = 1;
			game.map.openDoor(game.map.doorPosition[find]);
			updateMap();
		}
		else
		{
			break;
		}
	}
	int allOpen = 0;
	for (int i = 0; i < DOORNUM; i++)//所有門是否都開啟
	{
		if (game.map.doorOpen[i] != 1)
		{
			allOpen = 1;
		}
	}
	if (allOpen == 0 && noMonster() == 1)//角色獲勝
	{
		cout << "character win~" << '\n';
		int gameBreak = initializeInput();
		DEBUG = new int[MONSTERNUM];
		for (int i = 0; i < MONSTERNUM; i++)
		{
			DEBUG[i] = 0;
		}
		return gameBreak;
	}
	if (characterDie())//怪物獲勝
	{
		cout << "monster win~" << '\n';
		int gameBreak = initializeInput();
		DEBUG = new int[MONSTERNUM];
		for (int i = 0; i < MONSTERNUM; i++)
		{
			DEBUG[i] = 0;
		}
		return gameBreak;
	}
	for (int i = 0; i < CHARACTERNUM; i++)
	{
		if ((*characters[i].getCard()).size() < 2 && (*characters[i].getAbandonCard()).size() < 2 || (*characters[i].getCard()).size() < 1 && (*characters[i].getAbandonCard()).size() < 3)
		{
			characters[i].setHp(0);
			cout << characters[i].getIcon() << "is dead" << '\n';
		}
	}
	return 0;
}