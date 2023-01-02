#pragma once
#include <SFML\Graphics.hpp>
class Animation
{
public:
	Animation(sf::Texture&texture, int firstFrame,int lastFrame, int imageCount,float switchTime);
	~Animation();

	void Update(int startFrame, int lastFrame, float deltatime, bool flip);

public:
	sf::IntRect uvRect;
	int currentImage;
	bool loop = true;
private:
	int imageCount;
	float totalTime;
	float switchTime;
};

