#include "DXUT.h"
#include "Stage1.h"
#include "ObjectManager.h"
#include "GameManager.h"
#include "SoundManager.h"


Stage1::Stage1()
{
}


Stage1::~Stage1()
{
}

void Stage1::Init()
{
	ObjectManager::Instance().Load(L"./resorce/background/stage/stage1/stage1.png", 1920, 1080, &pBackTex);
	info.size = D3DXVECTOR2(1920, 1080);

	SoundManager::Instance().CreateSound(&BGM, L"./resorce/sound/scene/stage1.wav");

	player.Init();

	bStageClear = false;
	bGameOver = false;
	showOption = false;
	startBGM = false;

	for (int i = 0; i < 5; i++)
	{
		enemy1[i].Init();
		enemy1[i].SetPos(D3DXVECTOR2(500 * i, 500));
	}
}

void Stage1::Update()
{
	if (!startBGM)
	{
		SoundManager::Instance().StartBGM(BGM);
		startBGM = !startBGM;
	}

	if (showOption)
		OptionUpdate();
	else
	{
		player.Update();
		camera.MoveCamera();
		for (int i = 0; i < 5; i++)
		{
			enemy1[i].Update();
		}
	}
}

void Stage1::Render()
{
	ObjectManager::Instance().Draw(pBackTex, info, D3DXVECTOR2(0, 0));
	player.Render();
	for (int i = 0; i < 5; i++)
	{
		enemy1[i].Render();
	}

	if (showOption)
		OptionRender();
}

void Stage1::Release()
{
	for (int i = 0; i < 5; i++)
	{
		enemy1[i].Release();
	}
	player.Release();
	pBackTex->Release();
}

void Stage1::GameSetup()
{
}

void Stage1::OptionUpdate()
{
}

void Stage1::OptionRender()
{
}

void Stage1::Input()
{
	if (GetAsyncKeyState('q') & 0x8000)
	{
		if (showOption)
			showOption = false;
		else
			showOption = true;
	}
}
