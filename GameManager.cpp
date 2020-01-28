#include "DXUT.h"
#include "GameManager.h"


GameManager::GameManager()
{
	gameState = GameState::MAINMENU;
	BGMVolume = 0;
	soundEffectVolume = 0;
}


GameManager::~GameManager()
{
}

void GameManager::Init()
{
	gameState = GameState::MAINMENU;

	mainMenu.Init();
	intro.Init();
	ending.Init();
	option.Init();

	stage1.Init();
	stage2.Init();
	stage3.Init();

	BGMVolume = 0;
	soundEffectVolume = 0;
}

void GameManager::Update()
{
	switch (gameState)
	{
	case GameManager::GameState::MAINMENU:	mainMenu.Update();	break;
	case GameManager::GameState::INTRO:		intro.Update();		break;
	case GameManager::GameState::STAGE1:	stage1.Update();	break;
	case GameManager::GameState::STAGE2:	stage2.Update();	break;
	case GameManager::GameState::STAGE3:	stage3.Update();	break;
	case GameManager::GameState::ENDING:	ending.Update();	break;
	case GameManager::GameState::OPTION:	option.Update();	break;
	}
}

void GameManager::Render()
{
	switch (gameState)
	{
	case GameManager::GameState::MAINMENU:	mainMenu.Render();	break;
	case GameManager::GameState::INTRO:	intro.Render();		break;
	case GameManager::GameState::STAGE1:	stage1.Render();	break;
	case GameManager::GameState::STAGE2:	stage2.Render();	break;
	case GameManager::GameState::STAGE3:	stage3.Render();	break;
	case GameManager::GameState::ENDING:	ending.Render();	break;
	case GameManager::GameState::OPTION:	option.Render();	break;
	}
}

void GameManager::Release()
{
	mainMenu.Release();
	intro.Release();
	ending.Release();
	option.Release();

	stage1.Release();
	stage2.Release();
	stage3.Release();
}

CSound * GameManager::GetBGM()
{
	switch (gameState)
	{
	case GameManager::GameState::MAINMENU:	return mainMenu.GetBGM();
	case GameManager::GameState::INTRO:		return intro.GetBGM();
	case GameManager::GameState::STAGE1:	return stage1.GetBGM();
	case GameManager::GameState::STAGE2:	return stage2.GetBGM();
	case GameManager::GameState::STAGE3:	return stage3.GetBGM();
	case GameManager::GameState::ENDING:	return ending.GetBGM();
	case GameManager::GameState::OPTION:	return option.GetBGM();
	default:					return nullptr;
	}
}

Player & GameManager::GetPlayer()
{
	switch (gameState)
	{
	case GameManager::GameState::STAGE1:	return stage1.GetPlayer();
	case GameManager::GameState::STAGE2:	return stage2.GetPlayer();
	case GameManager::GameState::STAGE3:	return stage3.GetPlayer();
	case GameManager::GameState::MAINMENU:
	case GameManager::GameState::INTRO:
	case GameManager::GameState::ENDING:
	case GameManager::GameState::OPTION:
	default:					return Player();
	}
}
