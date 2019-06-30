#include "ResourceAllocator/ResourceAllocator.h"

ResourceAllocator::ResourceAllocator()
{
	this->bossBmp = new CBitmap();
	this->gunBmp = new CBitmap();
	this->monstersBmp = new CBitmap();
	this->stoneBmp = new CBitmap();
	this->mapBmp = new CBitmap();
	this->bulletBmp = new CBitmap();
	this->heartBmp = new CBitmap();
	this->treasureBmp = new CBitmap();
	this->shadowBmp = new CBitmap();
	this->monsterBloodBmp = new CBitmap();
	this->bossBloodBmp = new CBitmap();
	this->monsterBulletBmp = new CBitmap();
	this->treasureBmp = new CBitmap();

	bossBmp->m_hObject = LoadImage(NULL, "BMPResources\\Boss.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	gunBmp->m_hObject = LoadImage(NULL, "BMPResources\\gun.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	monstersBmp->m_hObject = LoadImage(NULL, "BMPResources\\monster.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	stoneBmp->m_hObject = LoadImage(NULL, "BMPResources\\stone.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	mapBmp->m_hObject = LoadImage(NULL, "BMPResources\\map2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bulletBmp->m_hObject = LoadImage(NULL, "BMPResources\\mybullet.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	heartBmp->m_hObject = LoadImage(NULL, "BMPResources\\heart.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bossBloodBmp->m_hObject = LoadImage(NULL, "BMPResources\\bossBlood.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	treasureBmp->m_hObject = LoadImage(NULL, "BMPResources\\treasure.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	monsterBloodBmp->m_hObject = LoadImage(NULL, "BMPResources\\monsterBlood.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	shadowBmp->m_hObject = LoadImage(NULL, "BMPResources\\shadow.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	monsterBulletBmp->m_hObject = LoadImage(NULL, "BMPResources\\bullet.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	InitMaps();
}

void ResourceAllocator::InitMaps()
{
	this->boss = {
	{"GrassPigFrontLeft", {0, 0}}, {"GrassPigFrontRight", {0, 130}}, {"GrassPigBackLeft", {0, 390}}, {"GrassPigBackRight",{0, 260}},
	{"LavaFrontLeft", {0, 520}}, {"LavaFrontRight", {0, 650}}, {"LavaBackLeft", {0, 910}}, {"LavaBackRight", {0, 780}},
	{"DemonFrontLeft", {0, 1040}}, {"DemonFrontRight", {0, 1170}}, {"DemonBackLeft", {0, 1430}}, {"DemonBackRight", {0, 1300}} };

	this->character = { {"CharactorFront", {0, 0}}, {"CharactorBack", {0, 130}} };

	this->meleeMonster = {
	{"Skeleton", {0, 260}}, {"Pig", {0, 390}}, {"Sheep", {0, 520}}, {"Panda", {0, 650}} };

	this->rangeMonster = {
	{"Skeleton", {0, 260}}, {"Duck", {0, 780}}, {"Rabit", {0, 910}}, {"Mushroom", {0, 1040}} };

	this->blockMonster = {
	{"Skeleton", {0, 260}}, {"Nut", {0, 1170}}, {"BoxOpen", {0, 1300}}, {"BoxClose", {0, 1430}} };

	this->stone = { {"HighStone", {0, 0}}, {"ShortStone", {0, 212}} };

	this->gun = {
	{"NonElemental", {0, 0}}, {"Metal", {0, 305}},
	{"Wood", {0, 208}}, {"Water", {305, 208}},
	{"Fire", {0, 416}}, {"Earth", {305, 416}},
	{"Mask", {0, 624}} };

	this->bullet = {
	{"NonElemental", {0, 0}}, {"Metal", {0, 30}},
	{"Wood", {0, 60}}, {"Water", {0, 90}},
	{"Fire", {0, 120}}, {"Earth", {0, 150}},
	{"Mask", {0, 180}} };

	this->monsterBullet = {
	{"LavaBullet", {0,0}},{"DemonBullet", {0, 30}},
	{"DuckBullet", {0, 60}},{"MushroomBullet", {0, 90}},{"RabitBullet", {0, 120}} };

	this->shadow = {
	{"GoldShadow", {0,0}}, {"WoodShadow", {0, 130}}, {"WaterShadow", {0, 260}},
	{"FireShadow", {0, 390}}, {"EarthShadow", {0, 520}}, {"MaskShadow", {0, 650}} };
}

CBitmap * ResourceAllocator::GetMonsterBmp()
{
	return this->monstersBmp;
}

CBitmap * ResourceAllocator::GetBossBmp()
{
	return this->bossBmp;
}

CBitmap * ResourceAllocator::GetGunBmp()
{
	return this->gunBmp;
}

CBitmap * ResourceAllocator::GetStoneBmp()
{
	return this->stoneBmp;
}

CBitmap * ResourceAllocator::GetMapBmp()
{
	return this->mapBmp;
}

CBitmap * ResourceAllocator::GetBulletBmp()
{
	return this->bulletBmp;
}

CBitmap * ResourceAllocator::GetHeartBmp()
{
	return this->heartBmp;
}

CBitmap * ResourceAllocator::GetMonsterBloodBmp()
{
	return this->monsterBloodBmp;
}

CBitmap * ResourceAllocator::GetBossBloodBmp()
{
	return this->bossBloodBmp;
}

CBitmap * ResourceAllocator::GetMonsterBulletBmp()
{
	return this->monsterBulletBmp;
}

CBitmap * ResourceAllocator::GetTreasuretBmp()
{
	return treasureBmp;
}

CBitmap * ResourceAllocator::GetShadowBmp()
{
	return shadowBmp;
}

std::map<CString, Point>& ResourceAllocator::GetBossPosMap()
{
	return this->boss;
}

std::map<CString, Point>& ResourceAllocator::GetMeleeMonsterPosMap()
{
	return this->meleeMonster;
}

std::map<CString, Point>& ResourceAllocator::GetRangeMonsterPosMap()
{
	return this->rangeMonster;
}

std::map<CString, Point>& ResourceAllocator::GetBlockMonsterPosMap()
{
	return this->blockMonster;
}

std::map<CString, Point>& ResourceAllocator::GetCharacterPosMap()
{
	return this->character;
}

std::map<CString, Point>& ResourceAllocator::GetGunPosMap()
{
	return this->gun;
}

std::map<CString, Point>& ResourceAllocator::GetStonePosMap()
{
	return this->stone;
}

std::map<CString, Point>& ResourceAllocator::GetBulletPosMap()
{
	return this->bullet;
}

std::map<CString, Point>& ResourceAllocator::GetMonsterBulletPosMap()
{
	return this->monsterBullet;
}

std::map<CString, Point>& ResourceAllocator::GetShadowPosMap()
{
	return this->shadow;
}


