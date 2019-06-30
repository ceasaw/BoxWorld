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
	//子弹基本属性
	bool isExist;
	bool isFromPlayer;
	int bulletAttack;
	int flySpeed;
	int bulletRadius;
	Node direction;
	bool isFlying;

	int bulletAttribute;

	//不想让每一个子弹创建的时候都去获取
	static ResourceAllocator* tempAllocator;

private:
	//时间锁控制子弹飞行速率
	SYSTEMTIME sys;
	int lastTime;
	int curTime;

public:
	CBullet(int bulletAttribute);

public:
	//实现父类的方法
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

	//设置子弹的飞行方向
	void SetDirection(int xMouse, int yMouse);

public:
	void BulletMove();

public:
	//设置根据条件设置子弹的贴图位置
	void SetBulletBmpPoint(bool isFromPlayer);

private:
	//内部设置子弹的点
	void SetMonsterBulletPoint();
	void SetPlayerBulletPoint();
	
};

#endif // !_CBULLET_H_
