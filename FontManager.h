#pragma once
class FontManager
{
private:
	LPD3DXSPRITE pSprite;
	LPD3DXFONT pFont40;
	LPD3DXFONT pFont80;

public:
	FontManager();
	~FontManager();

	// 싱글턴 반환 함수
	static FontManager& Instance()
	{
		static FontManager *instance = new FontManager;
		return *instance;
	}

	void Init();
	void Release();

	void Draw(int iSize, LPCWSTR pText, RECT rPos, UINT uiColor);
};

