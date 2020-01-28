#pragma once
#include "Scene.h"

class Option : public Scene
{
private:
	LPDIRECT3DTEXTURE9 background;

	TextureInfo backButtonInfo;
	D3DXVECTOR2 backButtonPos;
	LPDIRECT3DTEXTURE9 backButton;
	RECT backButtonRect;

	TextureInfo VolUpButtonInfo;
	D3DXVECTOR2 VolUpButtonPos;
	LPDIRECT3DTEXTURE9 VolUpButton;
	RECT VolUpButtonRect;

	TextureInfo VolDownButtonInfo;
	D3DXVECTOR2 VolDownButtonPos;
	LPDIRECT3DTEXTURE9 VolDownButton;
	RECT VolDownButtonRect;

public:
	Option();
	virtual ~Option();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	void Input();
};

