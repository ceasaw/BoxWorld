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

/*本类中仅仅是改变exist属性不进行实际的显示，实际的显示交给CMyWnd*/
class GameManager
{
public:
	static GameManager* getInstance();

private:
	GameManager();

private:
	static GameManager* m_Instance;

private:
	//游戏数据
	CDataAI* m_DTAI;
	CMapAI* m_map;
	ResourceAllocator* resource;
private:
	//游戏内状态
	int curLevel;
	int enemyType;
	bool isPlayerDie;
	int enemyShowNum;
	int playerBulletAttribute;

	//游戏开始时间
	int gameStartTime;
	int curTime;
	bool isBossCreate;
	Point tempPoint;

public:
	//获取/更改游戏状态的函数
	void setBossCreate(bool bossCreate);
	int GetPlayerBulletAttribute();

	int GetCurrentLevel();
	int SetCurrentLevel(int levelPlus);

	int GetEnemyShowNum();
	void PlusEnemyShowNum(int num);

	//改变角色状态
	void SetPlayerState(bool isDie);
	bool GetPlayerState();

public:
	//获取游戏内数据
	CDataAI* GetData();
	CMapAI* GetMap();
	void SetMap(CMapAI* tempMap);
	ResourceAllocator* GetResource();

public: //播放声音组件
	LPDIRECTSOUNDBUFFER pDSB_BK, pDSB_ES, pDSB_MC, pDSB_LU;
	LPDIRECTSOUNDBUFFER CreateSecondaryBuffer(LPSTR filename);
	LPDIRECTSOUND pDS;
	HRESULT result;

public:
	//游戏对象添加

	//创建BOSS
	void AddNewBoss(int x, int y);
	void ShowBoss();

	//显示（创建）敌人
	void AddNewEnemy(int x, int y);

	//显示（创建）子弹并设置在人物的相应位置,创建子弹的时候给定鼠标的位置即可
	void AddNewBullet(int x, int y, bool isPlayer, int xMouse, int yMouse, int bulletAttribute);

	//显示（创建）宝箱
	void AddNewTreasureChest(int x, int y);

public:
	
	//与角色相关
	int GetPlayerCurrentHealth();
	void ChangePlayerHealth(int healthChange);
	Point& GetPlayerCurrentPosition();
	void ChangePlayerExperience(int exChange);
	
	//改变玩家攻击属性
	void ChangePlayerAttribute(int attribute);

	//判断路径点是否在墙体内
	bool JudgePointIsInWall(Point judgePoint);

	//重置所有对象的exist为false
	void ReSetAllGameObjects();
};

#endif // !_GAME_MANAGER_H_
