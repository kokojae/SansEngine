#pragma once
#include "Enemy.h"

class Enemy1 : public Enemy
{
public:
	enum State { IDLE, MOVE, ATTACK };

private:
	LPDIRECT3DTEXTURE9	lpIdleTex[7];
	LPDIRECT3DTEXTURE9	lpMoveTex[2];
	LPDIRECT3DTEXTURE9	lpAtkTex[3];

	State		eState;

	int			iAniCount;

	const int	iIdleMax;
	const int	iMoveMax;
	const int	iAtkMax;

	const float	fIdleAniTime;
	const float	fMoveAniTime;
	const float	fAtkAniTime;

public:
	Enemy1();
	virtual ~Enemy1();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	virtual void Animation();

	virtual void Attack();
	void Move();
	void Move(D3DXVECTOR2 playerPos);

	virtual void AI();
};

