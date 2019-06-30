#include "CEnemyAI/CBosssAI/CLava.h"
#include "GameManager/GameManager.h"

CLava::CLava()
{
	this->m_animationName.push_back("LavaBackRight");
	this->m_animationName.push_back("LavaBackLeft");
	this->m_animationName.push_back("LavaFrontLeft");
	this->m_animationName.push_back("LavaFrontRight");

	CBossAI::initAnimation();
}

void CLava::attack()
{
	Point playerPosition = GameManager::getInstance()->GetPlayerCurrentPosition();
	
	

	if (calculateDistance(playerPosition, this->m_point) < this->m_attackRange) {
		changeDirection(playerPosition.x, playerPosition.y);
		skill();
	}
	else {
		move(playerPosition);
	}

	
}

void CLava::skill() {
	Point playerPosition = GameManager::getInstance()->GetPlayerCurrentPosition();
	int systemTime = GetTickCount();
	if (this->m_bulletHasShoot < this->m_bulletNumToShoot) {
		GameManager::getInstance()->AddNewBullet(this->m_point.x, this->m_point.y, false, playerPosition.x, playerPosition.y, (int)this->m_enemyType);
		this->m_bulletHasShoot++;
	}
	else {
		if (systemTime - this->m_castSkillTime > this->m_skillInterval) {
			this->m_bulletHasShoot=0;
			this->m_castSkillTime = systemTime;
		}
	}
}