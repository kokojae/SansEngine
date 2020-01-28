#pragma once
#include "Character.h"

class Enemy : public Character
{
protected:
	RECT rRader;	// 플레이어 탐지

	bool isLockOn;

public:
	Enemy();
	virtual ~Enemy();

	virtual void AI() = 0;
	virtual void IsLockOn();
};

