#pragma once
#ifndef _CDATAAI_H_
#define _CDATAAI_H_

#include "ResourceAllocator/ResourceAllocator.h"
#include "CBullet/CBullet.h"
#include "CTreasureChest/CTreasureChest.h"
#include "CPlayer/CPlayer.h"
#include "CEnemyAI/CEnemyAI.h"
#include "CMapAI/Wall.h"

class CDataAI
{
public:
	CDataAI();
private:
	CPlayer* m_Player; 

	vector<CEnemyAI*> m_Enemys;

	vector<CBullet*> m_Bullets;
	vector<CTreasureChest*> m_Chests;
	vector<WALL*> m_Walls;

	vector<GameObject*> m_AllGameObjects;

public:
	void SetPlayer(CPlayer* player);

	CPlayer* GetPlayer();

	void AddBullet(CBullet* tempBullet);
	void AddChest(CTreasureChest* tempChest);
	void AddEnemy(CEnemyAI* tempEnemy);

	vector<CTreasureChest*>& GetChests();
	vector<CBullet*>& GetBullets();
	vector<CEnemyAI*>& GetEnemys();
	vector<GameObject*>& GetAllGameObjects();
	vector<WALL*>& GetWalls();

	void SortAllGameObjects();

};

#endif // !_CDATAAI_H


