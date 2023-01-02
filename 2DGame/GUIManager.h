#pragma once
#include "Panel.h"
#include <iostream>
#include "LevelManager.h"
class GUIManager
{
public:
	GUIManager(sf::RenderWindow& window, sf::Vector2f windowSize);
	~GUIManager();
	//Panel* Menu;
	//Panel* Levels;
	//Panel* GameOver;
	//Panel* GameOverlay;
	//Panel* LevelFinished;
	//Panel* Editor;
	enum PanelType{ Menu, Levels, GameOver,GameOverlay,LevelFinished,Editor,Pause,Credits, Controls};
	PanelType panel = Menu;
	void HandlePanel(sf::RenderWindow& window, sf::Vector2f size);
	void UpdatePanel(sf::RenderWindow& window, bool levelEditorEnabled);
	void EditorUI(int currentTile);
	void UpdateText(int textIndex, std::string newText);
	void SetPanel(PanelType currentPanelType ,sf::Vector2f scaleFactor, sf::Vector2f windowSize);
	void ClickButton();
	int GetSelectedLevel();
	bool CheckIfCurrentWindow(PanelType panel);
	int GetCurrentButtonId();
	int currentButton = -1;
	Panel* currentPanel;
	bool inMenu = true;
private:
	LevelManager levelManager;
	sf::Texture buttonTexture;
	sf::Texture coinTexture;
	sf::Texture buttonActiveTexture;
	sf::Texture buttonSmallTexture;
	sf::Texture buttonSmallActiveTexture;
	sf::Font font;

};

