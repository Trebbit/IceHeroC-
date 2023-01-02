#pragma once
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "windows.h"
#include "shellapi.h"
#include "LevelManager.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include "GUIManager.h"
#include "SoundManager.h"
using namespace std;
class GameManager
{
public:
	GameManager(sf::RenderWindow& window, sf::Texture&backgroundTexture, LevelManager& levelManager, GUIManager& guiManager, sf::Sprite& background, int currentLevel, sf::Vector2f& orignalSize,SoundManager& soundManager);
	void CheckInput(sf::Event& event, sf::RenderWindow& window, LevelManager& levelManager, int& currentLevel, bool &levelEditorEnabled, GUIManager&guiManager, sf::Vector2f& orignalSize, sf::View& view, sf::Sprite& background, int& windowWidth, float VIEW_HEIGHT);
	~GameManager();
	void UpdateGame(sf::RenderWindow& window, GUIManager&guiManager, LevelManager&levelManager, float deltaTime, int currentLevel, sf::Vector2f& orignalSize, sf::View& view, sf::Sprite& background,bool editorEnabled);
	void ResizeView(sf::RenderWindow& window, sf::View& view, float VIEW_HEIGHT);
	sf::Vector2f GetWindowSize(sf::RenderWindow& window);
	Player *player;
	sf::Texture playerTexture;
	bool fullscreen = true;
private:
	sf::Vector2f posOffset;
	void CheckButton(int currentButtonId, sf::RenderWindow& window, LevelManager& levelManager, int& currentLevel, bool &levelEditorEnabled, GUIManager&guiManager, sf::Vector2f& orignalSize);
	void ResetGame(sf::RenderWindow& window, LevelManager& levelManager, int currentLevel);
	SoundManager *soundManager;
	sf::SoundBuffer coinBuffer;
	sf::Sound coinSound;
	sf::SoundBuffer dieBuffer;
	sf::Sound dieSound;
	sf::SoundBuffer clickBuffer;
	sf::Sound clickSound;
};
