#include "Panel.h"
#include <iostream>

Panel::Panel()
{
}
Panel::Panel(sf::Vector2f size, sf::Color backgroundColor,sf::Vector2f pos)
{
	body.setSize(size);
	body.setFillColor(backgroundColor);
	body.setPosition(pos);
	oldSize =size;
}
Panel::Panel(sf::Vector2f size, sf::Texture& backgroundTexture, sf::Vector2f pos)
{
	body.setSize(size);
	
	body.setTexture(&backgroundTexture);
	body.setPosition(pos);
	oldSize = size;
}

//checks if a button is selected with the mouse and handles when player is going through the menu with the arrow keys
void Panel::UpdatePanel(sf::RenderWindow& window, int selectedButton) {
	body.setPosition(window.mapPixelToCoords(sf::Vector2i(0, 0)));
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	currentButtonId = 0;
	currentButtonIndex = -1;
	for (int i = 0; i < buttons.size();i++) {
		if (buttons[i]->mouseHover(mousePos)||selectedButton == i) {
			if (selectedButton >= 0) 
			{
				if (selectedButton == i) 
				{
					buttons[i]->Selected(true);
				}
				else 
				{
					buttons[i]->Selected(false);
				}
			}
			currentButtonId = buttons[i]->buttonId;
			currentButtonIndex = i;
		}
	}
}

void Panel::HandlePanel(sf::RenderWindow& window,sf::Vector2f size) {
	body.setSize(size);
	if (body.getFillColor() != sf::Color::Transparent) {
		window.draw(body);
	}
	for (Button *b : buttons) {
		b->SetPositionWithFactor(window, size.x / oldSize.x, size.y / oldSize.y);
		b->Draw(window);
	}
	for (Text* t : texts) {
		t->SetPositionWithFactor(window, size.x/ oldSize.x, size.y/ oldSize.y);
		t->Draw(window);
	}
}


Panel::~Panel()
{
}
