#pragma once
#include <SFML\Graphics.hpp>
#include "Tile.h"
#include <string>
#include "Text.h"
class LevelManager
{

public:
	void CreateNewTile(sf::RenderWindow& window, int currentTileId);
	void Draw(sf::RenderWindow& window, int playerX, int windowSize, float deltaTime);
	void SaveLevel(int levelId);
	void LoadLevel(int levelId);
	void BuildLevel();
	void SaveHighScores();
	bool UpdateHighscore(int currentLevel, float score);
	void LoadHighScores();
	std::vector<std::unique_ptr<Tile>> tiles;
	LevelManager();	
	~LevelManager();
	sf::Texture levelTextures[23];
	sf::Texture eraser;
	//Data we need for a tile
	struct TileId
	{
		int tileId;
		sf::Vector2f position;
	};
	float currentTime = 0;
	int coinsCollected = 0;
	int currentTileId = 0;
	std::vector<TileId> tileIds;
	std::vector<float> highScores;

private:

	void SpawnTile(int tileId, sf::Vector2f pos);
	//images for level editor ui
	sf::Sprite pickedTile;
	sf::Sprite otherTile;
	
	//font settings
	sf::Font font;
	//text for level editor ui
	Text LeftText;
	Text RightText;
	Text otherTileText;
};