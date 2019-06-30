#include "CRedBlood\CRedBlood.h"

CRedBlood::CRedBlood()
{
	bloodValue = 3;
}

void CRedBlood::useItem()
{
	//Ϊ��ɫ�ظ�Ѫ��
	GameManager *gm = GameManager::getInstance();
	int blood = gm->GetData()->GetPlayer()->getBlood();
	if(blood <= (60 - bloodValue))
		gm->ChangePlayerHealth(blood + bloodValue);
	else
		gm->ChangePlayerHealth(60);
}