#include "CBulletAttribute\CBulletAttribute.h"
#include "GameManager\GameManager.h"

CBulletAttribute::CBulletAttribute()
{
	attr = metal;
}

CBulletAttribute::CBulletAttribute(int gattr)
{
	attr = gattr;
}

int CBulletAttribute::getBulletAttribute()
{
	return attr;
}

void CBulletAttribute::useItem()
{
	//更改子弹属性
	GameManager *gm = GameManager::getInstance();
	gm->ChangePlayerAttribute(attr);
}