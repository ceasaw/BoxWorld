#include "CBullet.h"
#include <time.h>
#include <cmath>
#include "GameManager/GameManager.h"

ResourceAllocator* CBullet::tempAllocator = nullptr;

CBullet::CBullet(int bulletAttribute)
{
	setObjectType(OBJECT_TYPE::CBULLET);
	SetBulletAttribute(bulletAttribute);
	this->xPos = 0;
	this->yPos = 0;
	this->isExist = false;
	this->isFromPlayer = true;
	this->bulletAttack = 3;
	this->flySpeed = 500;
	this->bulletRadius = 12;
	this->lastTime = 0;
	this->curTime = 0;
	this->isFlying = false;

	if (tempAllocator == nullptr)
		tempAllocator = GameManager::getInstance()->GetResource();
}

void CBullet::setXpos(int posX)
{
	this->xPos = posX;
}

void CBullet::setYpos(int posY)
{
	this->yPos = posY;
}

int CBullet::getXpos()
{
	return this->xPos;
}

int CBullet::getYpos()
{
	return this->yPos;
}

void CBullet::setPoint(int x, int y)
{
	p = Point{x, y};
}

Point CBullet::getPoint()
{
	SetBulletBmpPoint(this->GetIsFromPlayer());
	return this->p;
}

OBJECT_TYPE CBullet::getObjectType()
{
	return this->m_Type;
}

void CBullet::setObjectType(OBJECT_TYPE type)
{
	this->m_Type = type;
}

bool CBullet::GetIsFromPlayer()
{
	return this->isFromPlayer;
}

void CBullet::SetIsFromPlayer(bool isPlayer)
{
	this->isFromPlayer = isPlayer;
}

void CBullet::SetExist(bool isExist)
{
	this->isExist = isExist;

	if (!isExist)
		isFlying = false;
}

bool CBullet::GetExist()
{
	return this->isExist;
}

int CBullet::GetBulletAttack()
{
	return bulletAttack;
}

void CBullet::SetBulletAttack(int newAttack)
{
	this->bulletAttack = newAttack;
}

int CBullet::GetBulletRadius()
{
	return bulletRadius;
}

void CBullet::SetBulletFlySpeed(bool isFromPlayer)
{
	if (isFromPlayer)
		this->flySpeed = 550;
	else
		this->flySpeed = 350;
}

void CBullet::SetDirection(int xMouse, int yMouse)
{
	float xChange = (float)xMouse - (float)xPos;
	float yChange = (float)yMouse - (float)yPos;
	float ratio = (xChange) / (yChange);

	if(xChange <= 0)
		direction.x = -fabs(ratio);
	else
		direction.x = fabs(ratio);

	direction.y = -1;
	if (yChange >= 0)
		direction.y = 1;

	//将方向比化1
	float quadraticSum = direction.x * direction.x + 1;
	direction.x = direction.x / sqrt(quadraticSum);
	direction.y = direction.y / sqrt(quadraticSum);

	//根据方向重新设置子弹发出的位置
	setXpos(xPos + direction.x * 60);
	setYpos(yPos + direction.y * 60);
	
	
}

void CBullet::SetBulletAttribute(int bulletAttribute)
{
	this->bulletAttribute = bulletAttribute;
}

int CBullet::GetBulletAttribute()
{
	return this->bulletAttribute;
}

void CBullet::BulletMove()
{
	GetLocalTime(&sys);
	curTime = sys.wSecond * 1000 + sys.wMilliseconds;

	//第一次飞行初始化
	if (!isFlying)
	{
		isFlying = true;
		lastTime = curTime;
	}

	//系统时间差1s/10 动50
	if (curTime - lastTime >= 33 || curTime - lastTime < 0)
	{
		xPos += int(flySpeed / 10 * direction.x);
		yPos += int(flySpeed / 10 * direction.y);
		lastTime = curTime;
	}
}

void CBullet::SetBulletBmpPoint(bool isFromPlayer)
{
	if (isFromPlayer)
		SetPlayerBulletPoint();
	else
		SetMonsterBulletPoint();
}

void CBullet::SetMonsterBulletPoint()
{
	if (this->GetBulletAttribute() == (int)MONSTER_TYPE::DUCK)
		p = tempAllocator->GetMonsterBulletPosMap()["DuckBullet"];	
	else if (this->GetBulletAttribute() == (int)MONSTER_TYPE::RABIT)
		p = tempAllocator->GetMonsterBulletPosMap()["RabitBullet"];
	else if (this->GetBulletAttribute() == (int)MONSTER_TYPE::MUSHROOM)
		p = tempAllocator->GetMonsterBulletPosMap()["MushroomBullet"];
	else if (this->GetBulletAttribute() == (int)MONSTER_TYPE::LAVA)
		p = tempAllocator->GetMonsterBulletPosMap()["LavaBullet"];
	else if(this->GetBulletAttribute() == (int)MONSTER_TYPE::DEMON)
		p = tempAllocator->GetMonsterBulletPosMap()["DemonBullet"];
}

void CBullet::SetPlayerBulletPoint()
{
	if (this->GetBulletAttribute() == (int)PLAYER_TYPE::NON_ELEMENTAL)
		p = tempAllocator->GetBulletPosMap()["NonElemental"];
	else if (this->GetBulletAttribute() == (int)PLAYER_TYPE::METAL)
		p = tempAllocator->GetBulletPosMap()["Metal"];
	else if (this->GetBulletAttribute() == (int)PLAYER_TYPE::WOOD)
		p = tempAllocator->GetBulletPosMap()["Wood"];
	else if (this->GetBulletAttribute() == (int)PLAYER_TYPE::WATER)
		p = tempAllocator->GetBulletPosMap()["Water"];
	else if (this->GetBulletAttribute() == (int)PLAYER_TYPE::FIRE)
		p = tempAllocator->GetBulletPosMap()["Fire"];
	else if (this->GetBulletAttribute() == (int)PLAYER_TYPE::EARTH)
		p = tempAllocator->GetBulletPosMap()["Earth"];
}
