#include<CEnemyAI/CEnemyAI.h>
#include"GameManager/GameManager.h"
#include "CEnemyAI.h"

CEnemyAI::CEnemyAI() {
	this->setObjectType(OBJECT_TYPE::CENEMY);
}

CEnemyAI::CEnemyAI(Enemy_Attributes bean):CEnemyAI(bean.xPos,bean.yPos)
{
	this->setPatrolPoints(bean.road);
	this->setAttack(bean.attack);
	this->setAttackRange(bean.attackRange);
	this->setAttackSpeed(bean.attackInterval);
	this->setAttribute(bean.attribute);
	this->setBlood(bean.blood);
	this->setDetectionRange(bean.detectionRange);
	this->setEnemyType(bean.type);
	this->setExperience(bean.experience);
	this->setPatrolRange(bean.patrolRange);
	this->setRatioRange(bean.collisionRadius);
	this->setSpeed(bean.speed);
	this->m_exist = bean.isExist;

	this->m_state = EnemyState::PATROL;
	
}

CEnemyAI::CEnemyAI(int init_x, int init_y) {
	this->m_initPoint.x = init_x;
	this->m_initPoint.y = init_y;
	this->m_point.x = this->m_initPoint.x;
	this->m_point.y = this->m_initPoint.y;
	setXpos(this->m_point.x);
	setYpos(this->m_point.y);
	this->setObjectType(OBJECT_TYPE::CENEMY);
}

void CEnemyAI::setAllAttribute(Enemy_Attributes bean)
{
	this->m_point.x = bean.xPos;
	this->m_point.y = bean.yPos;
	this->setPatrolPoints(bean.road);
	this->setAttack(bean.attack);
	this->setAttackRange(bean.attackRange);
	this->setAttackSpeed(bean.attackInterval);
	this->setAttribute(bean.attribute);
	this->setBlood(bean.blood);
	this->setDetectionRange(bean.detectionRange);
	this->setEnemyType(bean.type);
	this->setExperience(bean.experience);
	this->setPatrolRange(bean.patrolRange);
	this->setRatioRange(bean.collisionRadius);
	this->setSpeed(bean.speed);
	this->m_exist = bean.isExist;

	this->m_state = EnemyState::PATROL;

	this->m_initPoint.x = bean.xPos;
	this->m_initPoint.y = bean.yPos;
	this->m_point.x = this->m_initPoint.x;
	this->m_point.y = this->m_initPoint.y;
	setXpos(this->m_point.x);
	setYpos(this->m_point.y);
	this->setObjectType(OBJECT_TYPE::CENEMY);
}

void CEnemyAI::setPatrolPoints(vector<Point> points)
{
	while (!m_movePoint.empty()) m_movePoint.pop();
	for (int i = 0; i < points.size(); i++) {
		m_movePoint.push(points[i]);
	}
}

void CEnemyAI::updateEnemy()
{
	//如果不可见则直接返回
	if (!this->m_exist)return;
	//更新敌人动画
	this->updateAnimation();
	//可见则根据状态做出具体行为
	switch (this->m_state)
	{
	case PATROL:
		this->patrol();
		break;
	case ATTACK:
		this->attack();
		break;
	case DIE:
		this->die();
		break;
	default:
		break;
	}
	
	this->m_attributeAnimationChange = (this->m_attributeAnimationChange++) % 18;
}

void CEnemyAI::patrol()
{
	if (m_movePoint.empty())return;

	Point dPoint = this->m_movePoint.front();

	if(calculateDistance(dPoint,this->m_point)>= ENEMY_MOVE_DEVIATION)
	{
		move(dPoint);
	}
	else {
		m_movePoint.pop();
		m_movePoint.push(dPoint);
	}

	
	Point playerPosition = GameManager::getInstance()->GetPlayerCurrentPosition();
	//在一定距离内就攻击
	if (calculateDistance(playerPosition, this->m_point) < this->m_detectionRange) {
		this->m_state = ATTACK;
	}
	
}

void CEnemyAI::die()
{
	double systemTime = GetTickCount();
	if (systemTime - m_dieTime > ENEMY_DIE_TIME_INTERVAL) {
		GameManager::getInstance()->ChangePlayerExperience(this->getExperience());
		GameManager::getInstance()->PlusEnemyShowNum(-1);
		this->disable();
	}
	
}

void CEnemyAI::enable() {
	this->m_exist = true;
}

bool CEnemyAI::beAttacked(int attack) {
	this->m_blood -= attack;
	if (this->m_blood <= 0) {
		this->m_dieTime = GetTickCount();
		this->m_state = DIE;
		return true;
	}
	return false;
}

void CEnemyAI::disable() {
	this->m_exist = false;
}

void CEnemyAI::changeDirection(int destination_x, int destination_y)
{
	if (destination_x > this->m_point.x && destination_y <= this->m_point.y) {
		this->m_direction = BACKRIGHT;
	}
	else if (destination_x <= this->m_point.x && destination_y < this->m_point.y) {
		this->m_direction = BACKLEFT;
	}
	else if (destination_x < this->m_point.x && destination_y >= this->m_point.y) {
		this->m_direction = FRONTLEFT;
	}
	else if (destination_x >= this->m_point.x && destination_y > this->m_point.y) {
		this->m_direction = FRONTRIGHT;
	}
}

void CEnemyAI::move(int destination_x, int destination_y)
{
	Point destinationPoint = { destination_x,destination_y };
	this->move(destinationPoint);
}

void CEnemyAI::move(Point destination_point)
{

	//改变方向
	this->changeDirection(destination_point.x, destination_point.y);

	//改变坐标
	double systemTime = GetTickCount();


	if (systemTime - m_lastMoveTime< 33) {
		return;
	}

	double length = calculateDistance(destination_point, m_point);
	//int dx = m_speed * (systemTime - m_lastMoveTime)*0.01*(destination_point.x - m_point.x) / length;
	//int dy = m_speed * (systemTime - m_lastMoveTime)*0.01*(destination_point.y - m_point.y) / length;

	int dx = m_speed* 33 / 1000 *(destination_point.x - m_point.x) / length;
	int dy = m_speed* 33 / 1000 *(destination_point.y - m_point.y) / length;
	Point nextPoint = { this->m_point.x + dx ,this->m_point.y + dy };
	if (!GameManager::getInstance()->JudgePointIsInWall(nextPoint)) {
		this->m_point = nextPoint;
		setXpos(this->m_point.x);
		setYpos(this->m_point.y);
	}
	this->m_lastMoveTime = systemTime;
}

double CEnemyAI::calculateDistance(Point p1, Point p2)
{
	return pow(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2),0.5);
}

double CEnemyAI::calculateDistance(int x1, int y1, int x2, int y2)
{
	Point p1 = { x1,y1 };
	Point p2 = { x2,y2 };
	return this->calculateDistance(p1, p2);
}

