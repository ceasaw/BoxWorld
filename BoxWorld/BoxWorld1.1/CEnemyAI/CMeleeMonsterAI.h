#pragma once
#ifndef _CMONSTERAI_H_
#define _CMONSTERAI_H_

#include"CEnemyAI\CEnemyAI.h"
#include"GameManager/GameManager.h"



class CMeleeMonsterAI :public CEnemyAI {
	
public:
	CMeleeMonsterAI();
	CMeleeMonsterAI(Enemy_Attributes bean) :CEnemyAI(bean) {}
	CMeleeMonsterAI(int init_x,int init_y);

	void attack();

	PicPos* getPicAndPos();
};





#endif 