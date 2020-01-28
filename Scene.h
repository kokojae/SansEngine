#pragma once
#include "TextureInfo.h"

class CSound;

class Scene
{
protected:	
	TextureInfo info;

	CSound* BGM;

	bool startBGM;

public:
	Scene();
	virtual ~Scene();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
	
	CSound* GetBGM() { return BGM; }
};

