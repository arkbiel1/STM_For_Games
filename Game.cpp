#include "stdafx.h"
#include "Game.h"
#include "Spaceship.h"

#include <iostream>
#include <sstream>

#include <vector> // to get the vector class definition
using std::vector; // to 


using namespace std;

Spaceship * Game::player;

AlienA * Game::alienAObj;
AlienF * Game::alienFObj;
AlienS * Game::alienSObj;

Flocking * Game::alienFlocking;
ASearch * Game::alienASearch;

int obstNo = 15;

sf::Sprite background;
sf::Font font;

// Converts an int into a string
static inline std::string int2Str(int x)
{
	std::stringstream type;
	type << x;
	return type.str();
}

void Game::Initialize(int type)
{
	if(_gameState != Uninitialized)
		return;

	_mainWindow.setFramerateLimit(50);

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),"STM Game");


	if (type == 1)
	{
		Flocking * AlienObj = new Flocking();
		alienFlocking = AlienObj;

		int alienNo = alienFlocking->GetAlienNo();

		//printf("AlienNo Game.cpp: %i /n", alienNo);

		// array of pointers to aliens
		Flocking** alien = new Flocking*[alienNo];

		for (int index = 1; index < alienNo+1 ; index++)
		{
		alien[index] = new Flocking();

		alien[index]->SetPosition(20+50*index,(SCREEN_HEIGHT-600));

		_gameObjectsManager.Add(index, alien[index]);
		}
		//AlienF * AlienObj = new AlienF();
		//alienFObj = AlienObj;

		//int alienNo = alienFObj->GetAlienNo();

		////printf("AlienNo Game.cpp: %i /n", alienNo);

		//// array of pointers to aliens
		//AlienF** alien = new AlienF*[alienNo];

		//for (int index = 1; index < alienNo+1 ; index++)
		//{
		//alien[index] = new AlienF();

		//alien[index]->SetPosition(20+20*index,(SCREEN_HEIGHT-600));

		//_gameObjectsManager.Add(index, alien[index]);
		//}
	}

	else if (type == 2)
	{
		AlienS * AlienObj = new AlienS();
		alienSObj = AlienObj;

		int alienNo = alienSObj->GetAlienNo();

		//printf("AlienNo Game.cpp: %i /n", alienNo);

		// array of pointers to aliens
		AlienS** alien = new AlienS*[alienNo];

		for (int index = 1; index < alienNo+1 ; index++)
		{
		alien[index] = new AlienS();

		alien[index]->SetPosition(20+20*index,(SCREEN_HEIGHT-600));

		_gameObjectsManager.Add(index, alien[index]);
		}
	}

	else if (type == 3)
	{
		ASearch * AlienObj = new ASearch();
		alienASearch = AlienObj;

		int alienNo = alienASearch->GetAlienNo();

		// array of pointers to obstacles
		Obstacle** obstacle = new Obstacle*[obstNo];

		for (int index = alienNo+1 ; index < alienNo+obstNo ; index++)
		{
		obstacle[index] = new Obstacle();

		// random numbers for obstacles position
		int randX = rand() % (Game::SCREEN_WIDTH-200);
		//printf("RandX: %i\n", randX);

		int randY = rand() % (Game::SCREEN_HEIGHT-200);
		//printf("RandY: %i\n", randY);

		obstacle[index]->SetPosition(randX+50, randY+50);

		_gameObjectsManager.Add(index, obstacle[index]);
		}

		//printf("AlienNo Game.cpp: %i /n", alienNo);

		// array of pointers to aliens
		ASearch** alien = new ASearch*[alienNo];

		for (int index = 1; index < alienNo+1 ; index++)
		{
		alien[index] = new ASearch();

		alien[index]->SetPosition(20+20*index,(SCREEN_HEIGHT-600));

		_gameObjectsManager.Add(index, alien[index]);
		}

		

		//AlienA * AlienObj = new AlienA();
		//alienAObj = AlienObj;

		//int alienNo = alienAObj->GetAlienNo();

		////printf("AlienNo Game.cpp: %i /n", alienNo);

		//// array of pointers to aliens
		//AlienA** alien = new AlienA*[alienNo];

		//for (int index = 1; index < alienNo+1 ; index++)
		//{
		//alien[index] = new AlienA();

		//alien[index]->SetPosition(20+20*index,(SCREEN_HEIGHT-600));

		//_gameObjectsManager.Add(index, alien[index]);
		//}
	}

	Spaceship *spaceship = new Spaceship();
	spaceship->SetPosition((SCREEN_WIDTH/2),(SCREEN_HEIGHT-100));

	_gameObjectsManager.Add(0, spaceship);

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

	if (player->getHealth() < 1)
		{
			atext.setCharacterSize(80);
			atext.setPosition(SCREEN_WIDTH/2-250, SCREEN_HEIGHT/2-50);
			atext.setString("GAME OVER");
			_gameObjectsManager.Remove(0);
			_mainWindow.clear();
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