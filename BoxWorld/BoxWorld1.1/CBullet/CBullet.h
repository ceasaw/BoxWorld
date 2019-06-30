#ifndef _CBULLET_H_
#define _CBULLET_H_

#include <afxwin.h>
#include "CBulletAttribute/CBulletAttribute.h"
#include "BasicTools/BasicTools.h"
#include "ResourceAllocator/ResourceAllocator.h"
#include "GameObject/GameObject.h"

class CBullet: public GameObject
{
private:
	//�ӵ���������
	bool isExist;
	bool isFromPlayer;
	int bulletAttack;
	int flySpeed;
	int bulletRadius;
	Node direction;
	bool isFlying;

	int bulletAttribute;

	//������ÿһ���ӵ�������ʱ��ȥ��ȡ
	static ResourceAllocator* tempAllocator;

private:
	//ʱ���������ӵ���������
	SYSTEMTIME sys;
	int lastTime;
	int curTime;

public:
	CBullet(int bulletAttribute);

public:
	//ʵ�ָ���ķ���
	void setXpos(int posX);
	void setYpos(int posY);
	int getXpos();
	int getYpos();
	void setPoint(int x, int y);
	Point getPoint();
	OBJECT_TYPE getObjectType();
	void setObjectType(OBJECT_TYPE type);

	bool GetIsFromPlayer();
	void SetIsFromPlayer(bool isPlayer);

	void SetExist(bool isExist);
	bool GetExist();

	int GetBulletAttack();
	void SetBulletAttack(int newAttack);

	void SetBulletAttribute(int bulletAttribute);
	int GetBulletAttribute();

	int GetBulletRadius();

	void SetBulletFlySpeed(bool isFromPlayer);

	//�����ӵ��ķ��з���
	void SetDirection(int xMouse, int yMouse);

public:
	void BulletMove();

public:
	//���ø������������ӵ�����ͼλ��
	void SetBulletBmpPoint(bool isFromPlayer);

private:
	//�ڲ������ӵ��ĵ�
	void SetMonsterBulletPoint();
	void SetPlayerBulletPoint();
	
};

#endif // !_CBULLET_H_
