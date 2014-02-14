#include "stdafx.h"
#include "Alien2.h"
#include "Game.h"
//#define _USE_MATH_DEFINES
//#include <cmath>
//#include <math.h>


Alien2::Alien2():
	velocity(0)
{
	//_maxVelocity(10.0f);
	Load("img/alien.png");

	//throws error window if file loading fails
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getLocalBounds().width /2, GetSprite().getLocalBounds().height / 2 - 90); //50
}

Alien2::~Alien2()
{
}

void Alien2::Draw(sf::RenderWindow & rw)
{
	GameObjects::Draw(rw);
}

float Alien2::GetVelocity() const
{
	return velocity;
}

void Alien2::Update(float elapsedTime)
{

	// Position

	sf::Vector2f position = GetSprite().getPosition(); // position vector

	printf(" alien position.x: %f \n", position.x);

	printf(" alien position.y: %f \n", position.y);

	//float move = 80*elapsedTime;

	GetSprite().move(-3,0);

	if (position.x < 50)
	{
		GetSprite().move(780,0);
	}

	//GetSprite().move(0,0); // move

	Spaceship* spaceship = dynamic_cast<Spaceship*>(Game::GetGameObjectsManager().Get("Spaceship"));
	if(spaceship != NULL)
		{
			sf::Rect<float> spaceshipBounds = spaceship->GetBoundingRect();

			if(spaceshipBounds.intersects(GetBoundingRect()))  //(GetPosition().x + moveByX + (GetSprite().GetSize().x /2),GetPosition().y + (GetSprite().GetSize().y /2) + moveByY))
			{ 
				printf("COLLLLLLLLLLLLLLLLLLLLLLLISION \n\n\n\n\n\n\n");
			}
		}
}