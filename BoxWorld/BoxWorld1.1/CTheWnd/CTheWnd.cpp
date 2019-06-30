#include "CTheWnd\CTheWnd.h"

CTheApp theApp;


BOOL CTheApp::InitInstance() {
	CTheWnd *pf = new CTheWnd;
	GameManager::getInstance()->pDSB_BK->Play(0, 0, 1);
	pf->ShowWindow(SW_SHOWMAXIMIZED);
	pf->UpdateWindow();
	this->m_pMainWnd = pf;
	return TRUE;
}

BEGIN_MESSAGE_MAP(CTheWnd, CFrameWnd)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void CTheWnd::InitHome()
{
	//  初始化主界面
	mciSendString("open buttonclick.mp3 alias back", NULL, 0, NULL);
	home = new CBitmap;
	home->m_hObject = LoadImage(NULL, "./BMPResources/home2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	gameState = HOMEPAGE;
}

void CTheWnd::InitGame()
{
	//  初始化游戏
	if (gameNum >0)
	{
		gm->ReSetAllGameObjects();
	}
	else
	{
		mapAI->WALLX_Y();
	}
	
	map = resAll->GetMapBmp();
	role = resAll->GetMonsterBmp();
	stone = resAll->GetStoneBmp();
	heart = resAll->GetHeartBmp();
	gun = resAll->GetGunBmp();
	rBullet = resAll->GetBulletBmp();
	mBullet = resAll->GetMonsterBulletBmp();
	shadow = resAll->GetShadowBmp();
	treaChest = resAll->GetTreasuretBmp();
	monBlood = resAll->GetMonsterBloodBmp();
	bossBlood = resAll->GetBossBloodBmp();

	win = new CBitmap;
	win->m_hObject = LoadImage(NULL, "./BMPResources/YouWin.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	lose = new CBitmap;
	lose->m_hObject = LoadImage(NULL, "./BMPResources/youLost.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	back = new CBitmap;
	back->m_hObject = LoadImage(NULL, "./BMPResources/backToMenu.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	Point point = mapAI->EnemyCreatePoint();
	int x = point.x;
	int y = point.y;
	player = new CPlayer(x, y, role);
	gm->GetData()->SetPlayer(player);
	gm->GetData()->GetAllGameObjects().push_back((GameObject*)player);

	
	shoot = false;
	hack = false;
	time = 1;
	bultime = 10;
	xSrc = 0;
	ySrc = 0;
	gameNum += 1;
	gameState = STARTGAME;
	sortTime = 0;
	boss = nullptr;
}

void CTheWnd::InitHelp()
{
	//  初始化帮助界面
	help = new CBitmap;
	help->m_hObject = LoadImage(NULL, "./BMPResources/help2.bmp", IMAGE_BITMAP, 1920, 1080, LR_LOADFROMFILE);
	gameState = HELP;
}



void CTheWnd::chartlet()
{
	//负责将所有需要显示的图片贴到屏幕上

	/*首先获取所有地图、人物、怪物、宝箱、子弹的对象，
	先排除exist为false的对象，再排除显示位置在屏幕外的对象，
	将所有能够显示出来的图片按从右上到左下的位置排序，地图贴
	在最下面，然后依次贴这些图片*/

	CClientDC dc(this);

	switch (gameState)
	{
	case HOMEPAGE:
		mdc->SelectObject(home);
		mdcBuffer->BitBlt(0, 0, rect.right, rect.bottom, mdc, 0, 0, SRCCOPY);
		break;
	case STARTGAME:
	case WIN:
	case LOSE:
		xSrc = (gm->GetData()->GetPlayer()->getXCoordinate()) - ((rect.right - 130) / 2);
		ySrc = (gm->GetData()->GetPlayer()->getYCoordinate()) - ((rect.bottom - 130) / 2);
		mdc->SelectObject(map);
		mdcBuffer->BitBlt(0, 0, rect.right+100, rect.bottom+100, mdc, xSrc, ySrc, SRCCOPY);

		showTreasure();
		showAllResource();

		showBlood();
		showGun();

		if (gameState == WIN)
		{
			mdc->SelectObject(win);
			mdcBuffer->BitBlt(647, 300, 627, 117, mdc, 0, 117, SRCAND);
			mdcBuffer->BitBlt(647, 300, 627, 117, mdc, 0, 0, SRCPAINT);
			mdc->SelectObject(back);
			mdcBuffer->BitBlt(810, 551, 301, 78, mdc, 0, 78, SRCAND);
			mdcBuffer->BitBlt(810, 551, 301, 78, mdc, 0, 0, SRCPAINT);
		}
		if (gameState == LOSE)
		{
			mdc->SelectObject(lose);
			mdcBuffer->BitBlt(680, 401, 501, 138, mdc, 0, 138, SRCAND);
			mdcBuffer->BitBlt(680, 401, 501, 138, mdc, 0, 0, SRCPAINT);
			mdc->SelectObject(back);
			mdcBuffer->BitBlt(810, 671, 301, 78, mdc, 0, 78, SRCAND);
			mdcBuffer->BitBlt(810, 671, 301, 78, mdc, 0, 0, SRCPAINT);
		}

		break;
	case HELP:
		mdc->SelectObject(help);
		mdcBuffer->BitBlt(0, 0, rect.right, rect.bottom, mdc, 0, 0, SRCCOPY);
		break;
	}

	dc.BitBlt(0, 0, rect.right, rect.bottom, mdcBuffer, 0, 0, SRCCOPY);
}


void CTheWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (gameState == STARTGAME)
	{
		if (nChar == VK_ESCAPE)
		{
			if (MessageBox(_T("确定要返回主界面吗？"), _T("返回主界面"), MB_YESNO) == IDYES)
			{
				InitHome();
			}
		}

	}
	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}




void CTheWnd::OnTimer(UINT_PTR nIDEvent)
{
	// 定时器，定时刷新地图、怪物和宝箱，以及对地图进行碰撞检测，调用怪物的动画函数，调用子弹的移动函数

	// 检测按键是否按下，改变人物位置


	int xmove = 0, ymove = 0;
	rMove(xmove, ymove);

	if (gm->GetData()->GetPlayer()->getBlood() <= 0)
	{
		//gm->SetPlayerState(false);
		gm->GetData()->GetPlayer()->setBlood(12);
		gameState = LOSE;
	}
	else if (gm->GetCurrentLevel() == 4)
	{
		gm->SetCurrentLevel(1);
		gameState = WIN;
	}
	else
	{
		if (gameState == STARTGAME)
		{
			if (0 == time % enemyRefreshInterval)
			{
				//调用随机生成一个怪物的函数
				if (gm->GetEnemyShowNum() < maxEnemyNum)
				{
						Point point = mapAI->EnemyCreatePoint();
						gm->AddNewEnemy(point.x, point.y);
				}
			}

			if (0 == time % 50)
			{
				//调用随机生成一个宝箱的函数
				Point point = mapAI->ChestCreate();
				gm->AddNewTreasureChest(point.x, point.y);

			}

			//显示boss
			gm->ShowBoss();

			//秘籍--满血
			maxBlood();
			if (hack)
			{
				gm->GetData()->GetPlayer()->setBlood(60);
			}

			//调用显示子弹的函数
			for (int i = 0; i < dataAI->GetBullets().size(); i++)
			{
				if (dataAI->GetBullets()[i]->GetExist())
				{
					dataAI->GetBullets()[i]->BulletMove();
				}
			}

			for (int j = 0; j < dataAI->GetEnemys().size(); j++)
			{
				if (dataAI->GetEnemys()[j]->getExist())
				{
					dataAI->GetEnemys()[j]->updateEnemy();
				}
			}


			//调用碰撞检测并进行处理的函数
			mapAI->ChestCollisionDetection();
			mapAI->WALLCollisionDetection();
			mapAI->BulletCollisionDetection();


			time += 1;
			bultime += 1;
		}
	}

	//调用刷新地图的函数
	this->chartlet();

	CFrameWnd::OnTimer(nIDEvent);
}


void CTheWnd::rMove(int xmove, int ymove)
{
	if (gameState == STARTGAME)
	{
		bool onekey = true;
		bool keyDown = true;
		int xPos = gm->GetData()->GetPlayer()->getXCoordinate();
		int yPos = gm->GetData()->GetPlayer()->getYCoordinate();
		if (GetKeyState('W') < 0)
		{
			if (GetKeyState('A') < 0 || GetKeyState('D') < 0)
			{
				if (GetKeyState('A') < 0)
				{
					xmove -= 14;
					onekey = false;
				}
				if (GetKeyState('D') < 0)
				{
					xmove += 14;
					onekey = false;
				}
				ymove -= 14;
			}
			if (GetKeyState('S') < 0)
			{
				onekey = false;
			}
			if (onekey)
				ymove -= 20;
			keyDown = false;
		}
		else if (GetKeyState('S') < 0)
		{
			if (GetKeyState('A') < 0 || GetKeyState('D') < 0)
			{
				if (GetKeyState('A') < 0)
				{
					xmove -= 14;
					onekey = false;
				}
				if (GetKeyState('D') < 0)
				{
					xmove += 14;
					onekey = false;
				}
				ymove += 14;
			}
			if (GetKeyState('W') < 0)
			{
				onekey = false;
			}
			if (onekey)
				ymove += 20;
			keyDown = false;
		}
		else if (GetKeyState('A') < 0)
		{
			if (GetKeyState('W') < 0 || GetKeyState('S') < 0)
			{
				if (GetKeyState('W') < 0)
				{
					ymove -= 14;
					onekey = false;
				}
				if (GetKeyState('S') < 0)
				{
					ymove += 14;
					onekey = false;
				}
				xmove -= 14;
			}
			if (GetKeyState('D') < 0)
			{
				onekey = false;
			}
			if (onekey)
				xmove -= 20;
			keyDown = false;
		}
		else if (GetKeyState('D') < 0)
		{
			if (GetKeyState('W') < 0 || GetKeyState('S') < 0)
			{
				if (GetKeyState('W') < 0)
				{
					ymove -= 14;
					onekey = false;
				}
				if (GetKeyState('S') < 0)
				{
					ymove += 14;
					onekey = false;
				}
				xmove += 14;
			}
			if (GetKeyState('A') < 0)
			{
				onekey = false;
			}
			if (onekey)
				xmove += 20;
			keyDown = false;
		}
		if (mapAI->WALL_PECollision(xPos + xmove , yPos + ymove ))
		{
			gm->GetData()->GetPlayer()->roleMove(xmove, ymove);
		}
	}

}


void CTheWnd::showPlayer()
{
	mdc->SelectObject(shadow);
	mdcBuffer->BitBlt((rect.right - 130) / 2, (rect.bottom - 130) / 2, 130, 130, mdc, 130, 780, SRCAND);
	mdcBuffer->BitBlt((rect.right - 130) / 2, (rect.bottom - 130) / 2, 130, 130, mdc, 0, 780, SRCPAINT);

	
	mdc->SelectObject(role);
	mdcBuffer->BitBlt((rect.right - 130) / 2, (rect.bottom - 130) / 2, 130, 130, mdc, player->getPoint().x, player->getPoint().y, SRCAND);
	mdcBuffer->BitBlt((rect.right - 130) / 2, (rect.bottom - 130) / 2, 130, 130, mdc, player->getPoint().x - 520, player->getPoint().y, SRCPAINT);
	if (!gm->GetData()->GetPlayer()->getPlayerState())
	{
		gm->GetData()->GetPlayer()->setPlayerState(true);
	}
}

void CTheWnd::showBlood()
{
	mdc->SelectObject(heart);

	int blood = gm->GetData()->GetPlayer()->getBlood();
	int i = 0;
	if (blood >= 0)
	{
		for (; i < blood / 3; i++)
		{
			mdcBuffer->BitBlt(42 + (i % 5) * 84, 30 + (i / 5) * 82, 84, 82, mdc, 168, 0, SRCAND);
			mdcBuffer->BitBlt(42 + (i % 5) * 84, 30 + (i / 5) * 82, 84, 82, mdc, 0, 0, SRCPAINT);
		}
		if (blood % 3 == 2)
		{
			mdcBuffer->BitBlt(42 + (i % 5) * 84, 30 + (i / 5) * 82, 84, 82, mdc, 168, 0, SRCAND);
			mdcBuffer->BitBlt(42 + (i % 5) * 84, 30 + (i / 5) * 82, 84, 82, mdc, 84, 0, SRCPAINT);
		}
		else if (blood % 3 == 1)
		{
			mdcBuffer->BitBlt(42 + (i % 5) * 84, 30 + (i / 5) * 82, 84, 82, mdc, 252, 0, SRCAND);
			mdcBuffer->BitBlt(42 + (i % 5) * 84, 30 + (i / 5) * 82, 84, 82, mdc, 336, 0, SRCPAINT);
		}
	}

}

void CTheWnd::showGun()
{
	mdc->SelectObject(gun);

	int attr = gm->GetPlayerBulletAttribute();
	int x = 0, y = 0;
	switch (attr)
	{
	case metal:
		x = 305;
		y = 0;
		break;
	case wood:
		x = 0;
		y = 208;
		break;
	case water:
		x = 305;
		y = 208;
		break;
	case fire:
		x = 0;
		y = 416;
		break;
	case earth:
		x = 305;
		y = 416;
		break;
	default:
		x = 0;
		y = 0;
		break;
	}

	mdcBuffer->BitBlt(1575, 802, 305, 208, mdc, 0, 624, SRCAND);
	mdcBuffer->BitBlt(1575, 802, 305, 208, mdc, x, y, SRCPAINT);
}

void CTheWnd::showBullet(GameObject *gObject)
{
	int x = gm->GetData()->GetPlayer()->getXCoordinate() - (rect.right - 130) / 2;
	int y = gm->GetData()->GetPlayer()->getYCoordinate() - (rect.bottom - 130) / 2;
	CBullet* bul = (CBullet*)gObject;

	if (bul->GetExist())
	{
		if (bul->getXpos() > (x - 150) && bul->getXpos() < (x + rect.right + 150))
		{
			if (bul->getYpos() > (y - 150) && bul->getYpos() < (y + rect.bottom + 150))
			{
				if (bul->GetIsFromPlayer())
				{
					mdc->SelectObject(rBullet);
					mdcBuffer->BitBlt(bul->getXpos() - x, bul->getYpos() - y, 30, 30, mdc, 0, 180, SRCAND);
					mdcBuffer->BitBlt(bul->getXpos() - x, bul->getYpos() - y, 30, 30, mdc, bul->getPoint().x, bul->getPoint().y, SRCPAINT);
				}
				else
				{
					mdc->SelectObject(mBullet);
					mdcBuffer->BitBlt(bul->getXpos() - x, bul->getYpos() - y, 30, 30, mdc, bul->getPoint().x + 30, bul->getPoint().y, SRCAND);
					mdcBuffer->BitBlt(bul->getXpos() - x, bul->getYpos() - y, 30, 30, mdc, bul->getPoint().x, bul->getPoint().y, SRCPAINT);
				}
			}
		}

	}

}

void CTheWnd::showTreasure()
{
	int x = gm->GetData()->GetPlayer()->getXCoordinate() - (rect.right - 130) / 2;
	int y = gm->GetData()->GetPlayer()->getYCoordinate() - (rect.bottom - 130) / 2;

	for (int i = 0; i < dataAI->GetChests().size(); i++)
	{
		dataAI->GetChests()[i]->refreshHeal();
		if (dataAI->GetChests()[i]->getExist())
		{
			if (dataAI->GetChests()[i]->getX() > (x - 150) && dataAI->GetChests()[i]->getX() < (x + rect.right + 150))
			{
				if (dataAI->GetChests()[i]->getY() > (y - 150) && dataAI->GetChests()[i]->getY() < (y + rect.bottom + 150))
				{
					mdc->SelectObject(shadow);
					mdcBuffer->BitBlt(dataAI->GetChests()[i]->getX() - x, dataAI->GetChests()[i]->getY() - y, 130, 130, mdc, 130, 780, SRCAND);
					mdcBuffer->BitBlt(dataAI->GetChests()[i]->getX() - x, dataAI->GetChests()[i]->getY() - y, 130, 130, mdc, 0, 780, SRCPAINT);
					mdc->SelectObject(treaChest);
					mdcBuffer->BitBlt(dataAI->GetChests()[i]->getX() - x, dataAI->GetChests()[i]->getY() - y, 130, 130, mdc, 130, 0, SRCAND);
					mdcBuffer->BitBlt(dataAI->GetChests()[i]->getX() - x, dataAI->GetChests()[i]->getY() - y, 130, 130, mdc, 0, 0, SRCPAINT);
				}
			}
		}
	}
}

void CTheWnd::showMonster(GameObject * gObject)
{
	int x = gm->GetData()->GetPlayer()->getXCoordinate() - (rect.right - 130) / 2;
	int y = gm->GetData()->GetPlayer()->getYCoordinate() - (rect.bottom - 130) / 2;
	int attr;

	CEnemyAI *enemy = (CEnemyAI*)gObject;

	if (enemy->getExist())
	{
		if (enemy->getXpos() > (x - 150) && enemy->getXpos() < (x + rect.right + 150))
		{
			if (enemy->getYpos() > (y - 150) && enemy->getYpos() < (y + rect.bottom + 150))
			{
				PicPos *monPos = enemy->getPicAndPos();

				int picNum = enemy->getAttributeAnimationNum();

				if (enemy->showHpBar())
				{
					mdc->SelectObject(shadow);
					attr = enemy->getAttribute().getBulletAttribute();
					mdcBuffer->BitBlt(enemy->getXpos() - x - 65, enemy->getYpos() - y - 65, 130, 130, mdc, ((picNum - 1) / 3) * 130, 650, SRCAND);
					mdcBuffer->BitBlt(enemy->getXpos() - x - 65, enemy->getYpos() - y - 65, 130, 130, mdc, ((picNum - 1) / 3) * 130, (attr - 1) * 130, SRCPAINT);
				}

				mdc->SelectObject(monPos->pic.picture);
				mdcBuffer->BitBlt(enemy->getXpos() - x - 65, enemy->getYpos() - y - 65, 130, 130, mdc, monPos->pic.maskPos.x, monPos->pic.maskPos.y, SRCAND);
				mdcBuffer->BitBlt(enemy->getXpos() - x - 65, enemy->getYpos() - y - 65, 130, 130, mdc, monPos->pic.spiritPos.x, monPos->pic.spiritPos.y, SRCPAINT);
				if (enemy->isBoss())
				{

				}
				else
				{
					if (enemy->showHpBar())
					{
						mdc->SelectObject(monBlood);
						mdcBuffer->BitBlt(enemy->getXpos() - x - 57, enemy->getYpos() - y - 83, 114, 18, mdc, 0, 54, SRCAND);
						mdcBuffer->BitBlt(enemy->getXpos() - x - 57, enemy->getYpos() - y - 83, int(114 * enemy->getPercentage()), 18, mdc, 0, 18, SRCPAINT);
						mdcBuffer->BitBlt(enemy->getXpos() - x - 57, enemy->getYpos() - y - 83, 114, 18, mdc, 0, 36, SRCAND);
						mdcBuffer->BitBlt(enemy->getXpos() - x - 57, enemy->getYpos() - y - 83, 114, 18, mdc, 0, 0, SRCPAINT);
					}
				}
			}
		}
	}
}

void CTheWnd::showWall(GameObject * gObject)
{
	mdc->SelectObject(stone);

	int x = gm->GetData()->GetPlayer()->getXCoordinate() - (rect.right - 130) / 2;
	int y = gm->GetData()->GetPlayer()->getYCoordinate() - (rect.bottom - 130) / 2;

	WALL* wall = (WALL*)gObject;

	if (wall->getXpos() > (x - 150) && wall->getXpos() < (x + rect.right + 150))
	{
		if (wall->getYpos() > (y - 150) && wall->getYpos() < (y + rect.bottom + 150))
		{
			mdcBuffer->BitBlt(wall->getXpos() - x - 61, wall->getYpos() - y - 41, 212, 212, mdc, wall->getPoint().x + 212, wall->getPoint().y, SRCAND);
			mdcBuffer->BitBlt(wall->getXpos() - x - 61, wall->getYpos() - y - 41, 212, 212, mdc, wall->getPoint().x, wall->getPoint().y, SRCPAINT);
		}
	}
}

void CTheWnd::maxBlood()
{
	if (GetKeyState('K') < 0)
	{
		hack = true;
	}
	if (GetKeyState('M') < 0)
	{
		gm->GetData()->GetPlayer()->setBlood(15);
		hack = false;
	}
}

void CTheWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	butDown = point;
	

	int bulletAttribute;
	CBitmap* bulletBmp = new CBitmap;
	int x = gm->GetData()->GetPlayer()->getXCoordinate();
	int y = gm->GetData()->GetPlayer()->getYCoordinate();
	int xBullet, yBullet;

	switch (gameState)
	{
	case HOMEPAGE:
		if (point.x >= 765 && point.x <= 1100)
		{
			if (point.y >= 580 && point.y <= 664)
			{
				gm->pDSB_MC->Play(0, 0, 0);
				InitGame();
			}
			else if (point.y >= 688 && point.y <= 782)
			{
				gm->pDSB_MC->Play(0, 0, 0);
				InitHelp();
			}
			else if (point.y >= 800 && point.y <= 888)
			{
				if (CWnd::MessageBox(_T("确定要退出游戏吗？"), _T("退出游戏"), MB_YESNO) == IDYES)
				{
					exit(0);
				}
			}
		}
		break;
	case STARTGAME:
		if (bultime >= 5)
		{
			gm->pDSB_ES->Play(0, 0, 0);
			xBullet = x - (rect.right - 130) / 2 + point.x;
			yBullet = y - (rect.bottom - 130) / 2 + point.y;
			bulletAttribute = gm->GetPlayerBulletAttribute();
			gm->AddNewBullet(x + 65, y + 65, true, xBullet, yBullet, bulletAttribute);
			bultime = 0;
			player->setPlayerState(false);
		}
		break;
	case HELP:
		if (point.x >= 1653 && point.x <= 1750)
		{
			if (point.y >= 58 && point.y <= 110)
			{
				gm->pDSB_MC->Play(0, 0, 0);
				InitHome();
			}
		}
		break;
	case WIN:
		if (point.x >= 810 && point.x <= 1111)
		{
			if (point.y >= 551 && point.y <= 629)
			{
				gm->pDSB_MC->Play(0, 0, 0);
				InitHome();
			}
		}
		break;
	case LOSE:
		if (point.x >= 810 && point.x <= 1111)
		{
			if (point.y >= 671 && point.y <= 749)
			{
				gm->pDSB_MC->Play(0, 0, 0);
				InitHome();
			}
		}
		break;
	}
	
	
	CFrameWnd::OnLButtonDown(nFlags, point);
}

void CTheWnd::showAllResource()
{
	dataAI->SortAllGameObjects();
	vector<GameObject*> gObject = gm->GetData()->GetAllGameObjects();

	bool show = false;

	for (int i = 0; i < gObject.size(); i++)
	{

		if (gObject[i]->getObjectType() == OBJECT_TYPE::CENEMY)
		{
			CEnemyAI* enemy = (CEnemyAI*)gObject[i];
			if (enemy->isBoss())
			{
				if (enemy->getExist())
				{
					boss = enemy;
					show = true;
				}
			}
		}
		switch ((int)gObject[i]->getObjectType())
		{
		case (int)OBJECT_TYPE::CBULLET:
			showBullet(gObject[i]);
			break;
		case (int)OBJECT_TYPE::CENEMY:
			showMonster(gObject[i]);
			break;
		case (int)OBJECT_TYPE::CPLAYER:
			showPlayer();
			break;
		case (int)OBJECT_TYPE::CWALL:
			showWall(gObject[i]);
			break;
		}
	}
	if (boss != nullptr)
	{
		if (show)
		{
			mdc->SelectObject(bossBlood);
			mdcBuffer->BitBlt(585, 30, 751, 102, mdc, 0, 204, SRCAND);
			mdcBuffer->BitBlt(585, 30, 751, 102, mdc, 0, 0, SRCPAINT);
			mdcBuffer->BitBlt(585, 30, 751, 102, mdc, 0, 306, SRCAND);
			mdcBuffer->BitBlt(585, 30, int(666 * boss->getPercentage()) + 85, 102, mdc, 0, 102, SRCPAINT);
		}
	}


}
