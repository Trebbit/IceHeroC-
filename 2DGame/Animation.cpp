#include "Animation.h"
#include <iostream>


Animation::Animation(sf::Texture&texture, int firstFrame, int lastFrame, int imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0;
	currentImage = 0;

	uvRect.width = texture.getSize().x / float(imageCount);
	uvRect.height = texture.getSize().y;
}


Animation::~Animation()
{
}
//handles the animation (first frame of wanted animation,last frame of the wanted animation,deltatime,moving left)
void Animation::Update(int startFrame, int lastFrame, float deltaTime, bool flip)
{
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage++;
		if (currentImage  > lastFrame) {
			if (!loop) {
				currentImage = lastFrame;
			}
			else {
				currentImage = startFrame;
			}
		}
	}
	//checks which direction is moving and flips the sprite if needed
	if (flip)
	{
		
		uvRect.left = (currentImage + 1) * abs(uvRect.width);
		if (uvRect.left < 0) {
			uvRect.left = -uvRect.left;
		}
		uvRect.width = -abs(uvRect.width);
	}
	else
	{
		uvRect.left = currentImage * uvRect.width;
		if (uvRect.left < 0) {
			uvRect.left = -uvRect.left;
		}
		uvRect.width = abs(uvRect.width);

	}
}