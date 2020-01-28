#include "DXUT.h"
#include "Ending.h"
#include "ObjectManager.h"
#include "GameManager.h"


Ending::Ending()
{
}


Ending::~Ending()
{
}

void Ending::Init()
{
	ObjectManager::Instance().Load(L"./resorce/background/scene/ending/deadscene.png", 1920, 1080, &background);
	info.size = D3DXVECTOR2(1920, 1080);
}

void Ending::Update()
{
}

void Ending::Render()
{
	ObjectManager::Instance().Draw(background, info, D3DXVECTOR2(0, 0));
}

void Ending::Release()
{
	background->Release();
}
