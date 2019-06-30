#include"CEnemyAI/CBlockMonsterAI.h"
#include"BasicTools/BasicTools.h"



CBlockMonsterAI::CBlockMonsterAI(Enemy_Attributes bean) :CEnemyAI(bean)
{
	if (bean.type == ENEMY_TYPE::BLOCKMONSTER2) {
		vector<BmpPic*> pictures;
		BmpPic* bmpPic;

		
		CBitmap* bmp = GameManager::getInstance()->GetResource()->GetMonsterBmp();
		Point p;
		p = GameManager::getInstance()->GetResource()->GetBlockMonsterPosMap()["BoxOpen"];
		for (int j = 0; j < 4; j++) {
			bmpPic = new BmpPic;
			bmpPic->picture = bmp;
			bmpPic->maskPos.x = p.x + (j + ENEMY_PIC_NUMBER)*ENEMY_PIC_SIZE_WIDTH;
			bmpPic->maskPos.y = p.y;
			bmpPic->spiritPos.x = p.x + j*ENEMY_PIC_SIZE_WIDTH;
			bmpPic->spiritPos.y = p.y;
			pictures.push_back(bmpPic);
		}

		p = GameManager::getInstance()->GetResource()->GetBlockMonsterPosMap()["BoxClose"];
		for (int j = 0; j < 4; j++) {
			bmpPic = new BmpPic;
			bmpPic->picture = bmp;
			bmpPic->maskPos.x = p.x + (j + ENEMY_PIC_NUMBER)*ENEMY_PIC_SIZE_WIDTH;
			bmpPic->maskPos.y = p.y;
			bmpPic->spiritPos.x = p.x + j * ENEMY_PIC_SIZE_WIDTH;
			bmpPic->spiritPos.y = p.y;
			pictures.push_back(bmpPic);
		}
		
		this->addAnimation("treasureMonster", 70, pictures,false);
	}
}


void CBlockMonsterAI::patrol()
{
	//ÅÐ¶ÏÍæ¼ÒÊÇ·ñ½øÈë¹¥»÷·¶Î§
	Point playerPosition = GameManager::getInstance()->GetPlayerCurrentPosition();
	if (calculateDistance(playerPosition, this->m_point) < this->m_detectionRange) {
		this->m_state = ATTACK;
	}
	return;
}

void CBlockMonsterAI::attack()
{
	Point playerPosition = GameManager::getInstance()->GetPlayerCurrentPosition();
	
	if (calculateDistance(playerPosition, this->m_point) < this->m_attackRange) {
		double systemTime = GetTickCount();
		if (systemTime - this->m_lastAttackTime > this->m_attackIntervalTime) {

			GameManager::getInstance()->ChangePlayerHealth( GameManager::getInstance()->GetPlayerCurrentHealth()-this->m_attack);
			this->m_lastAttackTime = systemTime;
			this->enableAnimation("treasureMonster");
		}
	}
	else {
		this->m_state = EnemyState::PATROL;
	}

}

PicPos* CBlockMonsterAI::getPicAndPos() {
	PicPos* picPos = new PicPos;


	picPos->coordinate.x = this->m_point.x;
	picPos->coordinate.y = this->m_point.y;


	if (this->m_enemyType == ENEMY_TYPE::BLOCKMONSTER2) {
		if (m_state == DIE) {
			Point p = GameManager::getInstance()->GetResource()->GetBlockMonsterPosMap().at("Skeleton");
			CBitmap* bmp = GameManager::getInstance()->GetResource()->GetMonsterBmp();
			picPos->pic.picture = bmp;
			picPos->pic.maskPos.x = (ENEMY_PIC_NUMBER + (this->m_direction + 2) % 4)*ENEMY_PIC_SIZE_WIDTH;
			picPos->pic.maskPos.y = p.y;
			picPos->pic.spiritPos.x = (this->m_direction + 2) % 4 * ENEMY_PIC_SIZE_WIDTH;
			picPos->pic.spiritPos.y = p.y;
		}
		else if (m_state == PATROL) {

			Point p = GameManager::getInstance()->GetResource()->GetBlockMonsterPosMap().at("BoxOpen");
			CBitmap* bmp = GameManager::getInstance()->GetResource()->GetMonsterBmp();
			picPos->pic.picture = bmp;
			picPos->pic.maskPos.x = ENEMY_PIC_NUMBER * ENEMY_PIC_SIZE_WIDTH;
			picPos->pic.maskPos.y = p.y;
			picPos->pic.spiritPos.x = 0 * ENEMY_PIC_SIZE_WIDTH;
			picPos->pic.spiritPos.y = p.y;
		}
		else if (m_state == ATTACK) {
			BmpPic* pic = this->getCBitmap();
			if (pic == nullptr) {
				Point p = GameManager::getInstance()->GetResource()->GetBlockMonsterPosMap().at("BoxOpen");
				CBitmap* bmp = GameManager::getInstance()->GetResource()->GetMonsterBmp();
				picPos->pic.picture = bmp;
				picPos->pic.maskPos.x = ENEMY_PIC_NUMBER * ENEMY_PIC_SIZE_WIDTH;
				picPos->pic.maskPos.y = p.y;
				picPos->pic.spiritPos.x = 0 * ENEMY_PIC_SIZE_WIDTH;
				picPos->pic.spiritPos.y = p.y;
			}
			else {
				picPos->pic.picture = pic->picture;
				picPos->pic.maskPos.x = pic->maskPos.x;
				picPos->pic.maskPos.y = pic->maskPos.y;
				picPos->pic.spiritPos.x = pic->spiritPos.x;
				picPos->pic.spiritPos.y = pic->spiritPos.y;
			}
		}
	}
	else if (this->m_enemyType == ENEMY_TYPE::BLOCKMONSTER1) {

		if (m_state == DIE) {
			Point p = GameManager::getInstance()->GetResource()->GetBlockMonsterPosMap().at("Skeleton");
			CBitmap* bmp = GameManager::getInstance()->GetResource()->GetMonsterBmp();
			picPos->pic.picture = bmp;
			picPos->pic.maskPos.x = (ENEMY_PIC_NUMBER + (this->m_direction + 2) % 4)*ENEMY_PIC_SIZE_WIDTH;
			picPos->pic.maskPos.y = p.y;
			picPos->pic.spiritPos.x = (this->m_direction + 2) % 4 * ENEMY_PIC_SIZE_WIDTH;
			picPos->pic.spiritPos.y = p.y;
		}
		else if (m_state == ATTACK) {

			Point p = GameManager::getInstance()->GetResource()->GetBlockMonsterPosMap().at("Nut");
			CBitmap* bmp = GameManager::getInstance()->GetResource()->GetMonsterBmp();
			picPos->pic.picture = bmp;
			picPos->pic.maskPos.x = (ENEMY_PIC_NUMBER + 1)*ENEMY_PIC_SIZE_WIDTH;
			picPos->pic.maskPos.y = p.y;
			picPos->pic.spiritPos.x = 1 * ENEMY_PIC_SIZE_WIDTH;
			picPos->pic.spiritPos.y = p.y;
		}
		else if (m_state == PATROL) {

			Point p = GameManager::getInstance()->GetResource()->GetBlockMonsterPosMap().at("Nut");
			CBitmap* bmp = GameManager::getInstance()->GetResource()->GetMonsterBmp();
			picPos->pic.picture = bmp;
			picPos->pic.maskPos.x = ENEMY_PIC_NUMBER * ENEMY_PIC_SIZE_WIDTH;
			picPos->pic.maskPos.y = p.y;
			picPos->pic.spiritPos.x = 0 * ENEMY_PIC_SIZE_WIDTH;
			picPos->pic.spiritPos.y = p.y;
		}
	}
	return picPos;
}



