#pragma once
#include "Character.h"

class Player : public Character
{
public:
	enum State { IDLE, MOVE, JUMP, ATTACK };

private:
	LPDIRECT3DTEXTURE9	lpIdleTex[1];
	LPDIRECT3DTEXTURE9	lpMoveTex[10];
	LPDIRECT3DTEXTURE9	lpJumpTex[5];
	LPDIRECT3DTEXTURE9	lpAtkTex[5];

	State		eState;

	int			iAniCount;

	const int	iIdleMax;
	const int	iMoveMax;
	const int	iJumpMax;
	const int	iAtkMax;

	const float	fIdleAniTime;
	const float	fMoveAniTime;
	const float	fJumpAniTime;
	const float	fAtkAniTime;

public:
	Player();
	virtual ~Player();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
	
	virtual void Animation();
	void InputKey();
	
	virtual void Attack();
	void Move();
	void Jump();
};

