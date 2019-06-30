#pragma once
#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "CDataAI/CDataAI.h"
#include "CTreasureChest/CTreasureChest.h"
#include "BasicTools/BasicTools.h"
#include "ResourceAllocator/ResourceAllocator.h"
#include <afxwin.h>
#include <mmsystem.h>
#include <dsound.h>
#pragma comment(lib, "WINMM.LIB")

class CMapAI;

/*�����н����Ǹı�exist���Բ�����ʵ�ʵ���ʾ��ʵ�ʵ���ʾ����CMyWnd*/
class GameManager
{
public:
	static GameManager* getInstance();

private:
	GameManager();

private:
	static GameManager* m_Instance;

private:
	//��Ϸ����
	CDataAI* m_DTAI;
	CMapAI* m_map;
	ResourceAllocator* resource;
private:
	//��Ϸ��״̬
	int curLevel;
	int enemyType;
	bool isPlayerDie;
	int enemyShowNum;
	int playerBulletAttribute;

	//��Ϸ��ʼʱ��
	int gameStartTime;
	int curTime;
	bool isBossCreate;
	Point tempPoint;

public:
	//��ȡ/������Ϸ״̬�ĺ���
	void setBossCreate(bool bossCreate);
	int GetPlayerBulletAttribute();

	int GetCurrentLevel();
	int SetCurrentLevel(int levelPlus);

	int GetEnemyShowNum();
	void PlusEnemyShowNum(int num);

	//�ı��ɫ״̬
	void SetPlayerState(bool isDie);
	bool GetPlayerState();

public:
	//��ȡ��Ϸ������
	CDataAI* GetData();
	CMapAI* GetMap();
	void SetMap(CMapAI* tempMap);
	ResourceAllocator* GetResource();

public: //�����������
	LPDIRECTSOUNDBUFFER pDSB_BK, pDSB_ES, pDSB_MC, pDSB_LU;
	LPDIRECTSOUNDBUFFER CreateSecondaryBuffer(LPSTR filename);
	LPDIRECTSOUND pDS;
	HRESULT result;

public:
	//��Ϸ�������

	//����BOSS
	void AddNewBoss(int x, int y);
	void ShowBoss();

	//��ʾ������������
	void AddNewEnemy(int x, int y);

	//��ʾ���������ӵ����������������Ӧλ��,�����ӵ���ʱ���������λ�ü���
	void AddNewBullet(int x, int y, bool isPlayer, int xMouse, int yMouse, int bulletAttribute);

	//��ʾ������������
	void AddNewTreasureChest(int x, int y);

public:
	
	//���ɫ���
	int GetPlayerCurrentHealth();
	void ChangePlayerHealth(int healthChange);
	Point& GetPlayerCurrentPosition();
	void ChangePlayerExperience(int exChange);
	
	//�ı���ҹ�������
	void ChangePlayerAttribute(int attribute);

	//�ж�·�����Ƿ���ǽ����
	bool JudgePointIsInWall(Point judgePoint);

	//�������ж����existΪfalse
	void ReSetAllGameObjects();
};

#endif // !_GAME_MANAGER_H_
