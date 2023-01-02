#pragma once
#include <SFML\Graphics.hpp>
class Particle
{
public:
	Particle(sf::Vector2f pos,sf::Vector2f vel,sf::Texture& texture, float lifeTime = 3.0f);
	~Particle();
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::Sprite  sprite;
	sf::Texture texture;
	float lifeTime = 3;
};

