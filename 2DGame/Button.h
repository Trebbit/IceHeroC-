#pragma once
#include <SFML\Graphics.hpp>
#include "Text.h"
class Button
{
public:
	Button();
	Button(int buttonId, sf::Texture*texture, sf::Texture*activeTexture, sf::Vector2f pos, sf::Font& font, float textSize, bool setOrigin, std::string string, bool updateSprite = true);
	~Button();
	void SetButton(sf::Texture*texture, sf::Vector2f pos, std::string text);
	void SetTexture(sf::Texture*texture, bool setOrigin);
	void ChangeButtonTexture(sf::Texture*texture);
	void Draw(sf::RenderWindow& window);
	void SetPositionWithFactor(sf::RenderWindow& window, float xFactor, float yFactor);
	void SetScale(sf::Vector2f scale);
	void SetButtonText(std::string string);
	void SetSize(sf::Vector2f size);
	void Selected(bool selected);
	bool mouseHover(sf::Vector2f mousePos);
	int buttonId;

private:
	sf::Texture* buttonTexture;
	sf::Texture* activeButton;
	bool updateSprite;
	float xPos;
	float yPos;
	sf::RectangleShape body;
	Text buttonText;
};

