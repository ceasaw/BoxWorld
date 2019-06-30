#include "CPlayer\CPlayer.h"
#include "GameManager\GameManager.h"

CPlayer::CPlayer()
{
	xPos = 1000;
	yPos = 1000;
	blood = 12;
	xp = 0;
	radius = 65;
	p.x = 0;
	p.y = 0;
	playerState = true;
	player = new CBitmap;
	m_Type = OBJECT_TYPE::CPLAYER;
}

CPlayer::CPlayer(int fx, int fy, CBitmap* bmp)
{
	xPos = fx;
	yPos = fy;
	blood = 12;
	xp = 0;
	radius = 40;
	p.x = 0;
	p.y = 0;
	playerState = true;
	player = bmp;
	m_Type = OBJECT_TYPE::CPLAYER;
}

void CPlayer::roleMove(int xmove, int ymove)
{
	//更改角色坐标，以当前坐标为初始点，x轴+xmove，y轴+ymove
	xPos += xmove;
	yPos += ymove;
}

int CPlayer::getXCoordinate()
{
	return xPos;
}

int CPlayer::getYCoordinate()
{
	return yPos;
}

void CPlayer::setBlood(int newBlood)
{
	if (newBlood > 60)
		blood = 60;
	else
		blood = newBlood;
}

int CPlayer::getBlood()
{
	return blood;
}

void CPlayer::setBmp(CBitmap* bmp)
{
	player = bmp;
}

CBitmap* CPlayer::getBmp()
{
	return player;
}

void CPlayer::upXP(int EXP)
{
	xp += EXP;
	if (xp >= 10)
	{
		if (blood <= 54)
			blood += 6;
		else
			blood = 60;
		xp -= 10;
		GameManager::getInstance()->pDSB_LU->Play(0,0,0);
	}
}

int CPlayer::getRadius()
{
	return radius;
}

void CPlayer::setRadius(int r)
{
	radius = r;
}

bool CPlayer::getPlayerState()
{
	return playerState;
}

void CPlayer::setPlayerState(bool state)
{
	playerState = state;
}

void CPlayer::setXpos(int posX)
{
	xPos = posX;
}

void CPlayer::setYpos(int posY)
{
	yPos = posY;
}

int CPlayer::getXpos()
{
	return xPos + 65;
}

int CPlayer::getYpos()
{
	return yPos + 65;
}

void CPlayer::setPoint(int x, int y)
{
	p.x = x;
	p.y = y;
}

Point CPlayer::getPoint()
{
	CPoint point;
	GetCursorPos(&point);
	CRect rect;
	GetClientRect(AfxGetMainWnd()->m_hWnd, &rect);

	if (playerState)
	{
		if (point.x > rect.right / 2)
		{
			if (point.y > rect.bottom / 2)
			{
				p.x = 780;
				p.y = 0;
			}
			else
			{
				p.x = 520;
				p.y = 130;
			}
		}
		else
		{
			if (point.y > rect.bottom / 2)
			{
				p.x = 520;
				p.y = 0;
			}
			else
			{
				p.x = 780;
				p.y = 130;
			}
		}
	}
	else
	{
		if (point.x > rect.right / 2)
		{
			if (point.y > rect.bottom / 2)
			{
				p.x = 910;
				p.y = 0;
			}
			else
			{
				p.x = 650;
				p.y = 130;
			}
		}
		else
		{
			if (point.y > rect.bottom / 2)
			{
				p.x = 650;
				p.y = 0;
			}
			else
			{
				p.x = 910;
				p.y = 130;
			}
		}
	}
	return p;
}

OBJECT_TYPE CPlayer::getObjectType()
{
	return m_Type;
}

void CPlayer::setObjectType(OBJECT_TYPE type)
{
	m_Type = type;
}

PicPos* CPlayer::getPicAndPos()
{
	return nullptr;
}