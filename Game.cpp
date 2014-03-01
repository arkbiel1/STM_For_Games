#include "stdafx.h"
#include "Game.h"
#include "Spaceship.h"

#include <iostream>
#include <sstream>

using namespace std;

Spaceship * Game::player;

sf::Sprite background;
sf::Font font;

// Converts an int into a string
static inline std::string int2Str(int x)
{
	std::stringstream type;
	type << x;
	return type.str();
}

void Game::Initialize(void)
{
	if(_gameState != Uninitialized)
		return;

	_mainWindow.setFramerateLimit(50);

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),"STM Game");


	Alien *alien1 = new Alien();
	alien1->SetPosition((SCREEN_WIDTH/2),(SCREEN_HEIGHT-600));

	Alien *alien2 = new Alien();
	alien2->SetPosition((SCREEN_WIDTH/2+150),(SCREEN_HEIGHT-600));

	Alien *alien3 = new Alien();
	alien3->SetPosition((SCREEN_WIDTH/2+300),(SCREEN_HEIGHT-600));

	Alien *alien4 = new Alien();
	alien4->SetPosition((SCREEN_WIDTH/2+450),(SCREEN_HEIGHT-600));

	Alien *alien5 = new Alien();
	alien5->SetPosition((SCREEN_WIDTH/2+600),(SCREEN_HEIGHT-600));

	Alien *alien6 = new Alien();
	alien6->SetPosition((SCREEN_WIDTH/2),(SCREEN_HEIGHT-600+100));

	Alien *alien7 = new Alien();
	alien7->SetPosition((SCREEN_WIDTH/2+150),(SCREEN_HEIGHT-600+100));

	Alien *alien8 = new Alien();
	alien8->SetPosition((SCREEN_WIDTH/2+300),(SCREEN_HEIGHT-600+100));

	Alien *alien9 = new Alien();
	alien9->SetPosition((SCREEN_WIDTH/2+450),(SCREEN_HEIGHT-600+100));

	Alien *alien10 = new Alien();
	alien10->SetPosition((SCREEN_WIDTH/2+600),(SCREEN_HEIGHT-600+100));

	_gameObjectsManager.Add("Alien1", alien1);
	_gameObjectsManager.Add("Alien2", alien2);
	_gameObjectsManager.Add("Alien3", alien3);
	_gameObjectsManager.Add("Alien4", alien4);
	_gameObjectsManager.Add("Alien5", alien5);
	_gameObjectsManager.Add("Alien6", alien6);
	_gameObjectsManager.Add("Alien7", alien7);
	_gameObjectsManager.Add("Alien8", alien8);
	_gameObjectsManager.Add("Alien9", alien9);
	_gameObjectsManager.Add("Alien10", alien10);


	Spaceship *spaceship = new Spaceship();
	spaceship->SetPosition((SCREEN_WIDTH/2),(SCREEN_HEIGHT-100));

	_gameObjectsManager.Add("Spaceship", spaceship);

	player = spaceship;

	// initialize stars

	sf::Texture stars;

	if (!stars.loadFromFile("img/stars.png"))
	{
		// error...
		printf("File not found");
	}

	//sf::Sprite background;
	stars.setRepeated(true);
	background.setTexture(stars);
	background.setTextureRect(sf::IntRect(0,0,Game::SCREEN_WIDTH,Game::SCREEN_HEIGHT));

	//background = sprite;

	//initialize font
	//sf::Font font;

	// Load it from a file
	if (!font.loadFromFile("font/sansation.ttf"))
	{
		printf("Error loading font\n");
	}

	
	
	_gameState = Game::Playing;


	while(!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}


bool Game::IsExiting()
{
	if(_gameState == Game::Exiting) 
		return true;
	else 
		return false;
}

sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

const sf::Event& Game::GetInput() 
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);
	return currentEvent;
}

const GameObjectsManager& Game::GetGameObjectsManager()
{
	return Game::_gameObjectsManager;
}

void Game::GameLoop()
{

	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);

	////create a font
	//sf::Font font;

	//// Load it from a file
	//if (!font.loadFromFile("font/sansation.ttf"))
	//{
	//	printf("Error loading font\n");
	//}

	string healStr = int2Str(player->getHealth());

	// draw health
	//playerHealth = getHealth();

	sf::Text atext;
	atext.setFont(font);
	atext.setCharacterSize(20);
	atext.setStyle(sf::Text::Bold);
	atext.setColor(sf::Color::White);
	atext.setPosition(0,0);
	//int health = player->getHealth();
	atext.setString("Health: "  + healStr); 

	if (player->getHealth() < 0)
		{
			atext.setCharacterSize(80);
			atext.setPosition(SCREEN_WIDTH/2-250, SCREEN_HEIGHT/2-50);
			atext.setString("GAME OVER");
			_gameObjectsManager.Remove("Spaceship");
		}	

	//draw the string

	//atext2.setString("Health: "); 

	switch(_gameState)
	{
	case Game::Playing:
		{

			//sf::Clock clock;
			//sf::Event currentEvent;
			//while(_mainWindow.pollEvent(currentEvent))

			_mainWindow.clear(sf::Color(sf::Color(0,0,0)));

			_mainWindow.draw(background);

			_mainWindow.draw(atext); 

			_gameObjectsManager.UpdateAll();
			_gameObjectsManager.DrawAll(_mainWindow);

			// Finally, display rendered frame on screen 
			_mainWindow.display(); 
			// _mainWindow.display();

			if(currentEvent.type == sf::Event::Closed) _gameState =
				Game::Exiting;

			if(currentEvent.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) _mainWindow.close();
			}
			break;
		}
	}
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectsManager Game::_gameObjectsManager;