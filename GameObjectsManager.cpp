#include "stdafx.h"
#include "GameObjectsManager.h"

GameObjectsManager::GameObjectsManager()
{  
}

GameObjectsManager::~GameObjectsManager()
{
 std::for_each(_gameObjects.begin(),_gameObjects.end(),GameObjectsDeallocator());
}

void GameObjectsManager::Add(std::string name, GameObjects* gameObject)
{
 _gameObjects.insert(std::pair<std::string,GameObjects*>(name,gameObject));
}

void GameObjectsManager::Remove(std::string name)
{
 std::map<std::string, GameObjects*>::iterator results = _gameObjects.find(name);
 if(results != _gameObjects.end() )
 {
  delete results->second;
  _gameObjects.erase(results);
 }
}

GameObjects* GameObjectsManager::Get(std::string name) const
{
 std::map<std::string, GameObjects*>::const_iterator results = _gameObjects.find(name);
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
 std::map<std::string,GameObjects*>::const_iterator itr = _gameObjects.begin();
 while(itr != _gameObjects.end())
 {
  itr->second->Draw(renderWindow);
  itr++;
 }
}

void GameObjectsManager::UpdateAll()
{
	std::map<std::string,GameObjects*>::const_iterator itr = _gameObjects.begin();
	float timeDelta = clock.restart().asSeconds();

	while(itr != _gameObjects.end())
	{
		itr->second->Update(timeDelta);
		itr++;
	}
	
}