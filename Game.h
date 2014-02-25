#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Spaceship.h"
#include "Alien.h"
#include "GameObjectsManager.h"

class Game
{

public:
  static void Initialize();
  static sf::RenderWindow& GetWindow();
  const static sf::Event& GetInput();
  const static GameObjectsManager& GetGameObjectsManager();
  const static int SCREEN_WIDTH = 800;
  const static int SCREEN_HEIGHT = 600;

private:
  static bool IsExiting();
  static void GameLoop();
  
  static Spaceship * player;

  enum GameState { Uninitialized, Playing, Exiting };
  
  static GameState _gameState;
  static sf::RenderWindow _mainWindow;
  static GameObjectsManager _gameObjectsManager;
};
