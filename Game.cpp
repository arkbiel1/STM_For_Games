#include "stdafx.h"
#include "Game.h"

void Game::Initialize(void)
{
  if(_gameState != Uninitialized)
    return;

  _mainWindow.setFramerateLimit(60);

  _mainWindow.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"STM Game");

   Spaceship *spaceship = new Spaceship();
   spaceship->SetPosition((SCREEN_WIDTH/2),500);

   _gameObjectsManager.Add("Spaceship",spaceship);

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
			
		 sf::Clock clock;
         sf::Event currentEvent;
         //while(_mainWindow.pollEvent(currentEvent))
		 while(mainWindow.isOpen)
           {
           _mainWindow.clear(sf::Color(sf::Color(0,0,0)));
		   _gameObjectsManager.UpdateAll();
		   _gameObjectsManager.DrawAll(_mainWindow);
           _mainWindow.display();
         
           if(currentEvent.type == sf::Event::Closed) _gameState =
                         Game::Exiting;
 
           if(currentEvent.type == sf::Event::KeyPressed)
             {
               if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) _mainWindow.close();
             }
           }
         break;
       }
   }
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectsManager Game::_gameObjectsManager;