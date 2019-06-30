#pragma once
#ifndef _RESOURCE_ALLOCATOR_H_
#define _RESOURCE_ALLOCATOR_H_

#include <afxwin.h>
#include <map>
#include <cstring>
#include "BasicTools/BasicTools.h"

class ResourceAllocator
{
public:
	ResourceAllocator();
private:

	CBitmap* monstersBmp;
	CBitmap* bossBmp;
	CBitmap* gunBmp;
	CBitmap* stoneBmp;
	CBitmap* mapBmp;
	CBitmap* bulletBmp;
	CBitmap* treasureBmp;
	CBitmap* shadowBmp;
	CBitmap* monsterBulletBmp;
	
	//��ʱû������
	CBitmap* bossBloodBmp;
	CBitmap* heartBmp;
	CBitmap* monsterBloodBmp;


private:

	//������
	std::map<CString, Point> gun;

	//������Դ
	std::map<CString, Point> boss;
	std::map<CString, Point> meleeMonster;
	std::map<CString, Point> rangeMonster;
	std::map<CString, Point> blockMonster;

	//��ҽ�ɫ
	std::map<CString, Point> character;

	//��ͼ��Դ
	std::map<CString, Point> stone;
	std::map<CString, Point> treasure;

	//ս��UI
	std::map<CString, Point> bullet;
	std::map<CString, Point> monsterBullet;
	std::map<CString, Point> shadow;


private:
	void InitMaps();

public:
	CBitmap* GetMonsterBmp();
	CBitmap* GetBossBmp();
	CBitmap* GetGunBmp();
	CBitmap* GetStoneBmp();
	CBitmap* GetMapBmp();
	CBitmap* GetBulletBmp();
	CBitmap* GetMonsterBulletBmp();
	CBitmap* GetTreasuretBmp();
	CBitmap* GetShadowBmp();

	//��ʱ�޷�����
	CBitmap* GetHeartBmp();
	CBitmap* GetMonsterBloodBmp();

	CBitmap * GetBossBloodBmp();

public:
	std::map<CString, Point>& GetBossPosMap();
	std::map<CString, Point>& GetMeleeMonsterPosMap();
	std::map<CString, Point>& GetRangeMonsterPosMap();
	std::map<CString, Point>& GetBlockMonsterPosMap();
	std::map<CString, Point>& GetCharacterPosMap();
	std::map<CString, Point>& GetGunPosMap();
	std::map<CString, Point>& GetStonePosMap();
	std::map<CString, Point>& GetBulletPosMap();
	std::map<CString, Point>& GetMonsterBulletPosMap();
	std::map<CString, Point>& GetShadowPosMap();
};

#endif // !_RESOURCE_ALLOCATOR_H_
