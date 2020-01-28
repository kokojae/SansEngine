#pragma once
#include "Scene.h"

class MainMenu : public Scene
{
private:
	LPDIRECT3DTEXTURE9 background[13];

	TextureInfo startButtonInfo;
	D3DXVECTOR2 startButtonPos;
	LPDIRECT3DTEXTURE9 startButton;
	RECT startButtonRect;

	TextureInfo optionButtonInfo;
	D3DXVECTOR2 optionButtonPos;
	LPDIRECT3DTEXTURE9 optionButton;
	RECT optionButtonRect;

	const int maxAniCount;
	int aniCount;
	float aniBetTime;

public:
	MainMenu();
	virtual ~MainMenu();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	void Animation();
	void Input();
};

