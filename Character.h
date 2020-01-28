#pragma once
#include "TextureInfo.h"

class Character
{
protected:
	TextureInfo info;
	D3DXVECTOR2	vPos;				// 캐릭터의 위치
	RECT	rRect;					// 캐릭터 콜라이더

	float	fGravity;				// 중력
	float	fSpeed;					// 이동속도
	float	fJump;					// 점프
	bool	bCanJump;				// 점프중인가
	bool	bLeft;					// 왼쪽을 보고있는가

	float	fBulletTime;			// 발사 간격
	float	fBulletBetTime;			// 총알 발사 후 지난 시간
	int		iBulletCount;			// 맵에 탄이 여러개 있게하기위한 변수

	float	fAniTime;				// 애니메이션 전환 간격
	float	fAniBetTime;			// 애니메이션 전환 후 지난 시간
	int		iAniCount;				// 현재 가리키고있는 애니메이션 프레임
	
	int		iHP;					// 목숨
	int		iAP;					// 공격력

public:
	Character();
	virtual ~Character();

	void Gravity();
	void MoveLimit();
	
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	virtual void Animation() = 0;

	virtual void Attack() = 0;

	void SetPos(D3DXVECTOR2 aPos) { vPos = aPos; }

	D3DXVECTOR2 GetPos() { return vPos; }
	RECT GetRect() { return rRect; }
};

