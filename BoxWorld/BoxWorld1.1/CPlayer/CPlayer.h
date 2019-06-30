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
	void roleMove(int xmove, int ymove);     //���Ľ�ɫλ��
	int getXCoordinate();    //��ȡ��ɫ��x����
	int getYCoordinate();    //��ȡ��ɫ��y����
	int getBlood();    //��ȡ��ɫ��Ѫ��
	void setBlood(int newBlood);  //�ı��ɫ��Ѫ������ΪnewBlood
	CBitmap* getBmp();  //��ȡ��ɫͼƬ
	void setBmp(CBitmap* bmp);  //���ý�ɫͼƬ
	void upXP(int upEXP);  //���ӽ�ɫ����ֵ,����ֵ��10��������Ѫ��
	int getRadius();  //��ȡ����뾶
	void setRadius(int r);  //��������뾶
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