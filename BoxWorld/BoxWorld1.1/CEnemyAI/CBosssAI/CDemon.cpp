#include "CEnemyAI/CBosssAI/CDemon.h"
#include "GameManager/GameManager.h"
#define PI acos(-1)

CDemon::CDemon()
{
	this->m_animationName.push_back("DemonBackRight");
	this->m_animationName.push_back("DemonBackLeft");
	this->m_animationName.push_back("DemonFrontLeft");
	this->m_animationName.push_back("DemonFrontRight");

	CBossAI::initAnimation();
}



void CDemon::attack()
{
	Point playerPosition = GameManager::getInstance()->GetPlayerCurrentPosition();

	int systemTime = GetTickCount();

	if (calculateDistance(playerPosition, this->m_point) < this->m_attackRange) {
		if (systemTime - this->m_lastAttackTime > this->m_attackIntervalTime) {
			changeDirection(playerPosition.x, playerPosition.y);
			skill();
			this->m_lastAttackTime = systemTime;
		}
	}
	else {
		move(playerPosition);
	}
}

void CDemon::skill()
{

	for (int i = 0; i < this->m_bulletNumToShoot; i++) {
		Point p;
		double angleTick = 2 * PI / this->m_bulletNumToShoot;
		p.y = this->m_point.y + cos(angleTick*i) * 100;
		p.x = this->m_point.x + sin(angleTick*i) * 100;
		
		GameManager::getInstance()->AddNewBullet(this->m_point.x, this->m_point.y, false, p.x,p.y, (int)this->m_enemyType);
	}
	//·¢ÉäÒ»È¦×Óµ¯
}

