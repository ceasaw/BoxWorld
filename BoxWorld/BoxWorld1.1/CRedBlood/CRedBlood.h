#pragma once
#ifndef _CREDBLOOD_H_
#define _CREDBLOOD_H_

#include "CItem\CItem.h"
#include "GameManager\GameManager.h"

class CRedBlood:public CItem {
public:
	CRedBlood();
	void useItem();  //Ϊ��ɫ�ظ�Ѫ�����ظ�ֵΪvalueBlood
};

#endif 