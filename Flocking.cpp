#include "stdafx.h"
#include "Flocking.h"
#include "Game.h"

#define PI 3.14159265

Flocking::Flocking():
	speed(80),
	alienNo(1)
{
	//_maxVelocity(10.0f);
	Load("img/alien.png");

	//throws error window if file loading fails
	assert(IsLoaded());

	//GetSprite().setOrigin(GetSprite().getLocalBounds().width /2, GetSprite().getLocalBounds().height / 2 - 50); //50
}

Flocking::~Flocking()
{
}

void Flocking::Draw(sf::RenderWindow & rw)
{
	GameObjects::Draw(rw);
}

sf::Vector2f Flocking::GetVelocity() const
{
	return velocity;
}

int Flocking::GetAlienNo() const
{
	return alienNo;
}

void Flocking::Update(float elapsedTime)
{
	// array of pointers to aliens
	Flocking** alien = new Flocking*[alienNo];

	// array of vectors
	//sf::Vector2f alienVectorArray = alien[alienNo]Vector;
	//sf::Vector2f* alienAVect = new sf::Vector2f[alienNo]; 

	// load spaceship
	Spaceship* spaceship = dynamic_cast<Spaceship*>(Game::GetGameObjectsManager().Get(0));
	sf::Vector2f spaceshipPos;

	if(spaceship != NULL)
	{
		
		spaceshipPos = spaceship->GetPosition();

		sf::Rect<float> spaceshipBounds = spaceship->GetBoundingRect();

		if(spaceshipBounds.intersects(GetBoundingRect()))  //(GetPosition().x + moveByX + (GetSprite().GetSize().x /2),GetPosition().y + (GetSprite().GetSize().y /2) + moveByY))
		{ 
			spaceship->reduceHealth(1);
		}

		float alienSpeed = speed*elapsedTime;

		int middleAlienInt = alienNo/2 +1;

		// middle alien movement
		if (alienNo < 3)
		{
			middleAlienInt = 1;
		}
		
		//printf("middlealienint: %i", middleAlienInt);

		alien[middleAlienInt] = dynamic_cast<Flocking*>(Game::GetGameObjectsManager().Get(middleAlienInt));
		sf::Vector2f alienMiddGetPos = alien[middleAlienInt]->GetPosition(); // position vector

		float dirx = (spaceshipPos.x - alienMiddGetPos.x);
		float diry = (spaceshipPos.y - alienMiddGetPos.y);

		float initPosx = alienMiddGetPos.x;
		float initPosy = alienMiddGetPos.y;

		float hyp = sqrt(dirx*dirx + diry*diry);
		dirx /= hyp;
		diry /= hyp;

		//velocity.y = 

		

		//printf("Velocity	speed(1): %f\n	direction(2): %f\n", velocity.x,  velocity.y);
		

		alien[middleAlienInt]->SetPosition(alienMiddGetPos.x + (dirx*alienSpeed)/alienNo, alienMiddGetPos.y + (diry*alienSpeed)/alienNo);

		float movex = initPosx - alien[middleAlienInt]->GetPosition().x;
		float movey = initPosy - alien[middleAlienInt]->GetPosition().y;

		// BC triangle side - change on x-axis
		float BC = movex*elapsedTime;
		// AC triangle side - change on y-axis
		float AC = movey*elapsedTime;
	
		float ANG = atan(BC/AC) * 180 / PI;

		// vector
		float AB = AC/cos(ANG);

		printf("BC: %f\nAC: %f\nANG: %f\nAB(v): %f\n", BC,  AC, ANG, AB);
	}
}