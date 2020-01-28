#pragma once
#include "Stage.h"

class Stage3 : public Stage
{
public:
	Stage3();
	virtual ~Stage3();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	virtual void GameSetup();
	virtual void OptionUpdate();
	virtual void OptionRender();
};

