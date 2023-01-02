#include "Collider.h"
#include <iostream>


Collider::Collider(sf::RectangleShape& body) :
	body(body)
{
}


Collider::~Collider()
{
}

bool Collider::checkCollision(Collider other, sf::Vector2f& direction, float push, float offsetX, float offsetY, sf::Vector2f posOffset,sf::Vector2f intersect)
{
	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f otherHalfSize = other.GetHalfSize();
	sf::Vector2f thisPosition = GetPosition();
	sf::Vector2f thisHalfSize = GetHalfSize();

	float deltaX = otherPosition.x - thisPosition.x - posOffset.x;
	float deltaY = otherPosition.y - thisPosition.y - posOffset.y;

	float intersectX = abs(deltaX) - ((otherHalfSize.x + offsetX) + thisHalfSize.x);
	float intersectY = abs(deltaY) - ((otherHalfSize.y + offsetY) + thisHalfSize.y);
	if (intersectX > intersect.x || intersectX < -intersect.x || intersectY > intersect.y || intersectY < -intersect.y) 
	{
		if (intersectX < 0.0f && intersectY < 0.0f)
		{
			push = std::min(std::max(push, 0.0f), 1.0f);

			if (intersectX > intersectY&& intersectY < -10)
			{
				if (deltaX > 0.0f)
				{
					Move(intersectX *(1.0f - push), 0.0f);
					other.Move(-intersectX * push, 0.0f);
					direction.x = 1.0f;
					direction.y = 0.0f;
					intersect.x = intersectX;
					intersect.y = 0.0f;
				}
				else
				{
					Move(-intersectX * (1.0f - push), 0.0f);
					other.Move(intersectX * push, 0.0f);
					direction.x = -1.0f;
					direction.y = 0.0f;
					intersect.x = intersectX;
					intersect.y = 0.0f;
				}
			}
			else
			{
				if (deltaY > 0.0f)
				{
					Move(0.0f, intersectY *(1.0f - push));
					other.Move(0.0f, -intersectY * push);
					direction.x = 0.0f;
					direction.y = 1.0f;
					intersect.x = 0.0f;
					intersect.y = intersectY;
				}
				else
				{
					Move(0.0f, -intersectY * (1.0f - push));
					other.Move(0.0f, intersectY * push);
					direction.x = 0.0f;
					direction.y = -1.0f;
					intersect.x = 0.0f;
					intersect.y = intersectY;
				}
			}
			return true;
		}
	}
	return false;
}
