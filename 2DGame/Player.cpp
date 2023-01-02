#include "Player.h"
#include <iostream>

Player::Player(sf::Texture&texture, float switchTime, float speed, float jumpHeight, SoundManager& soundManager) : animation(texture, 0,17,32, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	facingRight = true;
	currentStartFrame = ffIdleAnimation;
	currentEndFrame = lfIdleAnimation;
	body.setSize(sf::Vector2f(75.0f, 75.0f));//size of player
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(220.0f, 220.0f);
	body.setTexture(&texture);
	texture.setSmooth(true);
	particleTexture.loadFromFile("Textures/druppel.png");
	particleTrailTexture.loadFromFile("Textures/trail.png");
	jumpBuffer.loadFromFile("Audio/jump.wav");
	jumpSound.setBuffer(jumpBuffer);
	soundManager.sounds.push_back(&jumpSound);
	wallHitBuffer.loadFromFile("Audio/wallHit.wav");
	wallHitSound.setBuffer(wallHitBuffer);
	soundManager.sounds.push_back(&wallHitSound);
	walkBuffer.loadFromFile("Audio/steps.wav");
	walkSound.setBuffer(walkBuffer);
	walkSound.setLoop(true);
	soundManager.sounds.push_back(&walkSound);
	
	particleSystem = ParticleSystem(200, particleTexture, sf::Vector2f(220.0f, 220.0f),0.3f,1.0f,sf::Vector2i(1.0f,1.0f), sf::Vector2i(100.0f, 100.0f));
	trailParticleSystem = ParticleSystem(500, particleTrailTexture, sf::Vector2f(220.0f, 220.0f), 0.001f, 1.0f, sf::Vector2i(-1.0f, 1.0f), sf::Vector2i(1.0f, 1.0f));
}


Player::~Player()
{
}
void Player::SetPosition(sf::Vector2f position) 
{
	body.setPosition(position);
}
void Player::SetScale(sf::Vector2f scale) 
{
	float oldSize = body.getSize().x;
	body.setSize(sf::Vector2f(75.0f*scale.x, 75.0f*scale.y ));
	body.setOrigin(body.getSize() / 2.0f);
	if(oldSize > body.getSize().x)
	body.setPosition(body.getPosition().x, body.getPosition().y + (oldSize - body.getSize().x));
}
//handles player movement and animation
void Player::Update(float deltaTime)
{
	velocity.x *= 0.5f;
	if (editorMode) 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
		{
			velocity.x -= speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)||sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
		{
			velocity.x += speed;
		}
		SetScale(sf::Vector2f(health / maxHealth, health / maxHealth));
	} 
	else
	{
		if (!inColdZone) //only reduce player size when he is not walking on snow
		{
			health -= deltaTime * 8;
		}
		SetScale(sf::Vector2f(health / maxHealth, health / maxHealth));
		if (facingRight) {
			velocity.x += speed;
		}
		else
		{
			velocity.x -= speed;
		}
	}
	float dir = 1.0f;
	if (facingRight) 
	{
		dir = -1.0f;
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)||sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))&&canJump&&grounded)
	{
		canJump = false;
		jumpSound.play();
		if (currentStartFrame != ffJumpAnimation) 
		{
			animation.currentImage = ffJumpAnimation;
			currentStartFrame = ffJumpAnimation;
			currentEndFrame = lfJumpAnimation;
			animation.loop = false;
		}
		velocity.y = -sqrtf(2.0f*981.0f *jumpHeight);
	}

	velocity.y += 981.0f *deltaTime; //apply gravity

	if (velocity.x < 4.0f&&velocity.x > -4.0f)
	{
		if (currentStartFrame != ffIdleAnimation) 
		{
			animation.loop = true;
			animation.currentImage = ffIdleAnimation;
			currentStartFrame = ffIdleAnimation;
			currentEndFrame = lfIdleAnimation;
		}
	}
	else
	{
		if (!grounded) 
		{
			walkSound.pause();
			if (currentStartFrame != ffJumpAnimation) 
			{
				//when not grounded set the player animation to the fall/jump animation
				animation.currentImage = ffJumpAnimation;
				currentStartFrame = ffJumpAnimation;
				currentEndFrame = lfJumpAnimation;
				animation.loop = false;
			}
		}
		else if (currentStartFrame != ffRunAnimation) 
		{
			walkSound.play();
			animation.loop = true;
			animation.currentImage = ffRunAnimation;
			currentStartFrame = ffRunAnimation;
			currentEndFrame = lfRunAnimation;
		}
		if (velocity.x > 0.0f)
		{
			facingRight = true;
		}
		else
		{
			facingRight = false;
		}
	}

	animation.Update(currentStartFrame,currentEndFrame, deltaTime, !facingRight);
	body.setTextureRect(animation.uvRect);
	//turn off the particles when standing in the snow
	if (inColdZone) 
	{
		particleSystem.UpdateParticles(deltaTime, body.getPosition() - sf::Vector2f(0, (health / maxHealth)*18.5f), dir, 0);
		trailParticleSystem.UpdateParticles(deltaTime, body.getPosition() + sf::Vector2f(0, (health / maxHealth)*18.5f), dir, 0);
	}
	else 
	{
		particleSystem.UpdateParticles(deltaTime, body.getPosition() - sf::Vector2f(0, (health / maxHealth)*18.5f), dir, 3);
		trailParticleSystem.UpdateParticles(deltaTime, body.getPosition() + sf::Vector2f(0, (health / maxHealth)*18.5f), dir, 1);
	}
	body.move(velocity*deltaTime);
}

void Player::Draw(sf::RenderWindow& window)
{
	trailParticleSystem.Draw(window);
	particleSystem.Draw(window);
	window.draw(body);
}

void Player::OnCollision(sf::Vector2f direction)
{
	//when hitting something on the x axis turn in the other direction
	if (direction.x < 0.0f) 
	{
		velocity.x = 0.0f;
		facingRight = false;
		if (!editorMode) {
			wallHitSound.play();
		}
	}
	else if (direction.x > 0.0f) 
	{
		velocity.x = 0.0f;
		facingRight = true;
		if (!editorMode) {
			wallHitSound.play();
		}
	}
	if (direction.y < 0.0f) 
	{
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f) 
	{
		velocity.y = 0.0f;
	}
}

