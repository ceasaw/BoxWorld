#include"CEnemyAI\CMeleeMonsterAI.h"
#include"ResourceAllocator/ResourceAllocator.h"


CMeleeMonsterAI::CMeleeMonsterAI() {
	
}

CMeleeMonsterAI::CMeleeMonsterAI(int init_x,int init_y):CEnemyAI(init_x,init_y) {
	
	
	
}

void CMeleeMonsterAI::attack()
{
	Point playerPosition = GameManager::getInstance()->GetPlayerCurrentPosition();
	
	//获取玩家位置
	if (calculateDistance(playerPosition, this->m_point) < this->m_attackRange) {
		double systemTime = GetTickCount();
		if (systemTime - this->m_lastAttackTime > this->m_attackIntervalTime) {
			GameManager::getInstance()->ChangePlayerHealth(GameManager::getInstance()->GetPlayerCurrentHealth() - this->m_attack);
			this->m_lastAttackTime = systemTime;
		}
	}
	else {
		move(playerPosition);
	}
}

PicPos* CMeleeMonsterAI::getPicAndPos() {
	PicPos* picPos = new PicPos;


	picPos->coordinate.x = this->m_point.x;
	picPos->coordinate.y = this->m_point.y;

	if (m_state == DIE) {
		Point p = GameManager::getInstance()->GetResource()->GetMeleeMonsterPosMap().at("Skeleton");//todo: type????
		CBitmap* bmp = GameManager::getInstance()->GetResource()->GetMonsterBmp();
		picPos->pic.picture = bmp;
		picPos->pic.maskPos.x = (ENEMY_PIC_NUMBER + (this->m_direction + 2) % 4)*ENEMY_PIC_SIZE_WIDTH;
		picPos->pic.maskPos.y = p.y;
		picPos->pic.spiritPos.x = (this->m_direction + 2) % 4 *ENEMY_PIC_SIZE_WIDTH;
		picPos->pic.spiritPos.y = p.y;

		if (picPos->pic.maskPos.x < -10000 || picPos->pic.maskPos.y < -10000) {
			int i = 1;
		}
	}
	else if (m_state == ATTACK || m_state == PATROL) {

		Point p = GameManager::getInstance()->GetResource()->GetMeleeMonsterPosMap().at(enemyType[this->m_enemyType]);
		CBitmap* bmp = GameManager::getInstance()->GetResource()->GetMonsterBmp();
		picPos->pic.picture = bmp;
		picPos->pic.maskPos.x = (ENEMY_PIC_NUMBER + (this->m_direction+2)%4)*ENEMY_PIC_SIZE_WIDTH;
		picPos->pic.maskPos.y = p.y;
		picPos->pic.spiritPos.x = ((this->m_direction + 2) % 4) *ENEMY_PIC_SIZE_WIDTH;
		picPos->pic.spiritPos.y = p.y;
	}
	return picPos;
}







