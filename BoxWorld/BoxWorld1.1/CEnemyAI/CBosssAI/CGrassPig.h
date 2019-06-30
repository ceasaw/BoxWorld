#pragma
#ifndef _CGRASS_PIG_H_
#define _CGRASS_PIG_H_

#include"CEnemyAI/CBossAI.h"

class CGrassPig :public CBossAI {
private:
	int m_lastSkillTime;
	int m_skillTimeInterval=5000;
	bool m_skillTime;
	int m_speedUpRate = 3;

public:
	CGrassPig();
	CGrassPig(Enemy_Attributes bean) :CBossAI(bean) {}
	void attack();
	void skill();
	void debuff();


};


#endif // !_CGRASS_PIG_H_
