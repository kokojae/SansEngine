#pragma once

class CSoundManager;
class CSound;

class SoundManager
{
private:
	CSoundManager * m_cSoundManager;

public:
	SoundManager();
	~SoundManager();

	// 싱글턴 반환 함수
	static SoundManager& Instance()
	{
		static SoundManager *instance = new SoundManager;
		return *instance;
	}

	void Init();
	void Release();

	void CreateSound(CSound ** sound, wchar_t* fileName);

	void StartBGM(CSound* sound);
	void StopBGM(CSound* sound);
	void EndBGM(CSound* sound);

	void PlaySoundEffect(CSound* sound);
};

