
#include <SFML\Graphics.hpp>
#include "Particle.h"
#pragma once
class ParticleSystem
{
public:
	ParticleSystem(int particlesCount, sf::Texture& particleTexture, sf::Vector2f spawnPos,float spawnSpeed, float lifeTime, sf::Vector2i minVelocity=sf::Vector2i(-100.0f,-100.0f), sf::Vector2i maxVelocity = sf::Vector2i(100.0f, 100.0f));
	ParticleSystem();
	~ParticleSystem();
	void UpdateParticles(float deltaTime, sf::Vector2f spawnPos, float dir, float burst);
	void Draw(sf::RenderWindow& window);
	std::vector <Particle*> partricles;
	std::vector <Particle*> oldPartricles;
private:
	float spawnSpeed;
	float lifeTime;
	float timer;
	sf::Vector2i minVelocity;
	sf::Vector2i maxVelocity;
	float startSize;
	int particlesCount = 100;
	int currentParticles = 0;
	sf::Texture particleTexture;
};

