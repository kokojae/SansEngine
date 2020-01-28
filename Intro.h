#pragma once
#include "Scene.h"

class Intro : public Scene
{
private:
	LPDIRECT3DTEXTURE9 background;

public:
	Intro();
	virtual ~Intro();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
};

