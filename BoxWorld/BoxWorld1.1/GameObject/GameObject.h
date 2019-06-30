#pragma once
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "BasicTools/BasicTools.h"

class GameObject
{
public:
	GameObject() {};

protected:
	int xPos;
	int yPos;
	Point p;
	OBJECT_TYPE m_Type;

public:
	virtual void setXpos(int posX) = 0;
	virtual void setYpos(int posY) = 0;

	virtual int getXpos() = 0;
	virtual int getYpos() = 0;

	virtual void setPoint(int x, int y) = 0;
	virtual Point getPoint() = 0;

	virtual OBJECT_TYPE getObjectType() = 0;
	virtual void setObjectType(OBJECT_TYPE type) = 0;
};

#endif // !_GAMEOBJECT_H_

