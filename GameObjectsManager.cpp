#include "stdafx.h"
#include "GameObjectsManager.h"

GameObjectsManager::GameObjectsManager()
{  
}

GameObjectsManager::~GameObjectsManager()
{
 std::for_each(_gameObjects.begin(),_gameObjects.end(),GameObjectsDeallocator());
}

void GameObjectsManager::Add(int index, GameObjects* gameObject)
{
 _gameObjects.insert(std::pair<int,GameObjects*>(index,gameObject));
}

void GameObjectsManager::Remove(int index)
{
 std::map<int, GameObjects*>::iterator results = _gameObjects.find(index);
 if(results != _gameObjects.end() )
 {
  delete results->second;
  _gameObjects.erase(results);
 }
}

GameObjects* GameObjectsManager::Get(int index) const
{
 std::map<int, GameObjects*>::const_iterator results = _gameObjects.find(index);
 if(results == _gameObjects.end() )
  return NULL;
  return results->second;  
}

int GameObjectsManager::GetObjectsCount() const
{
 return _gameObjects.size();
}

void GameObjectsManager::DrawAll(sf::RenderWindow& renderWindow)
{
 std::map<int,GameObjects*>::const_iterator itr = _gameObjects.begin();
 while(itr != _gameObjects.end())
 {
  itr->second->Draw(renderWindow);
  itr++;
 }
}

void GameObjectsManager::UpdateAll()
{
	std::map<int,GameObjects*>::const_iterator itr = _gameObjects.begin();
	float timeDelta = clock.restart().asSeconds();

	while(itr != _gameObjects.end())
	{
		itr->second->Update(timeDelta);
		itr++;
	}
	
}