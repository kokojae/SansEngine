#pragma once
#include "MainMenu.h"
#include "Intro.h"
#include "Ending.h"
#include "Option.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"

class Player;

class GameManager
{
public:
	enum class GameState { MAINMENU = 0, INTRO, STAGE1, STAGE2, STAGE3, ENDING, OPTION };

private:
	GameState gameState;

	MainMenu mainMenu;
	Intro intro;
	Ending ending;
	Option option;

	Stage1 stage1;
	Stage2 stage2;
	Stage3 stage3;

	LONG BGMVolume;
	LONG soundEffectVolume;

public:
	GameManager();
	~GameManager();

	// 싱글턴 반환 함수
	static GameManager& Instance()
	{
		static GameManager *instance = new GameManager;
		return *instance;
	}

	void Init();
	void Update();
	void Render();
	void Release();

	void SetGameState(GameState aState) { gameState = aState; }

	void Stage1Setup() { stage1.GameSetup(); }
	void Stage2Setup() { stage2.GameSetup(); }
	void Stage3Setup() { stage3.GameSetup(); }

	void SetBGMVolume(LONG volume) { BGMVolume = volume; }
	void SetsoundEffectVolume(LONG volume) { soundEffectVolume = volume; }

	LONG GetBGMVolume() { return BGMVolume; }
	LONG GetSoundEffectVolume() { return soundEffectVolume; }
	CSound* GetBGM();
	Player& GetPlayer();
};

