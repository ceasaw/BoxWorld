#pragma once
#ifndef _CENEMYAI_H_
#define _CENEMYAI_H_

#include<AnimationBehavior/AnimationBehavior.h>
#include<CBulletAttribute/CBulletAttribute.h>
#include"BasicTools/BasicTools.h"
#include"GameObject/GameObject.h"
//#include"ConstValue.h"
#include<vector>
#include<queue>

using namespace std;

enum EnemyState
{
	PATROL,
	ATTACK,
	DIE
};

static std::map<ENEMY_TYPE, CString>enemyType = {
	{ENEMY_TYPE::MELEEMONSTER1, "Pig"},
	{ENEMY_TYPE::MELEEMONSTER2, "Sheep"},
	{ENEMY_TYPE::MELEEMONSTER3, "Panda"},
	{ENEMY_TYPE::RANGEMONSTER1, "Duck"},
	{ENEMY_TYPE::RANGEMONSTER2, "Rabit"},
	{ENEMY_TYPE::RANGEMONSTER3, "Mushroom"},
	{ENEMY_TYPE::BLOCKMONSTER1, "Nut"} };

enum EnemyType 
{
	MELEE,
	RANGED,
	BLOCK,
	BOSS
};

enum Direction 
{
	BACKRIGHT=0,
	BACKLEFT,
	FRONTLEFT,
	FRONTRIGHT
};

class CEnemyAI :public AnimationBehavior ,public GameObject{
protected:
	Point m_point = { 0,0 };
	Point m_initPoint;//
	Direction m_direction = Direction::FRONTLEFT;
	queue<Point> m_movePoint;//

	int m_attack;//
	int m_attackIntervalTime;//
	double m_lastAttackTime;
	int m_blood;//
	int m_maxBlood;
	int m_experience;//
	int m_speed;//
	double m_lastMoveTime;
	CBulletAttribute m_attribute;//

	int m_attackRange;//
	int m_detectionRange;//
	int m_patrolRange;//
	int m_radius;//

	bool m_exist;//
	int m_dieTime;

	EnemyState m_state;//
	ENEMY_TYPE m_enemyType;//
	vector<CString> m_animationName;
	int m_attributeAnimationChange = 0;

	//CBitmap* m_pics;



public:
	CEnemyAI();
	CEnemyAI(Enemy_Attributes bean);
	CEnemyAI(int init_x, int init_y);
	
	void setAllAttribute(Enemy_Attributes bean);

	int getExperience() { return this->m_experience; }
	void setExperience(int experience) { this->m_experience = experience; }

	int getBlood() { return this->m_blood; }
	void setBlood(int blood) { this->m_maxBlood = blood; this->m_blood = this->m_maxBlood; }

	bool getExist() { return this->m_exist; }

	void setSpeed(int speed) { this->m_speed = speed; }

	void setAttack(int attack) { this->m_attack = attack; }

	void setAttackSpeed(int attackIntervalTime) { this->m_attackIntervalTime = attackIntervalTime; }

	void setAttackRange(int range) { this->m_attackRange = range; }

	void setDetectionRange(int range) { this->m_detectionRange = range; }

	void setPatrolRange(int range) { this->m_patrolRange = range; }

	void setRatioRange(int range) { this->m_radius = range; }

	ENEMY_TYPE getEnemyType() { return this->m_enemyType; }
	void setEnemyType(ENEMY_TYPE enemyType) { this->m_enemyType = enemyType; }

	int getAttributeAnimationNum() { return this->m_attributeAnimationChange; }

	int getEnemyState() { return (int)this->m_state; }



	OBJECT_TYPE getObjectType() { return this->m_Type; }
	void setObjectType(OBJECT_TYPE type) { this->m_Type = type; }
	void setXpos(int posX) { this->xPos = posX; }
	void setYpos(int posY) { this->yPos = posY; }
	int getXpos() { return this->xPos; }
	int getYpos() { return this->yPos; }
	void setPoint(int x, int y) { p = Point{ x, y }; }
	Point getPoint() { return this->p; }

	bool isBoss() {
		if (this->m_enemyType == ENEMY_TYPE::BOSS1 || this->m_enemyType == ENEMY_TYPE::BOSS2 || this->m_enemyType == ENEMY_TYPE::BOSS3)return true;
		else return false;
	}

	bool showHpBar() {
		if (this->m_enemyType == ENEMY_TYPE::BLOCKMONSTER2)return false;
		else return true;
	}
	

	//设置巡逻路径节点
	void setPatrolPoints(vector<Point>points);

	//获取怪物属性
	CBulletAttribute getAttribute() { return this->m_attribute; }

	//设置怪物属性
	void setAttribute(CBulletAttribute attribute) { this->m_attribute = attribute; }

	//获取敌人位置
	Point getPosition() { return m_point; }

	//获取敌人判断范围
	int getRadius() { return this->m_radius; }

	//更新函数，供CMyWnd调用
	virtual void updateEnemy();

	//巡逻
	virtual void patrol();

	//死亡
	virtual void die();

	//攻击
	virtual void attack() = 0;

	//将敌人设为不可见
	virtual void disable();

	//将敌人设为可见
	virtual void enable();

	//受到攻击
	virtual bool beAttacked(int attack);

	//获取血量百分比
	double getPercentage() { return (double)this->m_blood / this->m_maxBlood; }


protected:
	virtual void changeDirection(int destination_x,int destination_y);
	void move(int destination_x, int destination_y);
	void move(Point destination_point);

protected:
	double calculateDistance(Point p1, Point p2);
	double calculateDistance(int x1,int y1,int x2,int y2);
};

#endif