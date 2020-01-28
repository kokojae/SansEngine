#pragma once
#include "TextureInfo.h"

class Character
{
protected:
	TextureInfo info;
	D3DXVECTOR2	vPos;				// ĳ������ ��ġ
	RECT	rRect;					// ĳ���� �ݶ��̴�

	float	fGravity;				// �߷�
	float	fSpeed;					// �̵��ӵ�
	float	fJump;					// ����
	bool	bCanJump;				// �������ΰ�
	bool	bLeft;					// ������ �����ִ°�

	float	fBulletTime;			// �߻� ����
	float	fBulletBetTime;			// �Ѿ� �߻� �� ���� �ð�
	int		iBulletCount;			// �ʿ� ź�� ������ �ְ��ϱ����� ����

	float	fAniTime;				// �ִϸ��̼� ��ȯ ����
	float	fAniBetTime;			// �ִϸ��̼� ��ȯ �� ���� �ð�
	int		iAniCount;				// ���� ����Ű���ִ� �ִϸ��̼� ������
	
	int		iHP;					// ���
	int		iAP;					// ���ݷ�

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

