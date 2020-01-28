#pragma once
#include "Stage.h"

class Stage2 : public Stage
{
public:
	Stage2();
	virtual ~Stage2();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	virtual void GameSetup();
	virtual void OptionUpdate();
	virtual void OptionRender();
};

