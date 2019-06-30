#include "GameManager/GameManager.h"
#include "CEnemyAI/CMeleeMonsterAI.h"
#include "CEnemyAI/CBlockMonsterAI.h"
#include "CEnemyAI/CRangeMonsterAI.h"
#include "CEnemyAI/CBosssAI/CDemon.h"
#include "CEnemyAI/CBosssAI/CGrassPig.h"
#include "CEnemyAI/CBosssAI/CLava.h"
#include "CMapAI/CMapAI.h"
GameManager* GameManager::m_Instance = nullptr;
GameManager::GameManager()
{
	this->m_DTAI = new CDataAI();
	this->m_map = nullptr;
	this->resource = new ResourceAllocator();

	this->playerBulletAttribute = 0;
	this->isPlayerDie = false;

	this->curLevel = 1;
	this->isBossCreate = false;
	this->enemyType = 0;
	this->enemyShowNum = 0;

	this->gameStartTime = GetTickCount();

}

GameManager * GameManager::getInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new GameManager();
	}

	return m_Instance;
}

void GameManager::setBossCreate(bool bossCreate)
{
	this->isBossCreate = bossCreate;
}

int GameManager::GetPlayerBulletAttribute()
{
	return playerBulletAttribute;
}

int GameManager::GetCurrentLevel()
{
	return this->curLevel;
}

int GameManager::SetCurrentLevel(int levelPlus)
{
	return this->curLevel += levelPlus;
}

int GameManager::GetEnemyShowNum()
{
	return this->enemyShowNum;
}

void GameManager::PlusEnemyShowNum(int num)
{
	this->enemyShowNum += num;
}

CDataAI * GameManager::GetData()
{
	return m_DTAI;
}

bool GameManager::GetPlayerState()
{
	return isPlayerDie;
}

void GameManager::SetPlayerState(bool isDie)
{
	this->isPlayerDie = isDie;
}

CMapAI * GameManager::GetMap()
{
	return m_map;
}

void GameManager::SetMap(CMapAI * tempMap)
{
	this->m_map = tempMap;
}

ResourceAllocator * GameManager::GetResource()
{
	return this->resource;
}

LPDIRECTSOUNDBUFFER GameManager::CreateSecondaryBuffer(LPSTR filename)
{
	HMMIO hmmio;
	MMRESULT mmresult;
	hmmio = mmioOpen(filename, NULL, NULL);
	if (hmmio == NULL) {
		//MessageBox("�ļ���ʧ�ܣ�");
	}
	MMCKINFO ckriff;
	ckriff.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmresult = mmioDescend(hmmio, &ckriff, NULL, MMIO_FINDRIFF);
	if (mmresult != MMSYSERR_NOERROR) {
		//MessageBox("�ļ����Ͳ���WAVE!");
	}
	MMCKINFO ckinfo;
	ckinfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmresult = mmioDescend(hmmio, &ckinfo, &ckriff, MMIO_FINDCHUNK);
	if (mmresult != MMSYSERR_NOERROR) {
		//MessageBox("����fmt�������");
	}
	WAVEFORMATEX swfmt;
	if (mmioRead(hmmio, (HPSTR)&swfmt, sizeof(swfmt)) == -1) {
		//MessageBox("��ȡ��Ƶ�ļ���ʽʧ�ܣ�");
	}
	mmioAscend(hmmio, &ckinfo, 0);
	ckinfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmresult = mmioDescend(hmmio, &ckinfo, &ckriff, MMIO_FINDCHUNK);
	if (MMSYSERR_ERROR == mmresult) {
		//MessageBox("����data����ʧ�ܣ�");
	}
	LPDIRECTSOUNDBUFFER pTempBuf;
	DSBUFFERDESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.dwSize = sizeof(desc);
	desc.lpwfxFormat = &swfmt;
	desc.dwFlags = DSBCAPS_STATIC;
	desc.dwBufferBytes = ckinfo.cksize;
	result = pDS->CreateSoundBuffer(&desc, &pTempBuf, NULL);

	if (result != DS_OK)
	{
		//MessageBox("�����λ�����ʧ�ܣ�");
	}
	LPVOID pAudio;
	DWORD BytesAudio;

	pTempBuf->Lock(0, ckinfo.cksize, &pAudio, &BytesAudio, NULL, NULL, NULL);
	if (mmioRead(hmmio, (HPSTR)pAudio, BytesAudio) == -1) {
		//MessageBox("��ȡ��Ƶ�ļ�����ʧ�ܣ�");
	}
	pTempBuf->Unlock(pAudio, BytesAudio, NULL, NULL);
	mmioClose(hmmio, 0);
	return pTempBuf;
}

void GameManager::ShowBoss()
{
	curTime = GetTickCount();
	if (isBossCreate)
	{
		gameStartTime = curTime;
		return;
	}	
	if (curTime - gameStartTime >= 0.1 * 60 * 1000)
	{
		gameStartTime = curTime;
		Point p = m_map->EnemyCreatePoint();
		AddNewBoss(p.x, p.y);
		this->isBossCreate = true;
	}
}

void GameManager::ChangePlayerHealth(int healthChange)
{
	m_DTAI->GetPlayer()->setBlood(healthChange);

	if (!healthChange)
	{
		this->isPlayerDie = true;
	}
}

void GameManager::ChangePlayerExperience(int exChange)
{
	m_DTAI->GetPlayer()->upXP(exChange);
	enemyShowNum--;
}

void GameManager::ChangePlayerAttribute(int attribute)
{
	playerBulletAttribute = attribute;
}

void GameManager::AddNewBullet(int x, int y, bool isPlayer, int xMouse, int yMouse, int bulletAttribute)
{
	if (m_DTAI == NULL)
		return;

	vector<CBullet*>::iterator itor = m_DTAI->GetBullets().begin();
	while (itor != m_DTAI->GetBullets().end())
	{
		//���÷���
		if ((*itor)->GetExist() == false)
		{
			(*itor)->setXpos(x);
			(*itor)->setYpos(y);
			(*itor)->SetIsFromPlayer(isPlayer);
			(*itor)->SetBulletFlySpeed(isPlayer);
			(*itor)->SetBulletAttribute(bulletAttribute);
			(*itor)->SetBulletBmpPoint(isPlayer);
			(*itor)->SetDirection(xMouse, yMouse);
			(*itor)->SetExist(true);
			if(isPlayer)
				this->playerBulletAttribute = bulletAttribute;
			return;
		}
		itor++;
	}
	//�����µ��ӵ��������ӵ��Ķ������
	CBullet* tempBullet = new CBullet(bulletAttribute);
	tempBullet->setXpos(x);
	tempBullet->setYpos(y);
	tempBullet->SetIsFromPlayer(isPlayer);
	tempBullet->SetBulletFlySpeed(isPlayer);
	tempBullet->SetBulletAttribute(bulletAttribute);
	tempBullet->SetBulletBmpPoint(isPlayer);
	tempBullet->SetDirection(xMouse, yMouse);
	tempBullet->SetExist(true);
	if(isPlayer)
		this->playerBulletAttribute = bulletAttribute;
	m_DTAI->GetBullets().push_back(tempBullet);
	m_DTAI->GetAllGameObjects().push_back((GameObject*)tempBullet);
}

void GameManager::AddNewEnemy(int x, int y)
{
	this->PlusEnemyShowNum(1);
	srand((unsigned)time(NULL));
	this->enemyType = rand() % 8;
	//this->enemyType = 7;
	int tempType;
	FILE_MONSTER_ATTRIBUTE tempFMA;
	if (enemyType <= 2)
	{
		tempType = curLevel - 1;
		tempFMA = fileMonster[ENEMY_TYPE(tempType)];
	}
	else if (enemyType <= 5)
	{
		tempType = curLevel + 2;
		tempFMA = fileMonster[ENEMY_TYPE(tempType)];

	}
	else
	{
		if (rand() % 2 == 0)
		{
			tempType = (int)ENEMY_TYPE::BLOCKMONSTER1;
			tempFMA = fileMonster[ENEMY_TYPE::BLOCKMONSTER1];
		}
		else
		{
			tempType = (int)ENEMY_TYPE::BLOCKMONSTER2;
			tempFMA = fileMonster[ENEMY_TYPE::BLOCKMONSTER2];
		}
	}

	vector<Point> road = this->m_map->RoadRandom(x, y, tempFMA.patrolRange);
	Enemy_Attributes tempEA = {x, y, road, tempFMA.attack, tempFMA.blood, tempFMA.experience,
	tempFMA.speed, tempFMA.attackInterval, rand()%5 + 1, tempFMA.attackRange,tempFMA.detectionRange,
	tempFMA.patrolRange, 60, false, (ENEMY_TYPE)tempType};

	//��ʼѰ���Ѿ��������������ó�false�ĵ���
	vector<CEnemyAI*>::iterator itor = m_DTAI->GetEnemys().begin();
	while (itor != m_DTAI->GetEnemys().end())
	{
		if ((*itor)->getExist() == false)
		{
			//��֤����������ǹ̶���
			if ((*itor)->getEnemyType() == (ENEMY_TYPE)tempType)
			{
				(*itor)->setAllAttribute(tempEA);
				(*itor)->enable();
				enemyShowNum++;
				return;
			}
		}
		itor++;
	}

	CEnemyAI* tempEnemy;
	//��Ӿ���ĵ���
	if (tempType <= 2)
		tempEnemy = new CMeleeMonsterAI(tempEA);
	else if(tempType <= 5)
		tempEnemy = new CRangeMonsterAI(tempEA);
	else
		tempEnemy = new CBlockMonsterAI(tempEA);
	tempEnemy->enable();
	m_DTAI->GetEnemys().push_back(tempEnemy);
	m_DTAI->GetAllGameObjects().push_back((GameObject*)tempEnemy);
	enemyShowNum++;
}

void GameManager::AddNewBoss(int x, int y)
{
	FILE_MONSTER_ATTRIBUTE tempFMA;
	CEnemyAI* tempBoss = nullptr;
	ENEMY_TYPE tempType;
	switch(curLevel)
	{
	case 1:
		tempFMA = fileMonster[ENEMY_TYPE::BOSS1];
		tempBoss = new CGrassPig();
		tempType = ENEMY_TYPE::BOSS1;
		break;
	case 2:
		tempFMA = fileMonster[ENEMY_TYPE::BOSS2];
		tempBoss = new CLava();
		tempType = ENEMY_TYPE::BOSS2;
		break;
	case 3:
		tempFMA = fileMonster[ENEMY_TYPE::BOSS3];
		tempBoss = new CDemon();
		tempType = ENEMY_TYPE::BOSS3;
		break;
	}

	//��������
	vector<Point> road = this->m_map->RoadRandom(x, y, tempFMA.patrolRange);
	Enemy_Attributes tempEA = { x, y, road, tempFMA.attack, tempFMA.blood, tempFMA.experience,
	tempFMA.speed, tempFMA.attackInterval, rand() % 5 + 1, tempFMA.attackRange,tempFMA.detectionRange,
	tempFMA.patrolRange, 60, false, tempType };

	//��Ѱ���Ƿ������õ�BOSS(�ڶ��ο�ʼ��Ϸ)
	vector<CEnemyAI*>::iterator itor = m_DTAI->GetEnemys().begin();
	while (itor != m_DTAI->GetEnemys().end())
	{
		if ((*itor)->getExist() == false)
		{
			//��֤����������ǹ̶���
			if ((*itor)->getEnemyType() == (ENEMY_TYPE)tempType)
			{
				(*itor)->setAllAttribute(tempEA);
				(*itor)->enable();
				enemyShowNum++;
				return;
			}
		}
		itor++;
	}

	//�޿���BOSS�������µ�
	tempBoss->setAllAttribute(tempEA);
	tempBoss->enable();

	m_DTAI->GetEnemys().push_back(tempBoss);
	m_DTAI->GetAllGameObjects().push_back((GameObject*)tempBoss);
	enemyShowNum++;
}

void GameManager::AddNewTreasureChest(int x, int y)
{
	if (m_DTAI == NULL)
		return;

	vector<CTreasureChest*>::iterator itor = m_DTAI->GetChests().begin();
	while (itor != m_DTAI->GetChests().end())
	{
		if ((*itor)->getExist() == false)
		{
			(*itor)->setExist(true);
			(*itor)->setX(x);
			(*itor)->setY(y);
			(*itor)->setItem();
			return;
		}
		itor++;
	}

	//ֻ���Ҳ������õı����ʱ���ٴ����µ�
	CTreasureChest* tempChest = new CTreasureChest;
	tempChest->setX(x);
	tempChest->setY(y);
	tempChest->setExist(true);
	tempChest->setItem();
	m_DTAI->GetChests().push_back(tempChest);
}

int GameManager::GetPlayerCurrentHealth()
{
	return m_DTAI->GetPlayer()->getBlood();
}

Point& GameManager::GetPlayerCurrentPosition()
{
	CPlayer* tempPlayer = this->m_DTAI->GetPlayer();
	tempPoint = { tempPlayer ->getXpos(), tempPlayer->getYpos()};
	return tempPoint;
}

bool GameManager::JudgePointIsInWall(Point judgePoint)
{
	return m_map->JudgeIsWall(judgePoint.x, judgePoint.y);
}

void GameManager::ReSetAllGameObjects()
{
	for (int i = 0; i < m_DTAI->GetBullets().size(); i++)
	{
		m_DTAI->GetBullets()[i]->SetExist(false);
	}

	for (int i = 0; i < m_DTAI->GetEnemys().size(); i++)
	{
		m_DTAI->GetEnemys()[i]->disable();
	}

	for (int i = 0; i < m_DTAI->GetChests().size(); i++)
	{
		m_DTAI->GetChests()[i]->setExist(false);
	}

	this->curLevel = 1;
	this->enemyType = 0;
	this->enemyShowNum = 0;
	this->gameStartTime = GetTickCount();
	this->isBossCreate = false;
	this->playerBulletAttribute = 0;
}
