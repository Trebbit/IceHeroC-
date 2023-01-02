#pragma once

#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
class SoundManager
{
public:
	void SetVolume(float volume);
	float currentVolume = 100;
	std::vector<sf::Sound*> sounds;
	SoundManager();
	~SoundManager();
};

