#include "CDataAI\CDataAI.h"
#include <algorithm>

//优先返回右上角的元素
bool OrderSort(GameObject* obj1, GameObject* obj2) 
{
	Point p1 = { obj1->getXpos(), obj1->getYpos()};
	Point p2 = { obj2->getXpos(), obj2->getYpos()};
	//return (p1.y <= p2.y)? false:(p1.x <= p2.x);
	return p1.y < p2.y;
};

CDataAI::CDataAI()
{
	//添加图片的文件名

	//初始化对象
}

void CDataAI::SetPlayer(CPlayer * player)
{
	this->m_Player = player;
}

CPlayer * CDataAI::GetPlayer()
{
	return this->m_Player;
}

void CDataAI::AddBullet(CBullet * tempBullet)
{
	m_Bullets.push_back(tempBullet);
}

void CDataAI::AddChest(CTreasureChest * tempChest)
{
	m_Chests.push_back(tempChest);
}

void CDataAI::AddEnemy(CEnemyAI * tempEnemy)
{
	m_Enemys.push_back(tempEnemy);
}

vector<CTreasureChest*>& CDataAI::GetChests()
{
	return m_Chests;
}

vector<CBullet*>& CDataAI::GetBullets()
{
	return m_Bullets;
}

vector<CEnemyAI*>& CDataAI::GetEnemys()
{
	return m_Enemys;
}

vector<GameObject*>& CDataAI::GetAllGameObjects()
{
	return m_AllGameObjects;
}

vector<WALL*>& CDataAI::GetWalls()
{
	return this->m_Walls;
}

void CDataAI::SortAllGameObjects()
{
	if (m_AllGameObjects.size() > 2)
		std::sort(m_AllGameObjects.begin(), m_AllGameObjects.end(),OrderSort);

	vector<GameObject*> temp = this->m_AllGameObjects;
}