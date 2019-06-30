#include "CTreasureChest/CTreasureChest.h"
#include "CBulletAttribute/CBulletAttribute.h"
#include "CRedBlood/CRedBlood.h"
#include <ctime>

CTreasureChest::CTreasureChest()
{
	xPos = 4000;
	yPos = 3000;
	radius = 65;
	exist = false;
	heal = 0;
}


void CTreasureChest::setItem()
{
	//随机设置一个宝箱内的物品，可设置的物品含有：子弹的五种属性、血瓶，
	//然后将此宝箱的exist设置为TRUE
	heal = 0;

	srand((unsigned)time(NULL));
	int temp = rand() % 6;
	switch (temp) {
	case metal:
		item = new CBulletAttribute(metal);
		break;
	case wood:
		item = new CBulletAttribute(wood);
		break;
	case water:
		item = new CBulletAttribute(water);
		break;
	case fire:
		item = new CBulletAttribute(fire);
		break;
	case earth:
		item = new CBulletAttribute(earth);
		break;
	default:
		item = new CRedBlood;
	}
	exist = true;
}

PicPos* CTreasureChest::getPicAndPos()
{
	return nullptr;
}

void CTreasureChest::openTreasureChest()
{
	//打开宝箱后调用对应的方法，然后将此宝箱的exist设置为false
	item->useItem();
	exist = false;
}

bool CTreasureChest::getExist()
{
	return exist;
}

void CTreasureChest::setExist(bool ex)
{
	exist = ex;
}

int CTreasureChest::getX()
{
	return xPos;
}

int CTreasureChest::getY()
{
	return yPos;
}

void CTreasureChest::setX(int fx)
{
	xPos = fx;
}

void CTreasureChest::setY(int fy)
{
	yPos = fy;
}

int CTreasureChest::getRadius()
{
	return radius;
}

void CTreasureChest::setRadius(int r)
{
	radius = r;
}

void CTreasureChest::refreshHeal()
{
	heal += 1;
	if (300 == heal)
	{
		heal = 0;
		exist = false;
	}
}


