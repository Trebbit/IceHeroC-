#include "ParticleSystem.h"
#include <iostream>
#include <stdlib.h>

ParticleSystem::ParticleSystem() {}
ParticleSystem::ParticleSystem(int particlesCount, sf::Texture& particleTexture, sf::Vector2f spawnPos, float spawnSpeed,float lifeTime, sf::Vector2i minVelocity , sf::Vector2i maxVelocity)
{
	this->spawnSpeed = spawnSpeed;
	this->particlesCount = particlesCount;
	this->particleTexture = particleTexture;
	this->lifeTime = lifeTime;
	timer = spawnSpeed;
	this->minVelocity = minVelocity; 
	this->maxVelocity = maxVelocity; 
	this->startSize = startSize;
}

void ParticleSystem::UpdateParticles(float deltaTime, sf::Vector2f spawnPos, float dir,float burst) 
{
	if (timer <= 0.0f) 
	{
		timer = spawnSpeed;
		for (int i = 0; i < burst; i++) 
		{
			if (particlesCount > currentParticles) 
			{
						partricles.push_back(new Particle(spawnPos, sf::Vector2f((rand() % maxVelocity.x + minVelocity.x)*dir, (rand() % maxVelocity.y + minVelocity.y)), particleTexture, lifeTime));
						currentParticles++;
			}
		}
	}
	timer -= deltaTime;
	for (int i = 0; i < partricles.size(); i++) 
	{
		if (i < partricles.size()) 
		{
			if (partricles[i]->lifeTime < 0) 
			{
				oldPartricles.push_back(partricles[i]);
				delete partricles[i];
				partricles[i] = NULL;
				partricles.erase(partricles.begin() + i);
				currentParticles--;
			}
			else 
			{
				partricles[i]->pos += partricles[i]->vel*deltaTime;
				partricles[i]->sprite.setPosition(partricles[i]->pos);
				partricles[i]->lifeTime -= deltaTime;
				float scale = partricles[i]->lifeTime / lifeTime;
				if (scale < 0)
				{
					scale = 0;
				}
				partricles[i]->sprite.setScale(scale, scale);
			}
		}
	}

}
void ParticleSystem::Draw(sf::RenderWindow& window) 
{
	for (int i = 0; i < partricles.size(); i++) 
	{
		window.draw(partricles[i]->sprite);
	}
}
ParticleSystem::~ParticleSystem()
{
}
