#include "SoundManager.h"



SoundManager::SoundManager()
{
}
void SoundManager::SetVolume(float volume) 
{
	currentVolume = volume;
	for (int i = 0; i < sounds.size(); i++) {
		sounds[i]->setVolume(volume);
	}
}

SoundManager::~SoundManager()
{
}
