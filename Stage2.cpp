#include "DXUT.h"
#include "Stage2.h"
#include "ObjectManager.h"
#include "GameManager.h"


Stage2::Stage2()
{
}


Stage2::~Stage2()
{
}

void Stage2::Init()
{
	ObjectManager::Instance().Load(L"./resorce/background/stage/stage2/stage2.png", 1920, 1080, &pBackTex);
	info.size = D3DXVECTOR2(1920, 1080);
	player.Init();
}

void Stage2::Update()
{
	player.Update();
}

void Stage2::Render()
{
	ObjectManager::Instance().Draw(pBackTex, info, D3DXVECTOR2(0, 0));
	player.Render();
}

void Stage2::Release()
{
	player.Release();
	pBackTex->Release();
}

void Stage2::GameSetup()
{
}

void Stage2::OptionUpdate()
{
}

void Stage2::OptionRender()
{
}
