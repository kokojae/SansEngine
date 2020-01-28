#include "DXUT.h"
#include "Character.h"
#include "SansEngine.h"


Character::Character()
{	
	info.uiColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	vPos = D3DXVECTOR2(0, 0);
	rRect = { 0 };

	fGravity = 0.0f;
	fSpeed = 0.0f;
	fJump = 0.0f;
	bCanJump = false;
	bLeft = false;

	fBulletTime = 0.0f;
	fBulletBetTime = 0.0f;
	iBulletCount = 0;

	fAniTime = 0.0f;
	fAniBetTime = 0.0f;
	iAniCount = 0;

	iHP = 0;
	iAP = 0;
}

Character::~Character()
{
}

void Character::Gravity()
{
	vPos.y += fGravity * DXUTGetElapsedTime();
	fGravity += 30.0f;
}

void Character::MoveLimit()
{
	if (vPos.y >= SCR_HEIGHT - 100 - rRect.bottom)
	{
		vPos.y = SCR_HEIGHT - 100 - rRect.bottom;
		fGravity = 100.0f;
		fJump = 0.0f;
		bCanJump = true;
	}
}
