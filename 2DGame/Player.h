#pragma once
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include "collider.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "SoundManager.h"
class Player
{
public:
	Player(sf::Texture&texture, float switchTime,float speed,float jumpHeight,SoundManager& soundManager);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	void SetPosition(sf::Vector2f position);
	void OnCollision(sf::Vector2f direction);
	void SetScale(sf::Vector2f scale);
	float health = 100.0f;
	float maxHealth = 100.0f;
	bool inColdZone = false;
	bool editorMode = false;
	bool facingRight;
	bool grounded;
	sf::Sound walkSound;
	sf::Vector2f GetPosition() {
		return body.getPosition();
	}
	Collider GetCollider() { return Collider(body); }
private:
	sf::RectangleShape body;
	Animation animation;
	float speed;
	int currentStartFrame = 0;
	int currentEndFrame = 18;
	int ffRunAnimation = 0;
	int lfRunAnimation = 17;
	int ffIdleAnimation = 18;
	int lfIdleAnimation = 29;
	int ffJumpAnimation = 30;
	int lfJumpAnimation = 31;
	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;
	sf::SoundBuffer jumpBuffer;
	sf::Sound jumpSound;
	sf::SoundBuffer wallHitBuffer;
	sf::Sound wallHitSound;
	sf::SoundBuffer walkBuffer;
	ParticleSystem particleSystem;
	ParticleSystem trailParticleSystem;
	sf::Texture particleTexture;
	sf::Texture particleTrailTexture;
};

