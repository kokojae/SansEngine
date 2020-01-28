#pragma once
#include "TextureInfo.h"
#include "Camera.h"
#include "Player.h"

class CSound;

class Stage
{
protected:
	LPDIRECT3DTEXTURE9 pBackTex;
	TextureInfo info;
	RECT rBackRect;

	CSound* BGM;

	Camera camera;

	Player player;

	bool bStageClear;
	bool bGameOver;
	bool showOption;
	bool startBGM;

public:
	Stage();
	virtual ~Stage();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	virtual void GameSetup() = 0;
	virtual void OptionUpdate() = 0;
	virtual void OptionRender() = 0;
	
	CSound* GetBGM() { return BGM; }
	Player& GetPlayer() { return player; }
};

