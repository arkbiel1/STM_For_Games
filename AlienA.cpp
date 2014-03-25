#include "stdafx.h"
#include "AlienA.h"
#include "Game.h"



//AlienA * AlienA::*alienNo;

AlienA::AlienA():
	speed(80),
	alienNo(30)
{
	//_maxVelocity(10.0f);
	Load("img/alien.png");

	//throws error window if file loading fails
	assert(IsLoaded());

	//GetSprite().setOrigin(GetSprite().getLocalBounds().width /2, GetSprite().getLocalBounds().height / 2 - 50); //50
}

AlienA::~AlienA()
{
}

void AlienA::Draw(sf::RenderWindow & rw)
{
	GameObjects::Draw(rw);
}

float AlienA::GetVelocity() const
{
	return speed;
}

int AlienA::GetAlienNo() const
{
	return alienNo;
}

void AlienA::Update(float elapsedTime)
{
	// array of pointers to aliens
	AlienA** alien = new AlienA*[alienNo];

	// array of vectors
	//sf::Vector2f alienVectorArray = alien[alienNo]Vector;
	//sf::Vector2f* alienAVect = new sf::Vector2f[alienNo]; 

	// load spaceship
	Spaceship* spaceship = dynamic_cast<Spaceship*>(Game::GetGameObjectsManager().Get(0));
	sf::Vector2f spaceshipVect;

	if(spaceship != NULL)
	{
		
		spaceshipVect = spaceship->GetPosition();

		sf::Rect<float> spaceshipBounds = spaceship->GetBoundingRect();

		if(spaceshipBounds.intersects(GetBoundingRect()))  //(GetPosition().x + moveByX + (GetSprite().GetSize().x /2),GetPosition().y + (GetSprite().GetSize().y /2) + moveByY))
		{ 
			spaceship->reduceHealth(1);
		}

		float alienSpeed = speed*elapsedTime;

		for (int index = 1; index < alienNo+1 ; index++)
		{
			alien[index] = dynamic_cast<AlienA*>(Game::GetGameObjectsManager().Get(index));

			sf::Vector2f alienGetPos = alien[index]->GetPosition(); // position vector

			//alien movement
			float dirx = (spaceshipVect.x - alienGetPos.x);
			float diry = (spaceshipVect.y - alienGetPos.y);

			float hyp = sqrt(dirx*dirx + diry*diry);

			dirx /= hyp;
			diry /= hyp;

			alien[index]->SetPosition(alienGetPos.x + (dirx*alienSpeed)/alienNo, alienGetPos.y + (diry*alienSpeed)/alienNo);
		}
	}	
}