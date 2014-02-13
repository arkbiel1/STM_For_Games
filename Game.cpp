#include "stdafx.h"
#include "Game.h"

#include <iostream>
#include <sstream>
 
using namespace std;

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

  _mainWindow.setFramerateLimit(60);


  _mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),"STM Game");

   Spaceship *spaceship = new Spaceship();
   spaceship->SetPosition((SCREEN_WIDTH/2),(SCREEN_HEIGHT-100));

   _gameObjectsManager.Add("Spaceship",spaceship);

   Alien *alien = new Alien();
   alien->SetPosition((SCREEN_WIDTH/2),(SCREEN_HEIGHT-600));

   _gameObjectsManager.Add("Alien",alien);

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

   switch(_gameState)
   {
     case Game::Playing:
       {
			
		 //sf::Clock clock;
         //sf::Event currentEvent;
         //while(_mainWindow.pollEvent(currentEvent))
		   

           _mainWindow.clear(sf::Color(sf::Color(0,0,0)));
		   _gameObjectsManager.UpdateAll();
		   _gameObjectsManager.DrawAll(_mainWindow);

		  //create a font
		sf::Font font;

		//int health = 100;


		// Load it from a file
		if (!font.loadFromFile("font/sansation.ttf"))
		{
			printf("Error loading font\n");
		}

		int health = 100; //Spaceship::health;

		string healStr = int2Str(health);

		sf::Text atext;
		atext.setFont(font);
		atext.setCharacterSize(20);
		atext.setStyle(sf::Text::Bold);
		atext.setColor(sf::Color::White);
		atext.setPosition(0,0);
		atext.setString("Health: "  +healStr); 

		//draw the string
		_mainWindow.draw(atext); 

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