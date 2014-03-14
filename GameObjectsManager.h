#pragma once
#include "GameObjects.h"

class GameObjectsManager
{
public:  
GameObjectsManager();
~GameObjectsManager();
 
void Add(int index, GameObjects* gameObject);
void Remove(int index);
int GetObjectsCount() const;
GameObjects* Get(int index) const;
 
void DrawAll(sf::RenderWindow& renderWindow);

void UpdateAll();
 
private:

std::map<int, GameObjects*> _gameObjects;

sf::Clock clock;
  
struct GameObjectsDeallocator
  {
    void operator()(const std::pair<int,GameObjects*> & p) const
    {
      delete p.second;
    }
  };
};