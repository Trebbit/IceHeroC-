#include "Tile.h"
#include <iostream>

Tile::Tile(sf::Texture& texture, sf::Vector2f size, sf::Vector2f position, int tileId, sf::Vector2f origin) 
{
	this->tileId = tileId;
	body.setSize(size);
	body.setOrigin(origin);
	body.setTexture(&texture);
	body.setPosition(position);
	this->position = position;
}

Coin::Coin(sf::Texture& texture, sf::Vector2f size, sf::Vector2f position, int tileId, sf::Vector2f origin): 
	animation(texture, 0, 15, 16, 0.05f)
{
	this->tileId = tileId;
	body.setSize(size);
	body.setOrigin(origin);
	body.setTexture(&texture);
	body.setPosition(position);
	this->position = position;
}
Enemy::Enemy(sf::Texture& texture, sf::Vector2f size, sf::Vector2f position, int tileId, sf::Vector2f origin)
{
	this->tileId = tileId;
	body.setSize(size);
	body.setOrigin(origin);
	body.setTexture(&texture);
	body.setPosition(position);
	this->position = position;
	startPos = body.getPosition();
	particleTexture.loadFromFile("Textures/druppel.png");
	particleSystem = ParticleSystem(200, particleTexture, sf::Vector2f(220.0f, 220.0f), 1.3f, 1.0f, sf::Vector2i(1.0f, 1.0f), sf::Vector2i(200.0f, 200.0f));

}
Tile::~Tile()
{
}


void Coin::PickedUp(sf::Vector2f newPosition) {
	SetPosition(newPosition);
}
void Tile::SetPosition(sf::Vector2f newPosition) 
{
	body.setPosition(newPosition);
}

