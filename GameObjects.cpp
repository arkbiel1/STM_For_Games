#include "StdAfx.h"
#include "GameObjects.h"

GameObjects::GameObjects()
	: _isLoaded(false)
{
	//_isLoaded = false; Slightly faster to use the above constructor initialization.
}

GameObjects::~GameObjects()
{
}

void GameObjects::Load(std::string filename)
{
	if(_image.loadFromFile(filename) == false)
	{
		_filename = "";
		_isLoaded = false;
	}
	else
	{
		_filename = filename;
		_sprite.setTexture(_image);
		_isLoaded = true;
	}
}

void GameObjects::Draw(sf::RenderWindow & renderWindow)
{
	if(_isLoaded)
	{
		renderWindow.draw(_sprite);
	}
}

void GameObjects::Update(float elapsedTime)
{
}

void GameObjects::SetPosition(float x, float y)
{
	if(_isLoaded)
	{
		_sprite.setPosition(x,y);
	}
}

sf::Vector2f GameObjects::GetPosition2()
{
 return sf::Vector2f();
}

sf::Vector2f GameObjects::GetPosition() const
{
 if(_isLoaded)
 {
  return _sprite.getPosition();
 }
 return sf::Vector2f();
}

float GameObjects::GetHeight() const
{
	return _sprite.getLocalBounds().height;
}

float GameObjects::GetWidth() const
{
	return _sprite.getLocalBounds().width;
}

sf::Rect<float> GameObjects::GetBoundingRect() const
{
	return _sprite.getGlobalBounds();
}

sf::Sprite& GameObjects::GetSprite()
{
 return _sprite;
}

bool GameObjects::IsLoaded() const
{
 return _isLoaded;
}