#include "GameManager.h"



GameManager::GameManager(sf::RenderWindow& window, sf::Texture&backgroundTexture, LevelManager& levelManager, GUIManager& guiManager, sf::Sprite &background, int currentLevel, sf::Vector2f& orignalSize, SoundManager& soundManager)
{
	this->soundManager = &soundManager;
	playerTexture.loadFromFile("Textures/player.png");
	backgroundTexture.loadFromFile("Textures/Background.png");
	playerTexture.setSmooth(true);
	backgroundTexture.setRepeated(true);
	stringstream stream;
	window.setTitle(("2DGame Level: " + to_string(currentLevel)));
	levelManager.LoadHighScores();
	background.setTexture(backgroundTexture);
	background.setScale(
		float(512.0f) / float(background.getTexture()->getSize().x),
		float(512.0f) / float(background.getTexture()->getSize().y));
	levelManager.LoadLevel(currentLevel);
	levelManager.BuildLevel();
	orignalSize = sf::Vector2f(512.0f, 512.0f);
	player = new Player(playerTexture, 0.02f, 120.0f, 200.0f,soundManager);//texture,animationFrames,animationspeed,playerSpeed,jumpheight
	player->editorMode = false;
	coinBuffer.loadFromFile("Audio/collectPoint.wav");
	coinSound.setBuffer(coinBuffer);
	soundManager.sounds.push_back(&coinSound);
	dieBuffer.loadFromFile("Audio/deadSound.wav");
	dieSound.setBuffer(dieBuffer);
	soundManager.sounds.push_back(&dieSound);
	clickBuffer.loadFromFile("Audio/click.wav");
	clickSound.setBuffer(clickBuffer);
	soundManager.sounds.push_back(&clickSound);
}
//function to load a level and reset everything
void GameManager::ResetGame(sf::RenderWindow& window, LevelManager& levelManager, int currentLevel)
{
	stringstream stream;
	stream << fixed << setprecision(2) << levelManager.highScores[currentLevel];
	levelManager.currentTime = 0;
	levelManager.coinsCollected = 0;
	player->SetPosition(sf::Vector2f(220, 220));
	player->health = player->maxHealth;
	player->SetScale(sf::Vector2f(1, 1));
	player->facingRight = true;
	player->editorMode = false;
	//levelManager.tiles.clear();
	levelManager.tileIds.clear();
	levelManager.LoadLevel(currentLevel);
	levelManager.BuildLevel();
}
//handles all the input from the keyboard and mouse
void GameManager::CheckInput(sf::Event& event, sf::RenderWindow& window, LevelManager& levelManager, int& currentLevel, bool &levelEditorEnabled, GUIManager&guiManager, sf::Vector2f& orignalSize, sf::View& view, sf::Sprite& background, int& windowWidth, float VIEW_HEIGHT) {
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			levelManager.SaveLevel(currentLevel);
			window.close();
			break;

		case sf::Event::Resized:
			ResizeView(window, view, VIEW_HEIGHT);
			background.setTextureRect(sf::IntRect(0, 0, background.getTexture()->getSize().x * 3, background.getTexture()->getSize().y));
			windowWidth = window.getSize().x;

			break;

		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::Escape) {
				guiManager.SetPanel(guiManager.Menu, sf::Vector2f(window.getSize().x / orignalSize.x, window.getSize().y / orignalSize.y), GetWindowSize(window));
				player->walkSound.stop();
			}
			if (!guiManager.inMenu) {
				if (event.key.code == sf::Keyboard::P) {
					player->walkSound.stop();
					guiManager.SetPanel(guiManager.Pause, sf::Vector2f(window.getSize().x / orignalSize.x, window.getSize().y / orignalSize.y), GetWindowSize(window));
				}
				if (event.key.code == sf::Keyboard::F10) {
					levelEditorEnabled = !levelEditorEnabled;
					player->editorMode = levelEditorEnabled;
					levelManager.SaveLevel(currentLevel);
					if (levelEditorEnabled) {
						guiManager.SetPanel(guiManager.Editor, sf::Vector2f(window.getSize().x / orignalSize.x, window.getSize().y / orignalSize.y), GetWindowSize(window));
					}
					else
					{
						guiManager.SetPanel(guiManager.GameOverlay, sf::Vector2f(window.getSize().x / orignalSize.x, window.getSize().y / orignalSize.y), GetWindowSize(window));
					}
				}
				if (levelEditorEnabled) {
					//for selecting a kind of tile so in the editor you can easily switch
					if (event.key.code == sf::Keyboard::Num1)
						if (levelManager.currentTileId > 0) {
							levelManager.currentTileId--;
						}
					if (event.key.code == sf::Keyboard::Num2)
						if (levelManager.currentTileId < 22) {
							levelManager.currentTileId++;
						}
					if (event.key.code == sf::Keyboard::Num3)
						levelManager.currentTileId = -1;

				}
			}
			else {
				if (event.key.code == sf::Keyboard::P) {
					guiManager.SetPanel(guiManager.GameOverlay, sf::Vector2f(window.getSize().x / orignalSize.x, window.getSize().y / orignalSize.y), GetWindowSize(window));
				}
				if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
					int t = guiManager.currentPanel->buttons.size() - 1;
					if (t > guiManager.currentButton) {
						guiManager.currentButton++;
					}
				}
				if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
					if (guiManager.currentButton > 0) {
						guiManager.currentButton--;
					}
				}
				if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::E) {
					CheckButton(guiManager.GetCurrentButtonId(), window, levelManager, currentLevel, levelEditorEnabled, guiManager, orignalSize);
				}
			}
			break;

		case sf::Event::MouseMoved:
			guiManager.currentButton = -1;
			break;
		case sf::Event::MouseButtonReleased:
			if (!guiManager.inMenu) {
				if (levelEditorEnabled) {
					if (event.mouseButton.button == sf::Mouse::Left)
						levelManager.CreateNewTile(window, levelManager.currentTileId);
				}
			}
			else
			{
				CheckButton(guiManager.GetCurrentButtonId(), window, levelManager, currentLevel, levelEditorEnabled, guiManager, orignalSize);
			}
			break;
		}
	}
}

//update the game player,ui text,collision
void GameManager::UpdateGame(sf::RenderWindow& window, GUIManager&guiManager, LevelManager&levelManager, float deltaTime, int currentLevel, sf::Vector2f& orignalSize, sf::View& view, sf::Sprite& background, bool editorEnabled)
{
	stringstream stream;
	stringstream streamHighscore;
	stringstream streamCoins;
	sf::Vector2f playerPos = player->GetPosition();
	if (!guiManager.inMenu)
	{
		player->Update(deltaTime);
		levelManager.currentTime += deltaTime;
		stream << fixed << setprecision(2) << levelManager.currentTime;
		streamHighscore << fixed << setprecision(2) << levelManager.highScores[currentLevel];
		streamCoins << levelManager.coinsCollected;
		if (guiManager.CheckIfCurrentWindow(guiManager.GameOverlay))
		{
			//update UI text
			guiManager.UpdateText(0, "Time: " + stream.str());
			guiManager.UpdateText(1, "HighScore: " + streamHighscore.str());
			guiManager.UpdateText(2, "Coins: " + streamCoins.str());
		}

		sf::Vector2f direction;

		player->grounded = false;
		for (vector<std::unique_ptr<Tile>>::iterator platform = levelManager.tiles.begin(); platform != levelManager.tiles.end(); ++platform)
		{
			if ((*platform)->position.x > (playerPos.x - 100) && (*platform)->position.x < (playerPos.x + 100))
			{
				if ((*platform)->tileId != 3)//tile 3 is mid dirt tile so doesn't need to be checked because the player can never reach that kind of tile
				{
					posOffset = sf::Vector2f(0.0f, 0.0f);
					sf::Vector2f intersect = sf::Vector2f(0.0f, 0.0f);
					if ((*platform)->tileId >= 14 && (*platform)->tileId <= 16) //colliding with half size tile
					{
						posOffset = sf::Vector2f(0.0f, 18.75f);
					}
					else if ((*platform)->tileId >= 17 && (*platform)->tileId <= 19) //colliding with half size tile
					{
						posOffset = sf::Vector2f(0.0f, -18.75f);
					}
					if (((*platform)->tileId == 11 || (*platform)->tileId == 12)) //colliding with enemy
					{
						intersect = sf::Vector2f(10.0f, 10.0f);
					}
					if ((*platform)->GetCollider().checkCollision(player->GetCollider(), direction, 1.0f, (-10.0f*(player->health / player->maxHealth)), (-10.0f*(player->health / player->maxHealth)), posOffset, intersect))
					{

						if ((*platform)->tileId == 9)// colliding with coin
						{
							levelManager.coinsCollected++;
							Coin* coin = (dynamic_cast <Coin*> ((*platform).get()));
							coin->PickedUp(sf::Vector2f(-1000.0f, -1000.0f));
							coinSound.play();
							if (player->health + 4000 < player->maxHealth) {
								player->health += 4000;

							}
							else
							{
								player->health = player->maxHealth;
							}
						}
						else if (((*platform)->tileId == 11 || (*platform)->tileId == 12) && !editorEnabled) // enemy
						{
							//colliding with enemy the game is over
							dieSound.play();
							player->walkSound.stop();
							guiManager.SetPanel(guiManager.GameOver, sf::Vector2f(window.getSize().x / orignalSize.x, window.getSize().y / orignalSize.y), GetWindowSize(window));

						}
						else if ((*platform)->tileId == 10)//finish 
						{
							player->walkSound.stop();
							//colliding with the finish end the game and check highscore
							if (levelManager.UpdateHighscore(currentLevel, (100 - levelManager.currentTime) + levelManager.coinsCollected - player->health / 10))
							{
								levelManager.SaveHighScores();
								std::cout << "new highscore\n";
							}
							guiManager.SetPanel(guiManager.LevelFinished, sf::Vector2f(window.getSize().x / orignalSize.x, window.getSize().y / orignalSize.y), GetWindowSize(window));
						}
						else
						{
							//if the player is in the snow he won't shrink
							player->inColdZone = ((*platform)->tileId >= 20 && (*platform)->tileId <= 22);
							//colliding with a normal wall/ground
							player->OnCollision(direction);
						}

						if (direction.y < 0.0f)
						{
							player->grounded = true;
						}
					}
				}
			}

		}

		//show gameover windows when player is dead
		if (playerPos.y < 450 && player->health > 1)
		{
			view.setCenter(playerPos);
		}
		else
		{
			if (player->health > 10)
			{
				view.setCenter(playerPos.x, 450);
				if (playerPos.y > 900)
				{
					dieSound.play();
					player->walkSound.stop();
					guiManager.SetPanel(guiManager.GameOver, sf::Vector2f(window.getSize().x / orignalSize.x, window.getSize().y / orignalSize.y), GetWindowSize(window));
				}
			}
			else
			{

				dieSound.play();
				player->walkSound.stop();
				guiManager.SetPanel(guiManager.GameOver, sf::Vector2f(window.getSize().x / orignalSize.x, window.getSize().y / orignalSize.y), GetWindowSize(window));
			}
		}
	}
	else
	{
		if (guiManager.CheckIfCurrentWindow(guiManager.LevelFinished))
		{
			stringstream streamScore;
			stream << fixed << setprecision(2) << levelManager.currentTime;
			streamHighscore << fixed << setprecision(2) << levelManager.highScores[currentLevel];
			streamCoins << levelManager.coinsCollected;
			streamScore << fixed << setprecision(2) << ((100 - levelManager.currentTime) + levelManager.coinsCollected - player->health / 10);
			guiManager.UpdateText(0, "Time: " + stream.str());
			guiManager.UpdateText(1, "HighScore: " + streamHighscore.str());
			guiManager.UpdateText(2, "Coins: " + streamCoins.str());
			guiManager.UpdateText(3, "Score: " + streamScore.str());
		}

	}
	background.setPosition(window.mapPixelToCoords(sf::Vector2i(0, 0)));
}
//checks if  which button is pressed or selected in the menu
void GameManager::CheckButton(int currentButtonId, sf::RenderWindow& window, LevelManager& levelManager, int& currentLevel, bool &levelEditorEnabled, GUIManager&guiManager, sf::Vector2f& orignalSize) 
{
	if(currentButtonId != 0)
	{
		clickSound.play();
	}
	switch (currentButtonId)
	{
		//0 is no button clicked
	case 1://startbutton on menu
		ResetGame(window, levelManager, currentLevel);
		guiManager.SetPanel(guiManager.GameOverlay, sf::Vector2f(window.getSize().x / orignalSize.x, window.getSize().y / orignalSize.y), GetWindowSize(window));
		break;
	case 2://exit application
		levelManager.SaveLevel(currentLevel);
		window.close();
		break;
	case 3://load nextLevel
		if (currentLevel < 3) {
			currentLevel++;
			levelEditorEnabled = false;
			ResetGame(window, levelManager, currentLevel);
			guiManager.SetPanel(guiManager.GameOverlay, sf::Vector2f(window.getSize().x / orignalSize.x, window.getSize().y / orignalSize.y), GetWindowSize(window));
		}
		else
		{
			guiManager.SetPanel(guiManager.Menu, sf::Vector2f(window.getSize().x / orignalSize.x, window.getSize().y / orignalSize.y), GetWindowSize(window));
			if (soundManager->currentVolume > 1.0f) {
				guiManager.currentPanel->buttons[6]->SetButtonText("Sounds Off!");
			}
			else
			{
				guiManager.currentPanel->buttons[6]->SetButtonText("Sounds On!");
			}
		}
		break;
	case 4://restart Level
		levelEditorEnabled = false;
		ResetGame(window, levelManager, currentLevel);
		guiManager.SetPanel(guiManager.GameOverlay, sf::Vector2f(window.getSize().x / orignalSize.x, window.getSize().y / orignalSize.y), GetWindowSize(window));
		break;
	case 5://load menu
		guiManager.SetPanel(guiManager.Menu, sf::Vector2f(window.getSize().x / orignalSize.x, window.getSize().y / orignalSize.y), GetWindowSize(window));

		if (soundManager->currentVolume > 1.0f) {
			guiManager.currentPanel->buttons[6]->SetButtonText("Sounds Off!");
		}
		else
		{
			guiManager.currentPanel->buttons[6]->SetButtonText("Sounds On!");
		}
		break;
	case 6://load level
		levelEditorEnabled = false;
		currentLevel = guiManager.GetSelectedLevel();
		ResetGame(window, levelManager, currentLevel);
		guiManager.SetPanel(guiManager.GameOverlay, sf::Vector2f(window.getSize().x / orignalSize.x, window.getSize().y / orignalSize.y), GetWindowSize(window));
		break;
	case 7://show levels
		guiManager.SetPanel(guiManager.Levels, sf::Vector2f(window.getSize().x / orignalSize.x, window.getSize().y / orignalSize.y), GetWindowSize(window));
		break;
	case 8://continue
		guiManager.SetPanel(guiManager.GameOverlay, sf::Vector2f(window.getSize().x / orignalSize.x, window.getSize().y / orignalSize.y), GetWindowSize(window));
		break;
	case 9://Credits page
		guiManager.SetPanel(guiManager.Credits, sf::Vector2f(window.getSize().x / orignalSize.x, window.getSize().y / orignalSize.y), GetWindowSize(window));
		break;
	case 10://open url to art page
		ShellExecute(NULL, "open", "https://bayat.itch.io/platform-game-assets/download/eyJleHBpcmVzIjoxNTQxNjc3MjI3LCJpZCI6MTI4MTM0fQ%3d%3d.zc6BxivH8PABSjne9RTaOktPGKc%3d", NULL, NULL, SW_SHOWNORMAL);
		break;
	case 11://open url to tutorial page
		ShellExecute(NULL, "open", "https://www.youtube.com/playlist?list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9", NULL, NULL, SW_SHOWNORMAL);
		break;
	case 12://open url to my website
		ShellExecute(NULL, "open", "http://rickrijkers.nl", NULL, NULL, SW_SHOWNORMAL);
		break;
	case 13://Control page
		guiManager.SetPanel(guiManager.Controls, sf::Vector2f(window.getSize().x / orignalSize.x, window.getSize().y / orignalSize.y), GetWindowSize(window));
		break;
	case 14://toggle between fullscreen and windowed
		fullscreen = !fullscreen;
		break;
	case 15://toggle sounds
		if (soundManager->currentVolume <= 1.0f) {
			soundManager->SetVolume(100.0f);
			guiManager.currentPanel->buttons[6]->SetButtonText("Sounds Off!");
		}
		else 
		{
			soundManager->SetVolume(0.0f);
			guiManager.currentPanel->buttons[6]->SetButtonText("Sounds On!");
		}
		break;
	case 16://open link to the website where I downloaded the sounds for this game
		ShellExecute(NULL, "open", "https://www.zapsplat.com", NULL, NULL, SW_SHOWNORMAL);
		break;
	}

}
//After changing the window size update the view so everything keeps its aspect ratio
void GameManager::ResizeView(sf::RenderWindow& window, sf::View& view, float VIEW_HEIGHT)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT*aspectRatio, VIEW_HEIGHT);

}
sf::Vector2f GameManager::GetWindowSize(sf::RenderWindow& window)
{
	return sf::Vector2f(window.getSize().x, window.getSize().y);
}
GameManager::~GameManager()
{
}
