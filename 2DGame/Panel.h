#pragma once
#include <SFML\Graphics.hpp>
#include "Button.h"
#include "Text.h"
class Panel
{
public:
	Panel();
	Panel(sf::Vector2f size,sf::Color backgroundColor, sf::Vector2f pos);
	Panel(sf::Vector2f size, sf::Texture& backgroundTexture, sf::Vector2f pos);
	~Panel();
	void HandlePanel(sf::RenderWindow& window, sf::Vector2f size);
	void UpdatePanel(sf::RenderWindow& window, int selectedButton);
	std::vector<Button*> buttons;
	std::vector <Text*> texts;
	int currentButtonId = 0;
	int currentButtonIndex = 0;

private:
	sf::RectangleShape body;
	sf::Vector2f oldSize;
};

