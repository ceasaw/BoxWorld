#pragma once
#include<afxwin.h>
#include"GameObject/GameObject.h"

class WALL: public GameObject {//墙体类
public:
	void setXpos(int posX);
	void setYpos(int posY);
	int r = 75;

	int getXpos();
	int getYpos();
	void setPoint(int x, int y);
	Point getPoint();

	OBJECT_TYPE getObjectType();
	void setObjectType(OBJECT_TYPE type);

	WALL();
	WALL(int x, int y);
	bool JudgeR_(int xn, int yn, int rn);//碰撞距离判断，若有接触则返回true;
};



