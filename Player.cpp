#include "DXUT.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Camera.h"
#include "SansEngine.h"


Player::Player() : iIdleMax(1), iMoveMax(10), iJumpMax(5), iAtkMax(5),
					fIdleAniTime(0.1f), fMoveAniTime(0.1f), fJumpAniTime(0.2f), fAtkAniTime(0.1f)
{
	for (int i = 0; i < 1; i++)
		lpIdleTex[i] = NULL;
	for (int i = 0; i < 1; i++)
		lpMoveTex[i] = NULL;
	for (int i = 0; i < 1; i++)
		lpJumpTex[i] = NULL;
	for (int i = 0; i < 1; i++)
		lpAtkTex[i] = NULL;

	eState = IDLE;

	iAniCount = 0;
	bCanJump = true;
}	
	
	
Player::~Player()
{
}

void Player::Init()
{
	char str[50] = { 0 };
	char num[5] = { 0 };
	wchar_t *fileName = nullptr;

	for (int i = 0; i < iIdleMax; i++)
	{
		sprintf_s(str, sizeof str, "\0");
		sprintf_s(num, sizeof num, "%d", i + 1);
		strcat_s(str, sizeof str, "./resorce/player/idle/");
		strcat_s(str, sizeof str, num);
		strcat_s(str, sizeof str, ".png");

		fileName = info.ConverCtoWC(str);

		ObjectManager::Instance().Load(fileName, 100, 100, &lpIdleTex[i]);
	}
	for (int i = 0; i < iMoveMax; i++)
	{
		sprintf_s(str, sizeof str, "\0");
		sprintf_s(num, sizeof num, "%d", i + 1);
		strcat_s(str, sizeof str, "./resorce/player/move/");
		strcat_s(str, sizeof str, num);
		strcat_s(str, sizeof str, ".png");

		fileName = info.ConverCtoWC(str);

		ObjectManager::Instance().Load(fileName, 100, 100, &lpMoveTex[i]);
	}
	for (int i = 0; i < iJumpMax; i++)
	{
		sprintf_s(str, sizeof str, "\0");
		sprintf_s(num, sizeof num, "%d", i + 1);
		strcat_s(str, sizeof str, "./resorce/player/jump/");
		strcat_s(str, sizeof str, num);
		strcat_s(str, sizeof str, ".png");

		fileName = info.ConverCtoWC(str);

		ObjectManager::Instance().Load(fileName, 100, 100, &lpJumpTex[i]);
	}
	for (int i = 0; i < iAtkMax; i++)
	{
		sprintf_s(str, sizeof str, "\0");
		sprintf_s(num, sizeof num, "%d", i + 1);
		strcat_s(str, sizeof str, "./resorce/player/attack/");
		strcat_s(str, sizeof str, num);
		strcat_s(str, sizeof str, ".png");

		fileName = info.ConverCtoWC(str);

		ObjectManager::Instance().Load(fileName, 100, 100, &lpAtkTex[i]);
	}

	vPos = { 500, (float)SCR_HEIGHT - rRect.bottom };
	rRect = { 0,0,100,100 };
	info.uiColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	fGravity = 100.0f;
	fSpeed = 500.0f;
	fJump = 0.0f;
	bCanJump = true;
	bLeft = false;

	fBulletTime = 1.0f;
	fBulletBetTime = DXUTGetElapsedTime();
	iBulletCount = 0;

	fAniTime = 0.1f;
	fAniBetTime = DXUTGetElapsedTime();
	iAniCount = 0;

	iHP = 100;
	iAP = 10;
}

void Player::Update()
{
	Gravity();
	Animation();
	InputKey();
	Jump();
	MoveLimit();
}

void Player::Render()
{
	switch (eState)
	{
	case Player::IDLE:
		if (bLeft)
			ObjectManager::Instance().Draw(lpIdleTex[iAniCount], info, vPos);
		else
			ObjectManager::Instance().Draw(lpIdleTex[iAniCount], info, vPos);
		break;
	case Player::MOVE:
		if (bLeft)
			ObjectManager::Instance().Draw(lpMoveTex[iAniCount], info, vPos);
		else
			ObjectManager::Instance().Draw(lpMoveTex[iAniCount], info, vPos);
		break;
	case Player::JUMP:
		if (bLeft)
			ObjectManager::Instance().Draw(lpJumpTex[iAniCount], info, vPos);
		else
			ObjectManager::Instance().Draw(lpJumpTex[iAniCount], info, vPos);
		break;
	case Player::ATTACK:
		if (bLeft)
			ObjectManager::Instance().Draw(lpAtkTex[iAniCount], info, vPos);
		else
			ObjectManager::Instance().Draw(lpAtkTex[iAniCount], info, vPos);
		break;
	default:
		break;
	}
}

void Player::Release()
{
	for (int i = 0; i < iIdleMax; i++)
		lpIdleTex[i]->Release();
	for (int i = 0; i < iMoveMax; i++)
		lpMoveTex[i]->Release();
	for (int i = 0; i < iJumpMax; i++)
		lpJumpTex[i]->Release();
	for (int i = 0; i < iAtkMax; i++)
		lpAtkTex[i]->Release();
}

void Player::InputKey()
{
	if (eState != ATTACK && bCanJump)
		eState = IDLE;

	// 공격
	if (GetAsyncKeyState('D') & 0x8000 && bCanJump)
	{
		Attack();
		if (eState != ATTACK)
			iAniCount = 0;
		eState = ATTACK;
	}
	// 점프
	if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && bCanJump)
	{
		bCanJump = false;
		eState = JUMP;
		iAniCount = 0;
		fJump = 1600.0f;
	}

	// 왼쪽
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		bLeft = true;
		info.scale = { 1,1 };
		Move();
		if (eState != ATTACK)
			eState = MOVE;
	}
	// 오른쪽
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		bLeft = false;
		info.scale = { -1,1 };
		Move();
		if (eState != ATTACK)
			eState = MOVE;
	}
}

void Player::Animation()
{
	fAniBetTime += DXUTGetElapsedTime();

	switch (eState)
	{
	case Player::IDLE:
		if (fAniBetTime >= fIdleAniTime)
		{
			fAniBetTime = DXUTGetElapsedTime();
			iAniCount++;
			if (iAniCount >= iIdleMax)
				iAniCount = 0;
		}
		break;
	case Player::MOVE:
		if (fAniBetTime >= fMoveAniTime)
		{
			fAniBetTime = DXUTGetElapsedTime();
			iAniCount++;
			if (iAniCount >= iMoveMax)
				iAniCount = 0;
		}
		break;
	case Player::JUMP:
		if (fAniBetTime >= fJumpAniTime)
		{
			fAniBetTime = DXUTGetElapsedTime();
			iAniCount++;
			if (iAniCount >= iJumpMax)
				iAniCount = 0;
		}
		break;
	case Player::ATTACK:
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

void Player::Move()
{
	if (bLeft)
		vPos.x -= fSpeed * DXUTGetElapsedTime();
	else
		vPos.x += fSpeed * DXUTGetElapsedTime();
}

void Player::Attack()
{
	eState = ATTACK;
	iAniCount = 0;
}

void Player::Jump()
{
	if (fJump > 0.0f)
	{
		vPos.y -= fJump * DXUTGetElapsedTime();
		fJump -= 30.0f;
	}
}
