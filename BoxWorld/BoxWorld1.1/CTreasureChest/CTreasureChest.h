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
	void setItem();  //�������������һ�����Ի�Ѫƿ
	void openTreasureChest();  //��������
	int getRadius();  //��ȡ����뾶
	void setRadius(int r);  //���ñ���뾶
	void refreshHeal();
};

#endif 