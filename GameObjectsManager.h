#pragma once
#include "GameObjects.h"

class GameObjectsManager
{
public:  
GameObjectsManager();
~GameObjectsManager();
 
void Add(std::string name, GameObjects* gameObject);
void Remove(std::string name);
int GetObjectsCount() const;
GameObjects* Get(std::string name) const;
 
void DrawAll(sf::RenderWindow& renderWindow);

void UpdateAll();
 
private:

std::map<std::string, GameObjects*> _gameObjects;

sf::Clock clock;
  
struct GameObjectsDeallocator
  {
    void operator()(const std::pair<std::string,GameObjects*> & p) const
    {
      delete p.second;
    }
  };
};