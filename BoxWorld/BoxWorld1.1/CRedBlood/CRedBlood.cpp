#include "CRedBlood\CRedBlood.h"

CRedBlood::CRedBlood()
{
	bloodValue = 3;
}

void CRedBlood::useItem()
{
	//为角色回复血量
	GameManager *gm = GameManager::getInstance();
	int blood = gm->GetData()->GetPlayer()->getBlood();
	if(blood <= (60 - bloodValue))
		gm->ChangePlayerHealth(blood + bloodValue);
	else
		gm->ChangePlayerHealth(60);
}