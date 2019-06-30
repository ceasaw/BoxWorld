#pragma
#ifndef _CDEMON_H_
#define _CDEMON_H_

#include"CEnemyAI/CBossAI.h"

class CDemon :public CBossAI {
private:
	int m_bulletNumToShoot = 36;

public:
	CDemon();

	void attack();
	void skill();

	
};

#endif // !_CDEMON_H_
