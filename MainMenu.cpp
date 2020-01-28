#include "DXUT.h"
#include "MainMenu.h"
#include "ObjectManager.h"
#include "SoundManager.h"
#include "GameManager.h"
#include "MouseManager.h"

MainMenu::MainMenu() : maxAniCount(13)
{
}


MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
	info.size = D3DXVECTOR2(192, 108);
	info.scale = D3DXVECTOR2(10, 10);

	char str[50] = { 0 };
	char num[5] = { 0 };
	wchar_t *fileName = nullptr;

	for (int i = 0; i < maxAniCount; i++)
	{
		sprintf_s(str, sizeof str, "\0");
		sprintf_s(num, sizeof num, "%d", i + 1);
		strcat_s(str, sizeof str, "./resorce/background/scene/mainmenu/");
		strcat_s(str, sizeof str, num);
		strcat_s(str, sizeof str, ".png");

		fileName = info.ConverCtoWC(str);

		ObjectManager::Instance().Load(fileName, info.size.x, info.size.y, &background[i]);
	}	

	startButtonInfo.size = D3DXVECTOR2(50, 11);
	startButtonInfo.scale = D3DXVECTOR2(10, 10);
	startButtonPos = D3DXVECTOR2(50, 400);
	ObjectManager::Instance().Load(L"./resorce/background/scene/mainmenu/start_b.png", startButtonInfo.size.x, startButtonInfo.size.y, &startButton);
	startButtonRect = { 0, 0,
		static_cast<LONG>(startButtonInfo.size.x * startButtonInfo.scale.x),
		static_cast<LONG>(startButtonInfo.size.y * startButtonInfo.scale.y) };

	optionButtonInfo.size = D3DXVECTOR2(59, 11);
	optionButtonInfo.scale = D3DXVECTOR2(10, 10);
	optionButtonPos = D3DXVECTOR2(50, 550);
	ObjectManager::Instance().Load(L"./resorce/background/scene/mainmenu/option_b.png", optionButtonInfo.size.x, optionButtonInfo.size.y, &optionButton);
	optionButtonRect = { 0, 0,
		static_cast<LONG>(optionButtonInfo.size.x * optionButtonInfo.scale.x),
		static_cast<LONG>(optionButtonInfo.size.y * optionButtonInfo.scale.y) };

	SoundManager::Instance().CreateSound(&BGM, L"./resorce/sound/scene/mainmenu.wav");

	aniCount = 0;
	aniBetTime = DXUTGetElapsedTime();

	startBGM = false;
}

void MainMenu::Update()
{
	if (!startBGM)
	{
		SoundManager::Instance().StartBGM(BGM);
		startBGM = !startBGM;
	}

	Animation();
	Input();
}

void MainMenu::Render()
{
	ObjectManager::Instance().Draw(background[aniCount], info, D3DXVECTOR2(0, 0));
	ObjectManager::Instance().Draw(startButton, startButtonInfo, startButtonPos);
	ObjectManager::Instance().Draw(optionButton, optionButtonInfo, optionButtonPos);
}

void MainMenu::Release()
{
	optionButton->Release();
	startButton->Release();
	for (int i = 0; i < maxAniCount; i++)
		background[i]->Release();
}

void MainMenu::Animation()
{
	aniBetTime += DXUTGetElapsedTime();

	if (aniBetTime >= 0.15f)
	{
		aniBetTime = DXUTGetElapsedTime();
		aniCount++;
		if (aniCount >= maxAniCount)
			aniCount = 0;
	}
}

void MainMenu::Input()
{
	if (MouseManager::Instance().GetMsg() == WM_LBUTTONDOWN)
	{
		if (ObjectManager::Instance().Collision(startButtonPos, startButtonRect,
			D3DXVECTOR2(MouseManager::Instance().GetXPos(), MouseManager::Instance().GetYPos()), RECT{0,0,0,0}))
		{
			GameManager::Instance().Stage1Setup();
			GameManager::Instance().SetGameState(GameManager::GameState::STAGE1);
			SoundManager::Instance().EndBGM(BGM);
		}

		if (ObjectManager::Instance().Collision(optionButtonPos, optionButtonRect,
			D3DXVECTOR2(MouseManager::Instance().GetXPos(), MouseManager::Instance().GetYPos()), RECT{ 0,0,0,0 }))
		{
			GameManager::Instance().SetGameState(GameManager::GameState::OPTION);
		}
	}
}
