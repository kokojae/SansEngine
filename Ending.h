#pragma once
#include "Scene.h"

class Ending : public Scene
{
private:
	LPDIRECT3DTEXTURE9 background;

public:
	Ending();
	virtual ~Ending();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
};

