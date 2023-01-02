#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "vector"
#include "Tile.h"
#include "LevelManager.h"
#include "GUIManager.h"
#include "GameManager.h"
#include "SoundManager.h"
using namespace std;

static const float VIEW_HEIGHT = 512.0f;

int main()
{
	const sf::Vector2u designedsize(512, 512);
	int currentLevel = 0;
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Ice Hero    by:Rick Rijkers", sf::Style::Fullscreen);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.setFramerateLimit(120);
	sf::Texture backgroundTexture;
	GUIManager guiManager(window, sf::Vector2f(512.0f,512.0f));
	bool fullScreen = true;
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	sf::Vector2f orignalSize;
	int windowWidth = 512;
	float deltaTime = 0.0f;
	//boolean for checking if we editing a level
	bool levelEditorEnabled = false;
	LevelManager levelManager;
	SoundManager soundManager;
	sf::Sprite background;
	GameManager gameManager(window, backgroundTexture,  levelManager, guiManager,  background,  currentLevel,  orignalSize,soundManager);
	sf::Clock clock;
	window.requestFocus();
	gameManager.ResizeView(window, view, 512.0f);
	background.setTextureRect(sf::IntRect(0, 0, background.getTexture()->getSize().x * 3, background.getTexture()->getSize().y));
	windowWidth = window.getSize().x;
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f) {
			deltaTime = 1.0f / 20.0f;
		}
		sf::Event event;
		gameManager.CheckInput(event, window, levelManager, currentLevel,levelEditorEnabled, guiManager, orignalSize, view, background, windowWidth, VIEW_HEIGHT);
		gameManager.UpdateGame(window, guiManager, levelManager, deltaTime, currentLevel, orignalSize, view, background,levelEditorEnabled);
		if (gameManager.fullscreen) 
		{
			if (!fullScreen) {
				window.create(sf::VideoMode::getDesktopMode(), "Ice Hero    by:Rick Rijkers", sf::Style::Fullscreen);
				gameManager.ResizeView(window, view, 512.0f);
				background.setTextureRect(sf::IntRect(0, 0, background.getTexture()->getSize().x * 3, background.getTexture()->getSize().y));
				windowWidth = window.getSize().x;
				fullScreen = true;
			}
		}
		else 
		{
			if (fullScreen) {
				window.create(sf::VideoMode(1024.0f, 768.0f), "Ice Hero    by:Rick Rijkers", sf::Style::Resize | sf::Style::Close);
				gameManager.ResizeView(window, view, 512.0f);
				background.setTextureRect(sf::IntRect(0, 0, background.getTexture()->getSize().x * 3, background.getTexture()->getSize().y));
				windowWidth = window.getSize().x;
				fullScreen = false;
			}
		}
		window.clear(sf::Color::Black);
		window.draw(background);
		window.setView(view);
		if (!guiManager.inMenu)
		{
			gameManager.player->Draw(window);
			levelManager.Draw(window, gameManager.player->GetPosition().x, windowWidth, deltaTime);
			//if in editor mode we will update the preview of the picked tile.
			if (levelEditorEnabled)
			{
				guiManager.EditorUI(levelManager.currentTileId);
			}
		}

		guiManager.UpdatePanel(window, levelEditorEnabled);
		guiManager.HandlePanel(window, gameManager.GetWindowSize(window));
		window.display();
	}

	return 0;
}