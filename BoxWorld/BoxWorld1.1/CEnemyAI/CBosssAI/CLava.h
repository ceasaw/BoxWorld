#pragma
#ifndef _CLAVA_H_
#define _CLAVA_H_

#include"CEnemyAI/CBossAI.h"

class CLava :public CBossAI {
private:
	int m_bulletNumToShoot = 10;
	double m_castSkillTime = 0;
	double m_skillInterval = 2000;
	int m_bulletHasShoot = 0;
	
public:
	CLava();

	void attack();
	void skill();

};

#endif // !_CDEMON_H_
