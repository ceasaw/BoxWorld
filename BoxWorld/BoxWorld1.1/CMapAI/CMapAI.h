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
	bool isWall[38][20];//ǽ���¼���飨trueΪǽ�壩
	CMapAI() {
		bornpoint = 0;
	}
	Point EnemyCreatePoint();//�ṩ�������ɵ�
	void WALLX_Y();//ǽ�����������¼��
	Point ChestCreate();//������ɱ���λ��;
	void ChestCollisionDetection();
	bool WALL_PECollision(int x, int y);//�ж�����/�����ߵ���һ����ǽ�Ƿ�ᷢ����ײ
	void WALLCollisionDetection();//ǽ����ײ���
	void BulletCollisionDetection();//�ӵ���ײ����ṩ����
	bool JudgeIsWall(int x, int y);//�ж��Ƿ�Ϊǽ
	vector<Point> RoadRandom(int x,int y,int na);/*���ô˺������ȡroad���鼴�ɻ��·����Ϣ��*/
};