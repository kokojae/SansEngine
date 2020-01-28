#pragma once

class TextureInfo;

class ObjectManager
{
private:
	LPD3DXSPRITE pSprite;

public:
	ObjectManager();
	~ObjectManager();

	// 싱글턴 반환 함수
	static ObjectManager& Instance()
	{
		static ObjectManager *instance = new ObjectManager;
		return *instance;
	}

	void Init();
	void Release();

	void Load(LPCWSTR pFile, int width, int height, LPDIRECT3DTEXTURE9* pTex);
	void Draw(LPDIRECT3DTEXTURE9 pTex, TextureInfo info, D3DXVECTOR2 position);
	bool Collision(D3DXVECTOR2 vPos, RECT rRect, D3DXVECTOR2 vOpponentPos, RECT rOpponentRect);

	LPD3DXSPRITE GetObjectSprite() { return pSprite; }
};

