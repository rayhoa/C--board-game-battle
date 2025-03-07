#pragma once
#include"point.h"
#include<string>
#include"Action.h"
#include"Header.h"
#include<cmath>
int initializeInput();//初始化遊戲
int positionCmp(Point2d a, Point2d b);//座標比較
int positionCmp(Point2d a, Point2d b, int c);//座標比較範圍
int searchCharacter(vector<Character>& character, char a);//尋找角色
void charSwap(char *role,int a);//字元互換
int findChooseCard(vector<int>& chooseCard, int a);//在選擇卡牌中尋找
void characterAction(CharacterData& characterd,Character *a,vector<Monster>& monsters,int& upDown,int& choosFirstCard);//角色技能動作
int findMonster(vector<Monster>& monster, char a);//怪物尋找
void updateMap();//地圖更新
float operator-(Point2d& a, Point2d& b); //a和b之間的距離
int checkRole(string a);//輸出相關資訊
int standOnDoor(int find);//判斷是否有角色站在門上
int noMonster();//判斷是否有怪物
void reshuffleMonster();//重新洗牌
int characterDie();//判斷是否角色死亡
int inSight(Point2d& a, Point2d& b);//視野計算