#pragma once
#ifndef _CPLAYER_H_
#define _CPLAYER_H_

#include "AnimationBehavior\AnimationBehavior.h"
#include "GameObject\GameObject.h"
#include <afxwin.h> 

using namespace std;
//class GameObject;

class CPlayer : public AnimationBehavior, public GameObject {
private:
	int radius;
	CBitmap* player;
	int blood;
	int xp;
	bool playerState;
public:
	CPlayer();
	CPlayer(int fx, int fy, CBitmap* bmp);
	PicPos* getPicAndPos();
	void roleMove(int xmove, int ymove);     //更改角色位置
	int getXCoordinate();    //获取角色的x坐标
	int getYCoordinate();    //获取角色的y坐标
	int getBlood();    //获取角色的血量
	void setBlood(int newBlood);  //改变角色的血量，改为newBlood
	CBitmap* getBmp();  //获取角色图片
	void setBmp(CBitmap* bmp);  //设置角色图片
	void upXP(int upEXP);  //增加角色经验值,经验值满10增加两颗血量
	int getRadius();  //获取人物半径
	void setRadius(int r);  //设置人物半径
	bool getPlayerState();
	void setPlayerState(bool state);

	void setXpos(int posX);
	void setYpos(int posY);
	int getXpos();
	int getYpos();
	void setPoint(int x, int y);
	Point getPoint();
	OBJECT_TYPE getObjectType();
	void setObjectType(OBJECT_TYPE type);
};

#endif 