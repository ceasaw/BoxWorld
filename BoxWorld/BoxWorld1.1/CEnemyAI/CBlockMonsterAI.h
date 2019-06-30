#pragma
#ifndef _CBLOCK_MONSTERAI_H_
#define _CBLOCK_MONSTERAI_H_

#include"CEnemyAI/CEnemyAI.h"
#include"GameManager/GameManager.h"

class CBlockMonsterAI :public CEnemyAI {
public:
	CBlockMonsterAI(Enemy_Attributes bean);

protected:
	void patrol();
	void attack();
	

	PicPos* getPicAndPos();
};

#endif // !_CBLOCK_MONSTERAI_H_
