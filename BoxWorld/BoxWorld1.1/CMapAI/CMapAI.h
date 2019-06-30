#pragma once
#include<afxwin.h>
#include"Wall.h"
#include"CEnemyAI/CEnemyAI.h"


class CMapAI 
{
public:
	WALL wall[38][20];
	Point enemyborn[100] = { -1,-1 };
	int bornpoint;
	vector<Point> road;
	bool isWall[38][20];//墙体记录数组（true为墙体）
	CMapAI() {
		bornpoint = 0;
	}
	Point EnemyCreatePoint();//提供怪物生成点
	void WALLX_Y();//墙体中心坐标记录。
	Point ChestCreate();//随机生成宝箱位置;
	void ChestCollisionDetection();
	bool WALL_PECollision(int x, int y);//判断人物/怪物走的下一步和墙是否会发生碰撞
	void WALLCollisionDetection();//墙体碰撞检测
	void BulletCollisionDetection();//子弹碰撞检测提供数据
	bool JudgeIsWall(int x, int y);//判断是否为墙
	vector<Point> RoadRandom(int x,int y,int na);/*调用此函数后读取road数组即可获得路径信息。*/
};