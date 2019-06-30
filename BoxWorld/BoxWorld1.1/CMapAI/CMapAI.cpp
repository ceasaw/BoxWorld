#include<math.h>
#include<time.h>
#include"CMapAI.h"
#include<afxwin.h>
#include<GameManager/GameManager.h>

bool CMapAI::JudgeIsWall(int x, int y) {
	for (int i = 0; i < 38; i++) {
		for (int j = 0; j < 20; j++) {
			if (this->isWall[i][j] == true) {
				int x0 = wall[i][j].getXpos();
				int y0 = wall[i][j].getYpos();
				int u = sqrt((x0 - x)*(x0 - x) + (y0 - y)*(y0 - y));
				if (this->wall[i][j].r+76 > u) {
					return true;

				}
			}
		}
	}
	return false;
}

void WallRandom(bool cirJ[38][20]) {//随机生成墙体标记数组
	for (int i = 0; i < 38; i++) {
		for (int j = 0; j < 20; j++) {
			cirJ[i][j] = false;
		}
	}
	srand((unsigned)time(NULL));
	for (int i = 3; i < 34; i += 6) {
		for (int j = 3; j < 16; j += 6) {
			int m = rand() % 100;
			if (m <= 90) {
				cirJ[i][j] = true;
				int ran[4];
				for (int i = 0; i < 4; i++) {
					ran[i] = i;
				}
				for (int i = 0; i < 4; i++) {
					int m = rand() % 4;
					int a = ran[i];
					ran[i] = ran[m];
					ran[m] = a;
				}
				int k = 2;
				int len = 1;
				for (int h = 0; h < 4; h++) {
					if (ran[h] == 0 && k != 0 && i + 1 < 10) {
						k--;
						cirJ[i + 1][j] = true;
						if (rand() % 100 <= 50 && len != 0) {
							cirJ[i + 2][j] = true;
							len--;
						}
					}
					if (ran[h] == 1 && k != 0 && i - 1 >= 0) {
						k--;
						cirJ[i - 1][j] = true;
						if (rand() % 100 <= 50 && len != 0) {
							cirJ[i - 2][j] = true;
							len--;
						}
					}
					if (ran[h] == 2 && k != 0 && j + 1 < 10) {
						k--;
						cirJ[i][j + 1] = true;
						if (rand() % 100 <= 50 && len != 0) {
							cirJ[i][j + 2] = true;
							len--;
						}
					}
					if (ran[h] == 3 && k != 0 && j - 1 >= 0) {
						k--;
						cirJ[i][j - 1] = true;
						if (rand() % 100 <= 50 && len != 0) {
							cirJ[i][j - 2] = true;
							len--;
						}
					}
				}
			}
		}
	}
}


void CMapAI::WALLX_Y() {
	WallRandom(this->isWall);//随机标记函数生成38X20.
	float x0 = 3082;
	float y0 = 641;
	int k = 0;
	int m = 0;
	int p = 0;
	for (int i = 0; i < 38; i++) {
		for (int j = 0; j < 20; j++) {
			if (this->isWall[i][j] == true) {
				int x = (x0 + (i - j)*sqrt(2) * 75);
				int y = (y0 + (i + j)*sqrt(2) * 75);
				this->wall[i][j].setXpos(x);
				this->wall[i][j].setYpos(y);

				WALL* tempWall = new WALL(x+20, y-10);
				GameManager::getInstance()->GetData()->GetWalls().push_back(tempWall);
				GameManager::getInstance()->GetData()->GetAllGameObjects().push_back(tempWall);
			}
			else {
				if (i > 2 && i < 36 && j > 2 && j <= 18)
				{
					m++;
					if (m == 6)
					{
						int x = (x0 + (i - j)*sqrt(2) * 75);
						int y = (y0 + (i + j)*sqrt(2) * 75);

						if (p < 100)
						{
							enemyborn[p] = { x,y };
						}
						p++;
						m = 0;
					}
				}
			}
		}
	}


}

Point CMapAI::ChestCreate() {

	bool afx = true;
	Point point;
	int x;
	int y;
	srand((unsigned)time(NULL));
	while (afx != false) {
		x = rand() % 38;
		y = rand() % 20;
		if (this->isWall[x][y] == false) {
			afx = false;
		}
	}
	point.x =int((x - y) * 75 * sqrt(2) + 3096);
	point.y = int((x + y) * 75 * sqrt(2) + 600);
	return point;
}

bool CMapAI::WALL_PECollision(int x, int y) {
	CPlayer* player = GameManager::getInstance()->GetData()->GetPlayer();
	vector<CBullet*> bullets = GameManager::getInstance()->GetData()->GetBullets();
	Point point2;
	point2.x = x;
	point2.y = y;
	for (int i = 0; i < 38; i++) {
		for (int j = 0; j < 20; j++) {
			if (this->isWall[i][j] == true) {
				Point point;
				point.x = this->wall[i][j].getXpos();
				point.y = this->wall[i][j].getYpos();
				int d2 = sqrt((point2.x - point.x)*(point2.x - point.x) + (point2.y - point.y)*(point2.y - point.y));
				if (d2 < this->wall[i][j].r + player->getRadius()) {
					return false;
				}
			}
			int a = point2.y - point2.x;
			int b = point2.y + point2.x;
			if ((point2.y - point2.x) < -2469 || (point2.y - point2.x) > 1603 || (point2.y + point2.x) < 3567 || (point2.y + point2.x) > 11457) {
				return false;
			}
		}
	}
	return true;
}
void CMapAI::WALLCollisionDetection() {
	CPlayer* player = GameManager::getInstance()->GetData()->GetPlayer();
	vector<CBullet*> bullets = GameManager::getInstance()->GetData()->GetBullets();
	for (int i = 0; i < 38; i++) {
		for (int j = 0; j < 20; j++) {
			if (this->isWall[i][j] == true) {
				Point point;
				point.x = this->wall[i][j].getXpos();
				point.y = this->wall[i][j].getYpos();
				
				for (int k = 0; k < bullets.size(); k++) {
					int x0 = bullets[k]->getXpos()-53;
					int y0 = bullets[k]->getYpos()-53;
					int d = sqrt((x0 - point.x)*(x0 - point.x) + (y0 - point.y)*(y0 - point.y));
					if (d < this->wall[i][j].r + bullets[k]->GetBulletRadius()) {
						bullets[k]->SetExist(false);
					}
				}
				
			}
		}
	}
}

void CMapAI::ChestCollisionDetection() {
	vector<CTreasureChest*> chest = GameManager::getInstance()->GetData()->GetChests();
	CPlayer* player = GameManager::getInstance()->GetData()->GetPlayer();
	Point point;
	point.x = player->getXCoordinate();
	point.y = player->getYCoordinate();
	for (int i = 0; i < chest.size(); i++) {
		if (chest[i]->getExist()) {
			int x0 = chest[i]->getX();
			int y0 = chest[i]->getY();
			int d = sqrt((x0 - point.x)*(x0 - point.x) + (y0 - point.y)*(y0 - point.y));
			if (d < player->getRadius() + chest[i]->getRadius()) {
				chest[i]->openTreasureChest();
			}
		}
	}
}

void CMapAI::BulletCollisionDetection() {
	vector<CBullet*> bullets = GameManager::getInstance()->GetData()->GetBullets();
	vector<CEnemyAI*> enemy = GameManager::getInstance()->GetData()->GetEnemys();
	CPlayer* player = GameManager::getInstance()->GetData()->GetPlayer();
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i]->GetExist()) {
			if ((bullets[i]->getYpos() - bullets[i]->getXpos()) < -2496 || (bullets[i]->getYpos() - bullets[i]->getXpos()) > 1786 || (bullets[i]->getYpos() + bullets[i]->getXpos()) < 3696 || (bullets[i]->getYpos() + bullets[i]->getXpos()) > 11796) {
				bullets[i]->SetExist(false);
			}
			else {
				if (bullets[i]->GetIsFromPlayer()) {
					for (int j = 0; j < enemy.size(); j++) {
						Point point = enemy[j]->getPosition();
						int d = sqrt((bullets[i]->getXpos() - point.x)*(bullets[i]->getXpos() - point.x) + (bullets[i]->getYpos() - point.y)*(bullets[i]->getYpos() - point.y));
						if (enemy[j]->getEnemyState()!= 2 && d < enemy[j]->getRadius() + bullets[i]->GetBulletRadius()&& bullets[i]->GetExist()) {
							bullets[i]->SetExist(false);
							int atB = bullets[i]->GetBulletAttribute();
							int atE = enemy[j]->getAttribute().getBulletAttribute();
							float AttractK = 1;//倍率
							//克制计算
							if (atB == 1) {
								if (atE == 4) {
									AttractK = 0.5;
								}
								if (atE == 2) {
									AttractK = 2;
								}
							}
							if (atB == 2) {
								if (atE == 1) {
									AttractK = 0.5;
								}
								if (atE == 5) {
									AttractK = 2;
								}
							}
							if (atB == 3) {
								if (atE == 5) {
									AttractK = 0.5;
								}
								if (atE == 4) {
									AttractK = 2;
								}
							}
							if (atB == 4) {
								if (atE == 3) {
									AttractK = 0.5;
								}
								if (atE == 1) {
									AttractK = 2;
								}
							}
							if (atB == 5) {
								if (atE == 2) {
									AttractK = 0.5;
								}
								if (atE == 3) {
									AttractK = 2;
								}
							}
							enemy[j]->beAttacked(int((float)(bullets[i]->GetBulletAttack())*AttractK));

						}
					}
				}
				else {
					Point point;
					point.x = player->getXpos();
					point.y = player->getYpos();
					int d = sqrt((bullets[i]->getXpos() - point.x)*(bullets[i]->getXpos() - point.x) + (bullets[i]->getYpos() - point.y)*(bullets[i]->getYpos() - point.y));
					if (d < player->getRadius() + bullets[i]->GetBulletRadius()) {
						bullets[i]->SetExist(false);
						player->setBlood(player->getBlood() - bullets[i]->GetBulletAttack());
					}
				}
			}
		}
	}
}

vector<Point> CMapAI::RoadRandom(int x, int y, int na) {
	road.clear();
	int xn = (x + y - 3696) / (150 * sqrt(2));
	int yn = (y - x + 2496) / (150 * sqrt(2));
	int a = 0;
	srand((unsigned)time(NULL));
	int i = 0;
	int m = na;
	int n = m;
	while (m != 0) {
		Point p = { xn,yn };
		road.push_back(p);
		m--;
		i++;
		int ran[4];
		for (int i = 0; i < 4; i++) {
			ran[i] = i;
		}
		for (int i = 0; i < 4; i++) {
			int m = rand() % 4;
			int a = ran[i];
			ran[i] = ran[m];
			ran[m] = a;
		}
		int k = 1;
		for (int h = 0; h < 4; h++) {
			if (a != 3 && ran[h] == 0 && k != 0 && xn + 1 < 38 && this->isWall[xn + 1][yn] == false) {
				k--;
				xn++;
				a = 1;
			}
			if (a != 4 && ran[h] == 1 && k != 0 && xn - 1 >= 0 && this->isWall[xn - 1][yn] == false) {
				k--;
				xn--;
				a = 2;
			}
			if (a != 1 && ran[h] == 2 && k != 0 && yn + 1 < 20 && this->isWall[xn][yn + 1] == false) {
				k--;
				yn++;
				a = 3;
			}
			if (a != 2 && ran[h] == 3 && k != 0 && yn - 1 >= 0 && this->isWall[xn][yn - 1] == false) {
				k--;
				yn--;
				a = 4;
			}
		}
	}
	for (int k = 0; k < i; k++) {
		float x0 = (float)this->road[k].x;
		float y0 = (float)this->road[k].y;
		this->road[k].x = int((x0 - y0) * 75 * sqrt(2) + 3096);
		this->road[k].y = int((x0 + y0) * 75 * sqrt(2) + 600);
	}
	return road;
}

Point CMapAI::EnemyCreatePoint() {
	Point point;
	//srand((unsigned)time(NULL));
	//int a = rand() % 38;
	//int b = rand() % 20;
	//while (this->isWall[a][b] != false) {
	//	a = rand() % 38;
	//	b = rand() % 20;
	//}
	while (enemyborn[bornpoint].x == -1)
	{
		bornpoint = (bornpoint + 1) % 100;
	}
	point.x = enemyborn[bornpoint].x;
	point.y = enemyborn[bornpoint].y;
	bornpoint = (bornpoint + 7) % 100;
	return point;
}