#include "CEnemyAI/CRangeMonsterAI.h"
#include "GameManager/GameManager.h"

void CRangeMonsterAI::attack()
{
	Point playerPosition = GameManager::getInstance()->GetPlayerCurrentPosition();
	changeDirection(playerPosition.x,playerPosition.y);

	//获取玩家位置
	if (calculateDistance(playerPosition, this->m_point) < this->m_attackRange) {
		double systemTime = GetTickCount();
		if (systemTime - this->m_lastAttackTime > this->m_attackIntervalTime) {
			GameManager::getInstance()->AddNewBullet(this->m_point.x, this->m_point.y, false, playerPosition.x, playerPosition.y,(int) this->m_enemyType);
			this->m_lastAttackTime = systemTime;
			
		}
	}
	else {
		move(playerPosition);
	}

}

PicPos* CRangeMonsterAI::getPicAndPos() {
	PicPos* picPos = new PicPos;


	picPos->coordinate.x = this->m_point.x;
	picPos->coordinate.y = this->m_point.y;

	if (m_state == DIE) {
		Point p = GameManager::getInstance()->GetResource()->GetRangeMonsterPosMap().at("Skeleton");//todo: type????
		CBitmap* bmp = GameManager::getInstance()->GetResource()->GetMonsterBmp();
		picPos->pic.picture = bmp;
		picPos->pic.maskPos.x = (ENEMY_PIC_NUMBER + (this->m_direction + 2) % 4)*ENEMY_PIC_SIZE_WIDTH;
		picPos->pic.maskPos.y = p.y;
		picPos->pic.spiritPos.x = (this->m_direction + 2) % 4 *ENEMY_PIC_SIZE_WIDTH;
		picPos->pic.spiritPos.y = p.y;
	}
	else if (m_state == ATTACK || m_state == PATROL) {

		Point p = GameManager::getInstance()->GetResource()->GetRangeMonsterPosMap().at(enemyType[this->m_enemyType]);
		CBitmap* bmp = GameManager::getInstance()->GetResource()->GetMonsterBmp();
		picPos->pic.picture = bmp;
		picPos->pic.maskPos.x = (ENEMY_PIC_NUMBER + (this->m_direction+2)%4)*ENEMY_PIC_SIZE_WIDTH;
		picPos->pic.maskPos.y = p.y;
		picPos->pic.spiritPos.x = (this->m_direction + 2) % 4 *ENEMY_PIC_SIZE_WIDTH;
		picPos->pic.spiritPos.y = p.y;
	}
	return picPos;
}

