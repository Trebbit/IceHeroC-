#pragma once
#include <SFML/\Graphics.hpp>

class Collider
{
public:
	Collider(sf::RectangleShape& body);
	~Collider();

	void Move(float dx, float dy) {
		body.move(dx,dy);
	}

	bool checkCollision(Collider other,sf::Vector2f& direction, float push, float offsetX, float offsetY, sf::Vector2f posOffset, sf::Vector2f intersect);

	sf::Vector2f GetPosition() {
		return body.getPosition();
	}

	sf::Vector2f GetHalfSize() {
		return body.getSize() / 2.0f;
	}

private:
	sf::RectangleShape& body;
};

