#pragma
#ifndef _CBOSSAI_H_
#define _CBOSSAI_H_

#include"CEnemyAI/CEnemyAI.h"

class CBossAI :public CEnemyAI {


protected:

	void changeDirection(int destination_x, int destination_y);
	
public:
	CBossAI() {}
	CBossAI(Enemy_Attributes bean) :CEnemyAI(bean) {}
	void initAnimation();
	void patrol();
	void die();
	virtual void skill() = 0;
	

	PicPos* getPicAndPos();
};



#endif // !_CBOSSAI_H_
