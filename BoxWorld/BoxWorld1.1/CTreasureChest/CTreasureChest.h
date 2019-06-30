#pragma once
#ifndef _CTREASURECHEST_H_
#define _CTREASURECHEST_H_

#include "AnimationBehavior\AnimationBehavior.h"
#include "CItem\CItem.h"
#include "GameObject\GameObject.h"

using namespace std;

class CTreasureChest : public AnimationBehavior{
private:
	int xPos, yPos;
	CItem *item;
	bool exist;
	int radius;
	int heal;
public:
	CTreasureChest();
	PicPos* getPicAndPos();
	int getX();
	int getY();
	bool getExist();
	void setExist(bool ex);
	void setX(int fx);
	void setY(int fy);
	void setItem();  //给宝箱随机设置一个属性或血瓶
	void openTreasureChest();  //开启宝箱
	int getRadius();  //获取宝箱半径
	void setRadius(int r);  //设置宝箱半径
	void refreshHeal();
};

#endif 