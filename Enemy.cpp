#include "DXUT.h"
#include "Enemy.h"
#include "ObjectManager.h"
#include "GameManager.h"


Enemy::Enemy()
{
	rRader = { 0 };
	isLockOn = false;
}


Enemy::~Enemy()
{
}

void Enemy::IsLockOn()
{
	if (ObjectManager::Instance().Collision(vPos, rRader,
		GameManager::Instance().GetPlayer().GetPos(), GameManager::Instance().GetPlayer().GetRect()))
		isLockOn = true;
	else isLockOn = false;
}
