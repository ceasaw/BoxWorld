#ifndef _BASIC_TOOLS_H_
#define _BASIC_TOOLS_H_

#include <afxwin.h>
#include <vector>
#include <map>

#define ENEMY_DIE_TIME_INTERVAL 1000
#define ENEMY_ANIMATION_INTERVAL_TIME 100
#define ENEMY_MOVE_DEVIATION 20
#define ENEMY_PIC_NUMBER 4          //一行怪物贴图的数量
#define ENEMY_PIC_SIZE_WIDTH 130
#define ENEMY_PIC_SIZE_HEIGTH 130


#define ENEMY_TYPE_MELEE_SHEEP  "sheep"


//敌人需要从文件中获得的属性
typedef struct file_monster_attribute
{
	int attack;
	int blood;
	int experience;
	float speed;
	int attackInterval;
	int attackRange;
	int detectionRange;
	int patrolRange;
}FILE_MONSTER_ATTRIBUTE;

enum class ENEMY_TYPE
{
	MELEEMONSTER1 = 0,
	MELEEMONSTER2,
	MELEEMONSTER3,
	RANGEMONSTER1,
	RANGEMONSTER2,
	RANGEMONSTER3,
	BLOCKMONSTER1,
	BLOCKMONSTER2,
	BOSS1,
	BOSS2,
	BOSS3
};

static std::map<ENEMY_TYPE, FILE_MONSTER_ATTRIBUTE> fileMonster = {
	{ENEMY_TYPE::MELEEMONSTER1,{1, 18, 3, 520, 1000, 100, 700, 6}},
	{ENEMY_TYPE::MELEEMONSTER2,{2, 22, 4, 540, 850, 120, 750, 7}},
	{ENEMY_TYPE::MELEEMONSTER3,{3, 26, 5, 560, 700, 140, 800, 8}},
	{ENEMY_TYPE::RANGEMONSTER1,{1, 13, 3, 350, 700, 400, 700, 6}},
	{ENEMY_TYPE::RANGEMONSTER2,{2, 16, 4, 370, 600, 450, 750, 7}},
	{ENEMY_TYPE::RANGEMONSTER3,{3, 19, 5, 390, 500, 500, 800, 8}},
	{ENEMY_TYPE::BLOCKMONSTER1,{5, 6, 4, 0, 2000, 150, 150, 0}},
	{ENEMY_TYPE::BLOCKMONSTER2,{5, 6, 4, 0, 2000, 150, 150, 0}},
	{ENEMY_TYPE::BOSS1, {3, 120, 10, 500, 800, 200, 1500, 0}},
	{ENEMY_TYPE::BOSS2, {4, 200, 20, 1000, 1200, 600, 1500, 0}},
	{ENEMY_TYPE::BOSS3, {5, 280, 10000, 1000, 1000, 600, 1500, 0}} };


typedef struct node
{
	float x;
	float y;
}Node;

typedef struct point 
{
	int x;
	int y;
}Point;

typedef struct bmpPic {
	CBitmap* picture;
	Point maskPos;
	Point spiritPos;
}BmpPic;

typedef struct picPos {
	BmpPic pic;
	Point coordinate;
}PicPos;

enum class MONSTER_TYPE
{
	LAVA = 9,
	DEMON = 10,
	DUCK = 3,
	RABIT = 4,
	MUSHROOM = 5,

};

enum class PLAYER_TYPE
{
	NON_ELEMENTAL = 0,
	METAL,
	WOOD,
	WATER,
	FIRE,
	EARTH
};



typedef struct enemy_attributes
{
	int xPos;
	int yPos;
	std::vector<Point> road;
	int attack; 
	int blood;
	int experience;
	float speed;
	int attackInterval;
	int attribute;
	int attackRange;
	int detectionRange;
	int patrolRange;
	int collisionRadius = 130;
	bool isExist;
	ENEMY_TYPE type;
}Enemy_Attributes;

enum class OBJECT_TYPE
{
	CBULLET,
	CENEMY,
	CPLAYER,
	CWALL
};


#endif // !_BASIC_TOOLS_H_
