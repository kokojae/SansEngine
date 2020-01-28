#pragma once
#include "Stage.h"
#include "Enemy1.h"

class Stage1 : public Stage
{
private:
	Enemy1 enemy1[5];

public:
	Stage1();
	virtual ~Stage1();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	virtual void GameSetup();
	virtual void OptionUpdate();
	virtual void OptionRender();

	void Input();
};

