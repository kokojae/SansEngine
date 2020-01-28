#include "DXUT.h"
#include "Intro.h"
#include "ObjectManager.h"
#include "GameManager.h"


Intro::Intro()
{
}


Intro::~Intro()
{
}

void Intro::Init()
{
	ObjectManager::Instance().Load(L"./resorce/background/scene/intro/intro.png", 1920, 1080, &background);
	info.size = D3DXVECTOR2(1920, 1080);
}

void Intro::Update()
{
}

void Intro::Render()
{
	ObjectManager::Instance().Draw(background, info, D3DXVECTOR2(0, 0));
}

void Intro::Release()
{
	background->Release();
}
