#pragma once
#include <SFML\Graphics.hpp>
class Text
{
public:
	Text();
	Text(float size, sf::Color textColor, sf::Font& font, std::string string, sf::Vector2f pos);
	~Text();
	void Draw(sf::RenderWindow& window);
	void SetPosition(sf::Vector2f pos);
	void SetPositionWithFactor(sf::RenderWindow& window,float xFactor,float yFactor);
	void SetString(std::string string);
	void SetOrigin();
private:
	sf::Text sfText;
	float xPos;
	float yPos;
};

