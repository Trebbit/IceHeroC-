#include "Button.h"

Button::Button() {}

Button::Button(int buttinId, sf::Texture*texture, sf::Texture*activeTexture, sf::Vector2f pos, sf::Font& font, float textSize, bool setOrigin, std::string text, bool updateSprite)
{
	texture->setSmooth(true);
	activeTexture->setSmooth(true);
	body.setTexture(texture);
	body.setPosition(pos);
	body.setSize(sf::Vector2f(texture->getSize().x, texture->getSize().y));
	buttonText = Text(textSize, sf::Color::Black, font, text, sf::Vector2f(0.0f, 0.0f));
	if (setOrigin) {
		body.setOrigin(sf::Vector2f(texture->getSize().x / 2, texture->getSize().y / 2));
		buttonText.SetOrigin();
	}
	this->updateSprite = updateSprite;
	activeButton = activeTexture;
	buttonTexture = texture;
	xPos = pos.x;
	this->buttonId = buttinId;
	yPos = pos.y;
}
void Button::SetTexture(sf::Texture* texture, bool setOrigin) {
	buttonTexture = texture;
	body.setSize(sf::Vector2f(texture->getSize().x, texture->getSize().y));
	if (setOrigin) {
		body.setOrigin(sf::Vector2f(texture->getSize().x / 2, texture->getSize().y / 2));
	}
	body.setTexture(buttonTexture);
}
void Button::SetScale(sf::Vector2f scale) {
	body.setScale(scale);
}
void Button::SetSize(sf::Vector2f size) {
	body.setSize(size);
}
void Button::SetButtonText(std::string string) {
	buttonText.SetString(string);
}
void Button::ChangeButtonTexture(sf::Texture*texture) {
	body.setTexture(texture);
}

void Button::SetButton(sf::Texture*texture, sf::Vector2f pos, std::string text) {
	body.setTexture(texture);
	body.setPosition(pos);
	//buttonText.SetPosition(pos);
	//buttonText.SetString(text);
}
void Button::Draw(sf::RenderWindow& window) {
	window.draw(body);
	buttonText.Draw(window);
}
//set position of button with a factor so the button will always at the same position when scaling the window
void Button::SetPositionWithFactor(sf::RenderWindow & window, float xFactor, float yFactor)
{
	body.setPosition(window.mapPixelToCoords(sf::Vector2i(xPos*xFactor, yPos*yFactor)));
	buttonText.SetPosition(window.mapPixelToCoords(sf::Vector2i(xPos*xFactor, yPos*yFactor)));
}
//when the mouse hovers over a button change its texture
bool Button::mouseHover(sf::Vector2f mousePos) {
	if (body.getGlobalBounds().contains(mousePos)) {
		if (updateSprite) {
			body.setTexture(activeButton);
		}
		return true;
	}
	if (updateSprite) {
		body.setTexture(buttonTexture);
	}
	return false;
}
//when selected change the buttons its texture
void Button::Selected(bool selected) {
	if (updateSprite)
	{
		if (selected) 
		{
			body.setTexture(activeButton);
		}
		else 
		{

			body.setTexture(buttonTexture);
		}
	}
}
Button::~Button()
{
}
