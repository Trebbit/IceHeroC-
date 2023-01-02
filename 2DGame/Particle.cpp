#include "Particle.h"



Particle::Particle(sf::Vector2f pos, sf::Vector2f vel, sf::Texture& texture,float lifeTime)
{
	this->pos = pos;
	this->vel = vel;
	this->sprite =  sf::Sprite();
	this->texture = texture;
	this->lifeTime = lifeTime;
	texture.setSmooth(true);
	sprite.setPosition(pos);
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}


Particle::~Particle()
{
}
