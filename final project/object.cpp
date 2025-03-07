#include"object.h"
void Object::setName(string a)
{
	name = a;
}
void Object::setPosition(Point2d a)
{
	position.x = a.x;
	position.y = a.y;
}
void Object::setPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}
void Object::setIcon(char a)
{
	icon = a;
}
void Object::setHp(int a)
{
	hp = a;
}
string Object::getName()
{
	return name;
}
Point2d* Object::getPosition()
{
	return &position;
}
char Object::getIcon()
{
	return icon;
}
int* Object::getHp()
{
	return &hp;
}
void Object::setShield(int a)
{
	shield = a;
}
int* Object::getShield()
{
	return &shield;
}
void Object::addCard(int a)
{
	card.push_back(a);
}
bool Object::deleteCard(int a)
{
	int find = 0;
	for (int i = 0; i < card.size(); i++)//§R°£¥d¤ù
	{
		if (card[i] == a)
		{
			card.erase(card.begin() + i);
			find = 1;
		}
	}
	if (find == 0)
	{
		return false;
	}
	abandonCard->push_back(a);
	return true;
}
vector<int>* Object::getCard()
{
	return &card;
}
vector<int>* Object::getAbandonCard()
{
	return abandonCard;
}