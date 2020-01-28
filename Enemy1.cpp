#include "DXUT.h"
#include "Enemy1.h"
#include "ObjectManager.h"
#include "GameManager.h"


Enemy1::Enemy1() : iIdleMax(7), iMoveMax(2), iAtkMax(3),
					fIdleAniTime(0.2f), fMoveAniTime(0.1f), fAtkAniTime(0.1f)
{
	for (int i = 0; i < iIdleMax; i++)
		lpIdleTex[i] = nullptr;
	for (int i = 0; i < iMoveMax; i++)
		lpMoveTex[i] = nullptr;
	for (int i = 0; i < iAtkMax; i++)
		lpAtkTex[i] = nullptr;

	eState = State::IDLE;

	iAniCount = 0;
}


Enemy1::~Enemy1()
{
}

void Enemy1::Init()
{
	info.size = D3DXVECTOR2(100, 120);
	info.scale = D3DXVECTOR2(1.5f, 1.5f);
	vPos = D3DXVECTOR2(0, 0);
	rRect = RECT { 0, 0,
		static_cast<LONG>(info.size.x * info.scale.x),
		static_cast<LONG>(info.size.y * info.scale.y) };

	fGravity = 100.0f;
	fSpeed = 500.0f;
	bLeft = false;

	fBulletTime = 1.0f;
	fBulletBetTime = DXUTGetElapsedTime();
	iBulletCount = 0;

	fAniTime = 0.1f;
	fAniBetTime = DXUTGetElapsedTime();
	iAniCount = 0;

	iHP = 100;
	iAP = 10;

	rRader = RECT{ -300, -200, 300, 200 };

	isLockOn = false;

	char str[50] = { 0 };
	char num[5] = { 0 };
	wchar_t *fileName = nullptr;
	for (int i = 0; i < iIdleMax; i++)
	{
		sprintf_s(str, sizeof str, "\0");
		sprintf_s(num, sizeof num, "%d", i + 1);
		strcat_s(str, sizeof str, "./resorce/enemy/enemy1/idle/idle_");
		strcat_s(str, sizeof str, num);
		strcat_s(str, sizeof str, ".png");

		fileName = info.ConverCtoWC(str);

		ObjectManager::Instance().Load(fileName, info.size.x, info.size.y, &lpIdleTex[i]);
	}
	for (int i = 0; i < iMoveMax; i++)
	{
		sprintf_s(str, sizeof str, "\0");
		sprintf_s(num, sizeof num, "%d", i + 1);
		strcat_s(str, sizeof str, "./resorce/enemy/enemy1/move/move_");
		strcat_s(str, sizeof str, num);
		strcat_s(str, sizeof str, ".png");

		fileName = info.ConverCtoWC(str);

		ObjectManager::Instance().Load(fileName, info.size.x, info.size.y, &lpMoveTex[i]);
	}
	for (int i = 0; i < iAtkMax; i++)
	{
		sprintf_s(str, sizeof str, "\0");
		sprintf_s(num, sizeof num, "%d", i + 1);
		strcat_s(str, sizeof str, "./resorce/enemy/enemy1/attack/cannon_");
		strcat_s(str, sizeof str, num);
		strcat_s(str, sizeof str, ".png");

		fileName = info.ConverCtoWC(str);

		ObjectManager::Instance().Load(fileName, info.size.x, info.size.y, &lpAtkTex[i]);
	}

	eState = State::IDLE;

	iAniCount = 0;

}

void Enemy1::Update()
{
	Gravity();
	Animation();
	AI();
	MoveLimit();
}

void Enemy1::Render()
{
	switch (eState)
	{
	case Enemy1::IDLE:
		ObjectManager::Instance().Draw(lpIdleTex[iAniCount], info, vPos);
		break;
	case Enemy1::MOVE:
		ObjectManager::Instance().Draw(lpMoveTex[iAniCount], info, vPos);
		break;
	case Enemy1::ATTACK:
		ObjectManager::Instance().Draw(lpAtkTex[iAniCount], info, vPos);
		break;
	default:
		break;
	}
}

void Enemy1::Release()
{
	for (int i = 0; i < iIdleMax; i++)
		lpIdleTex[i]->Release();
	for (int i = 0; i < iMoveMax; i++)
		lpMoveTex[i]->Release();
	for (int i = 0; i < iAtkMax; i++)
		lpAtkTex[i]->Release();
}

void Enemy1::Animation()
{
	fAniBetTime += DXUTGetElapsedTime();

	switch (eState)
	{
	case Enemy1::IDLE:
		if (fAniBetTime >= fIdleAniTime)
		{
			fAniBetTime = DXUTGetElapsedTime();
			iAniCount++;
			if (iAniCount >= iIdleMax)
				iAniCount = 0;
		}
		break;
	case Enemy1::MOVE:
		if (fAniBetTime >= fMoveAniTime)
		{
			fAniBetTime = DXUTGetElapsedTime();
			iAniCount++;
			if (iAniCount >= iMoveMax)
				iAniCount = 0;
		}
		break;
	case Enemy1::ATTACK:
		if (fAniBetTime >= fAtkAniTime)
		{
			fAniBetTime = DXUTGetElapsedTime();
			iAniCount++;
			if (iAniCount >= iAtkMax)
				iAniCount = 0;
		}
		break;
	default:
		break;
	}
}

void Enemy1::Attack()
{
}

void Enemy1::Move()
{
}

void Enemy1::Move(D3DXVECTOR2 playerPos)
{
}

void Enemy1::AI()
{
	IsLockOn();
	if (isLockOn)	Move(GameManager::Instance().GetPlayer().GetPos());
	else			Move();

	if (ObjectManager::Instance().Collision(vPos, rRect,
		GameManager::Instance().GetPlayer().GetPos(), GameManager::Instance().GetPlayer().GetRect()))
		Attack();
}
