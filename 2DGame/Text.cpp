#include "Text.h"
#include <iostream>
Text::Text() {};
Text::Text(float size, sf::Color textColor, sf::Font& font, std::string string, sf::Vector2f pos)
{
	sfText.setFont(font);
	sfText.setCharacterSize(size * 10);
	sfText.setScale(0.1f, 0.1f);
	sfText.setFillColor(textColor);
	sfText.setString(string);
	
	xPos = pos.x;
	yPos = pos.y;
	//sfText.setPosition(pos);
}
void Text::SetOrigin() {
	sfText.setOrigin(sf::Vector2f(sfText.getLocalBounds().width / 2, sfText.getLocalBounds().height / 2));
}
void Text::SetPositionWithFactor(sf::RenderWindow& window, float xFactor, float yFactor) {
	sfText.setPosition(window.mapPixelToCoords(sf::Vector2i(xPos*xFactor,yPos*yFactor)));
}
void Text::Draw(sf::RenderWindow& window)
{
	window.draw(sfText);
}
void Text::SetPosition(sf::Vector2f pos)
{
	xPos = pos.x;
	yPos = pos.y;

	sfText.setPosition(pos);
}

void Text::SetString(std::string string)
{
	sfText.setString(string);
}
Text::~Text()
{
}