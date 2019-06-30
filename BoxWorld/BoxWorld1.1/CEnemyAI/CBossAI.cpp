#include "CBossAI.h"
#include "GameManager/GameManager.h"


void CBossAI::initAnimation()
{
	Point p;
	BmpPic* pic;

	for (int i = 0; i < 4; i++) {
		vector<BmpPic*> pics;
		p.x = GameManager::getInstance()->GetResource()->GetBossPosMap()[this->m_animationName[i]].x;
		p.y = GameManager::getInstance()->GetResource()->GetBossPosMap()[this->m_animationName[i]].y;

		for (int j = 0; j < 4; j++) {
			pic = new BmpPic;
			pic->picture = GameManager::getInstance()->GetResource()->GetBossBmp();

			pic->maskPos.x = p.x + (j + ENEMY_PIC_NUMBER) * ENEMY_PIC_SIZE_WIDTH;
			pic->maskPos.y = p.y;
			pic->spiritPos.x = p.x + j * ENEMY_PIC_SIZE_WIDTH;
			pic->spiritPos.y = p.y;

			pics.push_back(pic);
		}
		this->addAnimation(this->m_animationName[i], ENEMY_ANIMATION_INTERVAL_TIME, pics,true);
	}
}



void CBossAI::patrol()
{
	Point playerPosition = GameManager::getInstance()->GetPlayerCurrentPosition();
	if (calculateDistance(playerPosition, this->m_point) < this->m_detectionRange) {
		this->m_state = ATTACK;
	}
	return;
}

void CBossAI::die()
{
	double systemTime = GetTickCount();
	if (systemTime - m_dieTime > ENEMY_DIE_TIME_INTERVAL) {
		GameManager::getInstance()->SetCurrentLevel(1);
		GameManager::getInstance()->setBossCreate(false);
		GameManager::getInstance()->ChangePlayerExperience(this->getExperience());
		this->disable();
	}

}

void CBossAI::changeDirection(int destination_x, int destination_y)
{
	CEnemyAI::changeDirection(destination_x, destination_y);
	this->enableAnimation(this->m_animationName[this->m_direction]);
}

PicPos* CBossAI::getPicAndPos()
{

	PicPos* picpos = new PicPos;
	BmpPic* bmp = nullptr;


	if (m_state == DIE) {
		Point p = GameManager::getInstance()->GetResource()->GetBlockMonsterPosMap().at("Skeleton");
		CBitmap* bmp = GameManager::getInstance()->GetResource()->GetMonsterBmp();
		picpos->pic.picture = bmp;
		picpos->pic.maskPos.x = (ENEMY_PIC_NUMBER + (this->m_direction + 2) % 4)*ENEMY_PIC_SIZE_WIDTH;
		picpos->pic.maskPos.y = p.y;
		picpos->pic.spiritPos.x = (this->m_direction + 2) % 4 * ENEMY_PIC_SIZE_WIDTH;
		picpos->pic.spiritPos.y = p.y;
	}
	else if (m_state == PATROL) {
		Animation* animation = this->getAnimation(this->m_animationName[0]);
		bmp = animation->pictures[0];

		picpos->pic.picture = bmp->picture;
		picpos->pic.maskPos.x = bmp->maskPos.x;
		picpos->pic.maskPos.y = bmp->maskPos.y;
		picpos->pic.spiritPos.x = bmp->spiritPos.x;
		picpos->pic.spiritPos.y = bmp->spiritPos.y;
		
	}
	else if (m_state == ATTACK) {
		BmpPic* pic = this->getCBitmap();
		if (pic == nullptr) {
			Animation* animation = this->getAnimation(this->m_animationName[0]);
			bmp = animation->pictures[0];

			picpos->pic.picture = bmp->picture;
			picpos->pic.maskPos.x = bmp->maskPos.x;
			picpos->pic.maskPos.y = bmp->maskPos.y;
			picpos->pic.spiritPos.x = bmp->spiritPos.x;
			picpos->pic.spiritPos.y = bmp->spiritPos.y;
		}
		else {
			bmp = pic;

			picpos->pic.picture = bmp->picture;
			picpos->pic.maskPos.x = bmp->maskPos.x;
			picpos->pic.maskPos.y = bmp->maskPos.y;
			picpos->pic.spiritPos.x = bmp->spiritPos.x;
			picpos->pic.spiritPos.y = bmp->spiritPos.y;
		}
	}

	
	picpos->coordinate.x = this->getPosition().x;
	picpos->coordinate.y = this->getPosition().y;

	return picpos;
}

