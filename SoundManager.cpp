#include "DXUT.h"
#include "SoundManager.h"
#include "GameManager.h"
#include "SDKsound.h"


SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

void SoundManager::Init()
{
	m_cSoundManager = new CSoundManager;
	m_cSoundManager->Initialize(DXUTGetHWND(), DSSCL_PRIORITY);
	m_cSoundManager->SetPrimaryBufferFormat(2, 22050, 16);
}

void SoundManager::Release()
{
	delete m_cSoundManager;
}

void SoundManager::CreateSound(CSound ** sound, wchar_t* fileName)
{
	m_cSoundManager->Create(sound, fileName, 0, GUID_NULL);
}

void SoundManager::StartBGM(CSound * sound)
{
	sound->Play(0, DSBPLAY_LOOPING, GameManager::Instance().GetBGMVolume());
}

void SoundManager::StopBGM(CSound * sound)
{
	sound->Stop();
}

void SoundManager::EndBGM(CSound * sound)
{
	sound->Stop();
	sound->Reset();
}

void SoundManager::PlaySoundEffect(CSound * sound)
{
	sound->Play(0, NULL,GameManager::Instance().GetSoundEffectVolume());
}
