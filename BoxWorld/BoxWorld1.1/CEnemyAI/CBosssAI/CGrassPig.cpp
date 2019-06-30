#include "CGrassPig.h"
#include "GameManager/GameManager.h"

CGrassPig::CGrassPig()
{
	this->m_animationName.push_back("GrassPigBackRight");
	this->m_animationName.push_back("GrassPigBackLeft");
	this->m_animationName.push_back("GrassPigFrontLeft");
	this->m_animationName.push_back("GrassPigFrontRight");

	CBossAI::initAnimation();
	
}

void CGrassPig::attack()
{

	Point playerPosition = GameManager::getInstance()->GetPlayerCurrentPosition();

	int systemTime = GetTickCount();

	if (systemTime - this->m_lastSkillTime > this->m_skillTimeInterval) {
		skill();
		this->m_lastSkillTime = systemTime;
	}
	else if (m_skillTime && systemTime - this->m_lastSkillTime > this->m_skillTimeInterval / 3) {
		debuff();
	}
	

	if (calculateDistance(playerPosition, this->m_point) < this->m_attackRange) {
		if (systemTime - this->m_lastAttackTime > this->m_attackIntervalTime) {
			GameManager::getInstance()->ChangePlayerHealth(GameManager::getInstance()->GetPlayerCurrentHealth() - this->m_attack);
			this->m_lastAttackTime = systemTime;
		}
	}
	else {
		CBossAI::move(playerPosition);
	}
}

void CGrassPig::skill()
{
	this->m_skillTime = true;
	this->m_speed = this->m_speedUpRate * this->m_speed;
}

void CGrassPig::debuff() {
	this->m_skillTime = false;
	this->m_speed =  this->m_speed/ this->m_speedUpRate;
}

