#include "stdafx.h"
#include "Obstacle.h"
#include "Game.h"

Obstacle::Obstacle()
{
	//_maxVelocity(10.0f);
	Load("img/obstacle.png");

	//throws error window if file loading fails
	assert(IsLoaded());

	//GetSprite().setOrigin(GetSprite().getLocalBounds().width /2, GetSprite().getLocalBounds().height / 2 - 50); //50
}

Obstacle::~Obstacle()
{
}

void Obstacle::Draw(sf::RenderWindow & rw)
{
	GameObjects::Draw(rw);
}

sf::Vector2f Obstacle::GetPosition() const
{
	return position;
}
