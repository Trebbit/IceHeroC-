#include "LevelManager.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


LevelManager::LevelManager()
{
	levelTextures[0].loadFromFile("Textures/GrassCliffLeft.png");
	levelTextures[1].loadFromFile("Textures/GrassCliffRight.png");
	levelTextures[2].loadFromFile("Textures/GrassCliffMid.png");
	levelTextures[3].loadFromFile("Textures/Dirt.png");
	levelTextures[4].loadFromFile("Textures/DirtLeft.png");
	levelTextures[5].loadFromFile("Textures/DirtRight.png");
	levelTextures[6].loadFromFile("Textures/GrassLeft.png");
	levelTextures[7].loadFromFile("Textures/GrassRight.png");
	levelTextures[8].loadFromFile("Textures/GrassMid.png");
	levelTextures[9].loadFromFile("Textures/coins.png");
	levelTextures[10].loadFromFile("Textures/chest.png");
	levelTextures[11].loadFromFile("Textures/Saw.png");
	levelTextures[12].loadFromFile("Textures/Mace.png");
	levelTextures[13].loadFromFile("Textures/GrassLeftHalf.png");
	levelTextures[14].loadFromFile("Textures/GrassRightHalf.png");
	levelTextures[15].loadFromFile("Textures/GrassMidHalf.png");
	levelTextures[16].loadFromFile("Textures/GrassMid2Half.png");
	levelTextures[17].loadFromFile("Textures/DirtMidBot.png");
	levelTextures[18].loadFromFile("Textures/DirtleftBot.png");
	levelTextures[19].loadFromFile("Textures/DirtRightBot.png");
	levelTextures[20].loadFromFile("Textures/GrassSnowLeft.png");
	levelTextures[21].loadFromFile("Textures/GrassSnowRight.png");
	levelTextures[22].loadFromFile("Textures/GrassSnowMid.png");
	
	eraser.loadFromFile("Textures/Eraser.png");


	font.loadFromFile("Font/RifficFree-Bold.ttf");
	LeftText = Text(20, sf::Color::Black, font, "< 1", sf::Vector2f(0.0f, 0.0f));
	RightText = Text(20, sf::Color::Black, font, "2 >", sf::Vector2f(0.0f, 0.0f));
	otherTileText = Text(20, sf::Color::Black, font, "3", sf::Vector2f(0.0f, 0.0f));
	otherTile.setScale(sf::Vector2f(0.25f, 0.25f));
	pickedTile.setScale(sf::Vector2f(0.5f, 0.5f));

}
void LevelManager::CreateNewTile(sf::RenderWindow& window, int currentTileId)
{
	//will create tile data this will be saved later on.
	TileId newTile;
	newTile.position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	newTile.position = sf::Vector2f(round(newTile.position.x / 75) * 75, round(newTile.position.y / 75) * 75);
	newTile.tileId = currentTileId;
	bool alreadyExists = false;

	//check if position is already is used if so than overwrite tileId
	for (int i = 0; i < tileIds.size();i++) {
		if (tileIds[i].position == newTile.position) {
			alreadyExists = true;
			if (newTile.tileId >= 0)
			{
				tileIds[i].tileId = newTile.tileId;
			}
			else
			{
				tileIds.erase(tileIds.begin() + i);
			}
		}
	}

	//sort the tiles from left to right
	std::sort(tileIds.begin(), tileIds.end(),
		[](TileId const& a, TileId const& b) { return a.position.x < b.position.x; });

	if (newTile.tileId >= 0)
	{
		if (!alreadyExists) {
			tileIds.push_back(newTile);
		}
		//make a platform for see a live version of the level and sort the platform array for optimizing collision
		SpawnTile(currentTileId, newTile.position);

	}
	else
	{
		//checks if there is a tile with the same position so the old one will be erased
		for (int p = 0; p < tiles.size();p++)
		{
			if (newTile.position == tiles[p]->position) {
				tiles.erase(tiles.begin() + p);
			}
		}
	} 

}

//checks if there is a new highscore
bool LevelManager::UpdateHighscore(int currentLevel, float score) {
	if (highScores[currentLevel] < score || highScores[currentLevel] == 0) {
		highScores[currentLevel] = score;
		return true;
	}
	return false;
}

//saves the highscores to a txt file
void LevelManager::SaveHighScores() {
	ofstream HighScoreData("levels/Highscores.txt");
	if (HighScoreData.is_open())
	{
		for (float& f : highScores) {
			HighScoreData << f;
			HighScoreData << "" << endl;
		}
		HighScoreData.close();
	}
	else cout << "Unable to open file";
}

//Gets highscores from txt file
void LevelManager::LoadHighScores() {
	highScores.clear();
	ifstream HighScoreData("levels/Highscores.txt");
	if (HighScoreData.is_open())
	{
		float score = 0;
		while (HighScoreData >> score) {
			highScores.push_back(score);
		}
		HighScoreData.close();
	}
	else
	{
		cout << "Unable to open file";
		for (int i = 0; i < 10;i++) {
			highScores.push_back(0);
		}
		SaveHighScores();
	}
}
//save level to txt file
void LevelManager::SaveLevel(int levelId)
{
	ofstream LevelData("levels/LevelData" + to_string(levelId) + ".txt");
	if (LevelData.is_open())
	{
		for (TileId& tId : tileIds) {
			LevelData << tId.tileId << " " << tId.position.x << " " << tId.position.y;
			LevelData << "" << endl;
		}
		LevelData.close();
	}
	else cout << "Unable to open file";
}
//load from txt file
void LevelManager::LoadLevel(int levelId)
{
	tileIds.clear();
	ifstream LevelData("levels/LevelData" + to_string(levelId) + ".txt");
	if (LevelData.is_open())
	{
		int id = 0, x = 0, y = 0;

		while (LevelData >> id >> x >> y) {
			TileId newTile;
			newTile.tileId = id;
			newTile.position.x = x;
			newTile.position.y = y;
			tileIds.push_back(newTile);
		}
		LevelData.close();
	}
	else cout << "Unable to open file";
}

//adds a tile when clicking in the leveleditor
void LevelManager::SpawnTile(int tileId, sf::Vector2f pos) {

	switch (tileId)
	{
	case 9:
		tiles.emplace_back(std::unique_ptr<Coin>(new Coin(levelTextures[tileId], sf::Vector2f(35.0f, 50.0f), pos, tileId, sf::Vector2f(17.5f, 25.0f))));
		break;
	case 12:
		tiles.emplace_back(std::unique_ptr<Enemy>(new Enemy(levelTextures[tileId], sf::Vector2f(75.0f, 75.0f), pos, tileId, sf::Vector2f(37.5f, 37.5f))));
		break;
	case 11:
		tiles.emplace_back(std::unique_ptr<Enemy>(new Enemy(levelTextures[tileId], sf::Vector2f(75.0f, 75.0f), pos, tileId, sf::Vector2f(37.5f, 37.5f))));
		break;
	case 13:
		tiles.emplace_back(std::unique_ptr<Tile>(new Tile(levelTextures[tileId], sf::Vector2f(75.0f, 37.5f), pos, tileId, sf::Vector2f(37.5f, 0.0f))));
		break;
	case 14:
		tiles.emplace_back(std::unique_ptr<Tile>(new Tile(levelTextures[tileId], sf::Vector2f(75.0f, 37.5f), pos, tileId, sf::Vector2f(37.5f, 0.0f))));
		break;
	case 15:
		tiles.emplace_back(std::unique_ptr<Tile>(new Tile(levelTextures[tileId], sf::Vector2f(75.0f, 37.5f), pos, tileId, sf::Vector2f(37.5f, 0.0f))));
		break;
	case 16:
		tiles.emplace_back(std::unique_ptr<Tile>(new Tile(levelTextures[tileId], sf::Vector2f(75.0f, 37.5f), pos, tileId, sf::Vector2f(37.5f, 0.0f))));
		break;
	case 17:
		tiles.emplace_back(std::unique_ptr<Tile>(new Tile(levelTextures[tileId], sf::Vector2f(75.0f, 37.5f), pos, tileId, sf::Vector2f(37.5f, 37.5f))));
		break;
	case 18:
		tiles.emplace_back(std::unique_ptr<Tile>(new Tile(levelTextures[tileId], sf::Vector2f(75.0f, 37.5f), pos, tileId, sf::Vector2f(37.5f, 37.5f))));
		break;
	case 19:
		tiles.emplace_back(std::unique_ptr<Tile>(new Tile(levelTextures[tileId], sf::Vector2f(75.0f, 37.5f), pos, tileId, sf::Vector2f(37.5f, 37.5f))));
		break;
	default:
		tiles.emplace_back(std::unique_ptr<Tile>(new Tile(levelTextures[tileId], sf::Vector2f(75.0f, 75.0f), pos, tileId, sf::Vector2f(37.5f, 37.5f))));
		break;
	}
}
//building a level out of Loaded data
void LevelManager::BuildLevel()
{
	tiles.clear();
	if (tileIds.size() > 1) {
		for (int i = 0; i < tileIds.size(); i++)
		{
			if (i < tileIds.size()) {
				SpawnTile(tileIds[i].tileId, tileIds[i].position);
			}
		}
	}
}

//draws all the tiles which are in the view of the player
void LevelManager::Draw(sf::RenderWindow& window, int playerX, int windowSize, float deltaTime)
{
	for (vector<std::unique_ptr<Tile>>::iterator platform = tiles.begin(); platform != tiles.end(); ++platform)
	{
		if ((*platform)->position.x > (playerX - (windowSize / 2) - 50) && (*platform)->position.x < (playerX + (windowSize / 2) + 50))
		{
			
			if ((*platform)->tileId == 9) {
				Coin *p = dynamic_cast<Coin *>((*platform).get());
				if (p) {
					p->TileBehaviour(deltaTime);
					p->Draw(window);
				}
			}
			else if ((*platform)->tileId == 11 || (*platform)->tileId == 12)
			{
				Enemy *p = dynamic_cast<Enemy *>((*platform).get());
				if (p) {
					p->TileBehaviour(deltaTime);
					p->Draw(window);
				}
			}
			else {
				(*platform)->Draw(window);
			}
		}
	}
}

LevelManager::~LevelManager()
{
}
