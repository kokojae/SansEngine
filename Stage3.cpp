#include "DXUT.h"
#include "Stage3.h"
#include "ObjectManager.h"
#include "GameManager.h"


Stage3::Stage3()
{
}


Stage3::~Stage3()
{
}

void Stage3::Init()
{
	ObjectManager::Instance().Load(L"./resorce/background/stage/stage3/stage3.png", 1920, 1080, &pBackTex);
	info.size = D3DXVECTOR2(1920, 1080);
	player.Init();
}

void Stage3::Update()
{
	player.Update();
}

void Stage3::Render()
{
	ObjectManager::Instance().Draw(pBackTex, info, D3DXVECTOR2(0, 0));
	player.Render();
}

void Stage3::Release()
{
	player.Release();
	pBackTex->Release();
}

void Stage3::GameSetup()
{
}

void Stage3::OptionUpdate()
{
}

void Stage3::OptionRender()
{
}
