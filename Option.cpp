#include "DXUT.h"
#include "Option.h"
#include "ObjectManager.h"
#include "SoundManager.h"
#include "GameManager.h"
#include "MouseManager.h"
#include "FontManager.h"


Option::Option()
{
}


Option::~Option()
{
}

void Option::Init()
{
	ObjectManager::Instance().Load(L"./resorce/background/scene/option/option.png", 1920, 1080, &background);
	info.size = D3DXVECTOR2(1920, 1080);

	backButtonInfo.size = D3DXVECTOR2(200, 200);
	backButtonInfo.scale = D3DXVECTOR2(1, 1);
	backButtonPos = D3DXVECTOR2(10, 10);
	ObjectManager::Instance().Load(L"./resorce/background/scene/option/backmainmenu.png", backButtonInfo.size.x, backButtonInfo.size.y, &backButton);
	backButtonRect = { 0, 0,
		static_cast<LONG>(backButtonInfo.size.x * backButtonInfo.scale.x),
		static_cast<LONG>(backButtonInfo.size.y * backButtonInfo.scale.y) };

	VolUpButtonInfo.size = D3DXVECTOR2(100, 100);
	VolUpButtonInfo.scale = D3DXVECTOR2(1, 1);
	VolUpButtonPos = D3DXVECTOR2(500, 300);
	ObjectManager::Instance().Load(L"./resorce/background/scene/option/volumeup.png", VolUpButtonInfo.size.x, VolUpButtonInfo.size.y, &VolUpButton);
	VolUpButtonRect = { 0, 0,
		static_cast<LONG>(VolUpButtonInfo.size.x * VolUpButtonInfo.scale.x),
		static_cast<LONG>(VolUpButtonInfo.size.y * VolUpButtonInfo.scale.y) };

	VolDownButtonInfo.size = D3DXVECTOR2(100, 100);
	VolDownButtonInfo.scale = D3DXVECTOR2(1, 1);
	VolDownButtonPos = D3DXVECTOR2(10, 300);
	ObjectManager::Instance().Load(L"./resorce/background/scene/option/volumedown.png", VolDownButtonInfo.size.x, VolDownButtonInfo.size.y, &VolDownButton);
	VolDownButtonRect = { 0, 0,
		static_cast<LONG>(VolDownButtonInfo.size.x * VolDownButtonInfo.scale.x),
		static_cast<LONG>(VolDownButtonInfo.size.y * VolDownButtonInfo.scale.y) };

	BGM = GameManager::Instance().GetBGM();

	startBGM = false;
}

void Option::Update()
{
	Input();
}

void Option::Render()
{
	ObjectManager::Instance().Draw(background, info, D3DXVECTOR2(0, 0));
	ObjectManager::Instance().Draw(backButton, backButtonInfo, backButtonPos);
	ObjectManager::Instance().Draw(VolUpButton, VolUpButtonInfo, VolUpButtonPos);
	ObjectManager::Instance().Draw(VolDownButton, VolDownButtonInfo, VolDownButtonPos);
	
	wchar_t buf[255];
	ZeroMemory(buf, sizeof buf);
	swprintf_s(buf, L"%d", GameManager::Instance().GetBGMVolume());
	FontManager::Instance().Draw(40, buf, RECT{ 0, 0 }, 0xffffffff);
}

void Option::Release()
{
	VolDownButton->Release();
	VolUpButton->Release();
	backButton->Release();
	background->Release();
}

void Option::Input()
{
	if (MouseManager::Instance().GetMsg() == WM_LBUTTONDOWN)
	{
		if (ObjectManager::Instance().Collision(backButtonPos, backButtonRect,
			D3DXVECTOR2(MouseManager::Instance().GetXPos(), MouseManager::Instance().GetYPos()), RECT{ 0,0,0,0 }))
		{
			GameManager::Instance().SetGameState(GameManager::GameState::MAINMENU);
		}
		if (ObjectManager::Instance().Collision(VolUpButtonPos,VolUpButtonRect,
			D3DXVECTOR2(MouseManager::Instance().GetXPos(), MouseManager::Instance().GetYPos()), RECT{ 0,0,0,0 }))
		{
			SoundManager::Instance().StopBGM(BGM);
			GameManager::Instance().SetBGMVolume(GameManager::Instance().GetBGMVolume() + 1000);
			if (GameManager::Instance().GetBGMVolume() > 0)
				GameManager::Instance().SetBGMVolume(0);
			SoundManager::Instance().StartBGM(BGM);
		}
		if (ObjectManager::Instance().Collision(VolDownButtonPos, VolDownButtonRect,
			D3DXVECTOR2(MouseManager::Instance().GetXPos(), MouseManager::Instance().GetYPos()), RECT{ 0,0,0,0 }))
		{
			SoundManager::Instance().StopBGM(BGM);
			GameManager::Instance().SetBGMVolume(GameManager::Instance().GetBGMVolume() - 1000);
			if (GameManager::Instance().GetBGMVolume() < -10000 )
				GameManager::Instance().SetBGMVolume(-10000);
			SoundManager::Instance().StartBGM(BGM);
		}
	}
}
