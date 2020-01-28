#include "DXUT.h"
#include "FontManager.h"


FontManager::FontManager()
{
}


FontManager::~FontManager()
{
}

void FontManager::Init()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &pSprite);

	D3DXCreateFont(DXUTGetD3D9Device(), 40, 0, FW_NORMAL, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Fixedsys", &pFont40);
	D3DXCreateFont(DXUTGetD3D9Device(), 80, 0, FW_NORMAL, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Fixedsys", &pFont80);
}

void FontManager::Release()
{
	if (pSprite != NULL)
		pSprite->Release();

	if (pFont40 != NULL)
		pFont40->Release();

	if (pFont80 != NULL)
		pFont80->Release();
}

void FontManager::Draw(int iSize, LPCWSTR pText, RECT rPos, UINT uiColor)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	switch (iSize)
	{
	case 40:
		pFont40->DrawTextW(pSprite, pText, -1, &rPos, DT_NOCLIP, uiColor);
		break;
	case 80:
		pFont80->DrawTextW(pSprite, pText, -1, &rPos, DT_NOCLIP, uiColor);
		break;
	}

	pSprite->End();
}
