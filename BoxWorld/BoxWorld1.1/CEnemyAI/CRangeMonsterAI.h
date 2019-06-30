#pragma
#ifndef _CRANGE_MONSTERAI_H_
#define _CRANGE_MONSTERAI_H_

#include"CEnemyAI/CEnemyAI.h"
#include"CBullet/CBullet.h"


class CRangeMonsterAI :public CEnemyAI {
public:
	CRangeMonsterAI(Enemy_Attributes bean) :CEnemyAI(bean) {}


	void attack();

	PicPos* getPicAndPos();
};


#endif // !_CRANGE_MONSTERAI_H_
