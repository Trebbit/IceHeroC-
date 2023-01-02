#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"
#include "Animation.h"
#include <iostream>
#include "ParticleSystem.h"
class Tile
{
public:
	Tile() {};
	Tile(sf::Texture& texture, sf::Vector2f size, sf::Vector2f position, int tileId, sf::Vector2f origin);
	Tile(const Tile &t2) { 
		position = t2.position; 
		tileId = t2.tileId;
		body.setSize(t2.body.getSize());
		body.setOrigin(t2.body.getOrigin());
		body.setTexture(t2.body.getTexture());
		body.setPosition(t2.position);
	}

	~Tile();
	int tileId;
	sf::Vector2f position;
	void SetPosition(sf::Vector2f newPosition);
	virtual void TileBehaviour(float deltaTime) {}
	virtual void Draw(sf::RenderWindow & window) {
		window.draw(body);
	}
	Collider GetCollider() { return Collider(body); }
	sf::RectangleShape body;
private:

};


class Coin : public Tile {

public:
	Coin();
	Coin(sf::Texture& texture, sf::Vector2f size, sf::Vector2f position, int tileId, sf::Vector2f origin);
	void PickedUp(sf::Vector2f newPosition);
	void TileBehaviour(float deltaTime) override
	{
			animation.Update(0, 15, deltaTime, false);
			body.setTextureRect(animation.uvRect);
	}
	void Draw(sf::RenderWindow & window) override {
		window.draw(body);
	}
private:
	Animation animation;
};


class Enemy : public Tile {
public:
	Enemy(sf::Texture& texture, sf::Vector2f size, sf::Vector2f position, int tileId, sf::Vector2f origin);
	float upSpeed = 175.0f;
	float downSpeed = 500.0f;
	void Draw(sf::RenderWindow & window) override {
		//particleSystem.Draw(window);
		window.draw(body);
	}
	void TileBehaviour(float deltaTime) override
	{
		//handles the enemies behaviour 
		if (tileId == 12) {
			//falling cube moving him up and down
			//particleSystem.UpdateParticles(deltaTime, body.getPosition(), 0.1f, 100);
			if ((body.getPosition().y < startPos.y + (75 * 3)) && !reached) {
				SetPosition(body.getPosition() + sf::Vector2f(0.0f, deltaTime * downSpeed));
				upSpeed = rand() % (200 -120 + 1) + 120;
			}
			else
			{
				reached = true;
				SetPosition(body.getPosition() - sf::Vector2f(0.0f, deltaTime * upSpeed));
				if (body.getPosition().y < startPos.y) {
					reached = false;
					downSpeed = rand() % (500 - 400 + 1) + 400;
				}
			}
		}
		else {
			//saw just some rotation
			body.rotate(body.getRotation() - (deltaTime));
		}
	}
private:
	sf::Texture particleTexture;
	sf::Vector2f startPos;
	bool reached = false;
	ParticleSystem particleSystem;
};

