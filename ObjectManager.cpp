#include "DXUT.h"
#include "ObjectManager.h"
#include "TextureInfo.h"
#include "Camera.h"
#include "SansEngine.h"


ObjectManager::ObjectManager()
{
	pSprite = NULL;
}


ObjectManager::~ObjectManager()
{
}

void ObjectManager::Init()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &pSprite);
}

void ObjectManager::Release()
{
	if (pSprite != NULL)
		pSprite->Release();
}

void ObjectManager::Load(LPCWSTR pFile, int width, int height, LPDIRECT3DTEXTURE9 * pTex)
{
	D3DXCreateTextureFromFileEx(DXUTGetD3D9Device(), pFile, width, height, 0, false, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT,
		D3DX_DEFAULT, D3DX_DEFAULT, NULL, NULL, NULL, pTex);
}

void ObjectManager::Draw(LPDIRECT3DTEXTURE9 pTex, TextureInfo info, D3DXVECTOR2 position)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMATRIX mat, center, pos, scale, rotation;

	D3DXMatrixTranslation(&center, -info.center.x, -info.center.y, 0);
	D3DXMatrixTranslation(&pos, (int)position.x, (int)position.y, 0);
	D3DXMatrixScaling(&scale, info.scale.x, info.scale.y, 1);
	D3DXMatrixRotationZ(&rotation, D3DXToRadian(info.rotation));

	mat = center * scale * rotation * pos;

	pSprite->SetTransform(&mat);

	//도트겜일경우 사용	
	DXUTGetD3D9Device()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	DXUTGetD3D9Device()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	DXUTGetD3D9Device()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	RECT rect = RECT{ (LONG)(int)info.index * (LONG)info.size.x,0,(LONG)((int)info.index + 1) * (LONG)info.size.x,(LONG)info.size.y };

	pSprite->Draw(pTex, &rect, NULL, NULL, info.uiColor);

	pSprite->End();
}

bool ObjectManager::Collision(D3DXVECTOR2 vPos, RECT rRect, D3DXVECTOR2 vOpponentPos, RECT rOpponentRect)
{
	if (vPos.x + rRect.left <= vOpponentPos.x + rOpponentRect.right &&
		vPos.y + rRect.top <= vOpponentPos.y + rOpponentRect.bottom &&
		vPos.x + rRect.right >= vOpponentPos.x + rOpponentRect.left &&
		vPos.y + rRect.bottom >= vOpponentPos.y + rOpponentRect.top)
		return true;

	return false;
}
