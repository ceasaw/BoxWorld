#pragma once
#include<afxwin.h>
#include"GameObject/GameObject.h"

class WALL: public GameObject {//ǽ����
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
	bool JudgeR_(int xn, int yn, int rn);//��ײ�����жϣ����нӴ��򷵻�true;
};



