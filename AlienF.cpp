#include "stdafx.h"
#include "AlienF.h"
#include "Game.h"

AlienF::AlienF():
	speed(80),
	alienNo(10)
{
	//_maxVelocity(10.0f);
	Load("img/alien.png");

	//throws error window if file loading fails
	assert(IsLoaded());

	//GetSprite().setOrigin(GetSprite().getLocalBounds().width /2, GetSprite().getLocalBounds().height / 2 - 50); //50
}

AlienF::~AlienF()
{
}

void AlienF::Draw(sf::RenderWindow & rw)
{
	GameObjects::Draw(rw);
}

float AlienF::GetVelocity() const
{
	return speed;
}

int AlienF::GetAlienNo() const
{
	return alienNo;
}

void AlienF::Update(float elapsedTime)
{
	// array of pointers to aliens
	AlienF** alien = new AlienF*[alienNo];

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
			alien[index] = dynamic_cast<AlienF*>(Game::GetGameObjectsManager().Get(index));

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
//
//	//Cohesion   Have each unit steer toward the average position of its neighbors.
//	//Alignment  Have each unit steer so as to align itself to the average heading of its neighbors.
//	//Separation Have each unit steer to avoid hitting its neighbors
//
//	////if alien1 a neighbour
//	//if (alienf2Vect.x - alienf1Vect.x < 100  && alienf2Vect.x - alienf1Vect.x > -100
//	//	&& alienf2Vect.y - alienf1Vect.y < 100 && alienf2Vect.y - alienf1Vect.y > -100)
//				
//	//// separation
//	//if (alienf2Vect.x - alienf1Vect.x < 30 && alienf2Vect.x - alienf1Vect.x > -30
//	//	&& alienf2Vect.y - alienf1Vect.y < 30 && alienf2Vect.y - alienf1Vect.y > -30)
//	//{
//	//	alienSpeed = 0;
//	//}
//
//						