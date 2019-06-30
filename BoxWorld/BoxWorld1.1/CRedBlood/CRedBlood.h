#pragma once
#ifndef _CREDBLOOD_H_
#define _CREDBLOOD_H_

#include "CItem\CItem.h"
#include "GameManager\GameManager.h"

class CRedBlood:public CItem {
public:
	CRedBlood();
	void useItem();  //为角色回复血量，回复值为valueBlood
};

#endif 