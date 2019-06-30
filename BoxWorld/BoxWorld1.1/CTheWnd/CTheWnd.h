#pragma once
#ifndef _CTHEWND_H_
#define _CTHEWND_H_

#include <afxwin.h>
#include "GameManager\GameManager.h"
#include "CMapAI\CMapAI.h"
#include "CDataAI\CDataAI.h"
#include "CPlayer\CPlayer.h"
#include "CBullet\CBullet.h"
#include "ResourceAllocator\ResourceAllocator.h"

enum { HOMEPAGE, STARTGAME, HELP, WIN, LOSE };

class CTheWnd : public CFrameWnd {
	
private:
	CDC *mdc, *mdcBuffer;
	CMapAI *mapAI;
	GameManager *gm;
	ResourceAllocator* resAll;
	CDataAI* dataAI;
	CRect rect;
	int time, bultime,sortTime;
	int lastTime;
	int curTime;
	int xSrc, ySrc;
	int gameState;
	int gameNum;
	CBitmap *map, *role, *bmpBuffer, *stone, *home, *help, *heart, *mBlood, *gun, *rBullet, *mBullet, *shadow, *treaChest, *monBlood, *bossBlood, *win, *lose, *back;
	CPlayer *player;
	bool shoot;
	bool hack;
	SYSTEMTIME sys;
	CPoint butDown;
	CEnemyAI* boss = nullptr;

	//敌人的最大数量和刷新间隔
	int maxEnemyNum = 75;
	int enemyRefreshInterval = 13;


public:


	CTheWnd() {
		Create(NULL, "BoxWorld");
		//MoveWindow(0, 0, 1920, 1080);
		SetWindowLong(m_hWnd, GWL_STYLE, WS_OVERLAPPED);
		SetWindowLong(m_hWnd, GWL_EXSTYLE, WS_EX_LTRREADING);
		SetWindowPos(&wndTopMost, 0, 0, GetSystemMetrics(SM_CXSCREEN) - 1, GetSystemMetrics(SM_CYSCREEN), 0);
		CClientDC dc(this);
		gm = GameManager::getInstance();
		gm->result = DirectSoundCreate(NULL, &gm->pDS, NULL);
		if (gm->result != DS_OK) {
			MessageBox("DirectSound对象创建失败！");
		}
		gm->result = gm->pDS->SetCooperativeLevel(m_hWnd, DSSCL_PRIORITY);
		if (gm->result != DS_OK) {
			MessageBox("设定协作等级失败");
		}

		gm->pDSB_BK = gm->CreateSecondaryBuffer((LPSTR)"background.wav");
		gm->pDSB_MC = gm->CreateSecondaryBuffer((LPSTR)"buttonclick.wav");
		gm->pDSB_ES = gm->CreateSecondaryBuffer((LPSTR)"bullet2.wav");
		gm->pDSB_LU = gm->CreateSecondaryBuffer((LPSTR)"levelup.wav");

		mdc = new CDC;
		mdc->CreateCompatibleDC(&dc);
		GetClientRect(&rect);
		mdcBuffer = new CDC;
		mdcBuffer->CreateCompatibleDC(&dc);
		bmpBuffer = new CBitmap;
		bmpBuffer->CreateCompatibleBitmap(&dc, rect.right, rect.bottom);
		mdcBuffer->SelectObject(bmpBuffer);
		
		mapAI = new CMapAI();
		gm->SetMap(mapAI);
		dataAI = gm->GetData();
		resAll = gm->GetResource();
		player = new CPlayer(3000, 3000, role);
		gm->GetData()->SetPlayer(player);
		//gm->GetData()->GetAllGameObjects().push_back(player);
		gameState = HOMEPAGE;
		lastTime = 0;
		curTime = 0;
		gameNum = 0;
		sortTime = 0;
		
		InitHome();
		SetTimer(1, 33, NULL);

	}
	void InitHome();  //初始化主界面
	void InitGame();  //初始化游戏
	void InitHelp();  //初始化帮助界面
	void chartlet();  //负责将所有需要显示的图片贴到屏幕上
	void rMove(int xmove, int ymove);  //控制人物坐标改变
	//void moveState();  //人物移动状态
	//void shootState(CPoint point);  //人物射击状态
	void showAllResource();  //加载所有资源
	void showPlayer();  //加载人物
	void showBlood();  //加载人物血量
	void showGun();  //加载人物子弹属性
	void showBullet(GameObject *gObject);
	void showTreasure();  //加载宝箱
	void showMonster(GameObject *gObject);
	void showWall(GameObject *gObject);

	void maxBlood(); //锁血秘籍

	DECLARE_MESSAGE_MAP()
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);  //检测按键是否按下，控制人物移动
	afx_msg void OnTimer(UINT_PTR nIDEvent);   // 定时器，定时刷新地图、怪物和宝箱，以及对地图进行碰撞检测，调用怪物的动画函数，调用子弹的移动函数
//	afx_msg void OnPaint();
//	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

class CTheApp :public CWinApp {
	BOOL InitInstance();

};

#endif 