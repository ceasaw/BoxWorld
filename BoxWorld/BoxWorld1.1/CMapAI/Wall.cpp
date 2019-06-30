#include<math.h>
#include<time.h>
#include"Wall.h"
#include<afxwin.h>
#include "GameManager/GameManager.h"

WALL::WALL() {
	setObjectType(OBJECT_TYPE::CWALL);
}

WALL::WALL(int x, int y)
{
	setObjectType(OBJECT_TYPE::CWALL);
	this->xPos = x;
	this->yPos = y;
	if (rand() % 2)
		p = GameManager::getInstance()->GetResource()->GetStonePosMap()["HighStone"];
	else
		p = GameManager::getInstance()->GetResource()->GetStonePosMap()["ShortStone"];
	this->setPoint(p.x, p.y);
}

bool WALL::JudgeR_(int xn, int yn, int rn)
{
	float d = sqrt(xn * xn + yn * yn) - sqrt(this->xPos * this->xPos + this->yPos * this->yPos);
	if (d < rn + this -> r) {
		return true;
	}
	else {
		return false;
	}
}

void WALL::setXpos(int posX) {
	this->xPos = posX;
}
void WALL::setYpos(int posY) {
	this->yPos = posY;
}

int WALL::getXpos() {
	return this->xPos;
}
int WALL::getYpos() {
	return this->yPos;
}

void WALL::setPoint(int x, int y) {
	this->p.x = x;
	this->p.y = y;
}
Point WALL::getPoint() {
	return p;
}

OBJECT_TYPE WALL::getObjectType() {
	return this->m_Type;
}
void WALL::setObjectType(OBJECT_TYPE type) {
	this->m_Type = type;
}