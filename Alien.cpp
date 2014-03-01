#include "stdafx.h"
#include "Alien.h"
#include "Game.h"
//#define _USE_MATH_DEFINES
//#include <cmath>
//#include <math.h>

//Spaceship * Game::player;

float enemyx = 0;
float enemyy = 0;

Alien::Alien():
	velocity(0)
{
	//_maxVelocity(10.0f);
	Load("img/alien.png");

	//throws error window if file loading fails
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getLocalBounds().width /2, GetSprite().getLocalBounds().height / 2 - 50); //50
}

Alien::~Alien()
{
}

void Alien::Draw(sf::RenderWindow & rw)
{
	GameObjects::Draw(rw);
}

float Alien::GetVelocity() const
{
	return velocity;
}

void Alien::Update(float elapsedTime)
{

	// Position

	sf::Vector2f alienVect = GetSprite().getPosition(); // position vector



	/*printf(" alien position.x: %f \n", position.x);

	printf(" alien position.y: %f \n", position.y);*/

	//float move = 80*elapsedTime;

	sf::Vector2f spaceshipVect; 

	//GetSprite().move(2,0);

	//sf::Vector2f moveToward = Spaceship::GetPosition2();


	if (alienVect.x > 780)
	{
		GetSprite().move(-780,0);
	}

	if (alienVect.y > 550)
	{
		GetSprite().move(0,-500);
	}

	//GetSprite().move(0,0); // move

	

	Spaceship* spaceship = dynamic_cast<Spaceship*>(Game::GetGameObjectsManager().Get("Spaceship"));
	if(spaceship != NULL)
		{
			spaceshipVect = spaceship->GetPosition();
			/*printf("spaceshipVect: %f, %f\n", spaceshipVect.x, spaceshipVect.y);
			printf("spaceshipVect: %f, %f\n", spaceshipVect.x, spaceshipVect.y);
			printf("spaceshipVect: %f, %f\n", spaceshipVect.x, spaceshipVect.y);
			printf("spaceshipVect: %f, %f\n", spaceshipVect.x, spaceshipVect.y);*/

			sf::Rect<float> spaceshipBounds = spaceship->GetBoundingRect();

			if(spaceshipBounds.intersects(GetBoundingRect()))  //(GetPosition().x + moveByX + (GetSprite().GetSize().x /2),GetPosition().y + (GetSprite().GetSize().y /2) + moveByY))
			{ 
				spaceship->reduceHealth(1);
				//Spaceship::health->reduceHealth(1);
			}

			Alien* alien1 = dynamic_cast<Alien*>(Game::GetGameObjectsManager().Get("Alien1"));
			if(alien1 != NULL)
				{
				// first alien position
				alienVect = alien1->GetPosition();

				float dirx = (spaceshipVect.x - alienVect.x);
				float diry = (spaceshipVect.y - alienVect.y);

				float hyp = sqrt(dirx*dirx + diry*diry);

				dirx /= hyp;
				diry /= hyp;

				printf("dirx: %f\n", dirx);
				printf("diry: %f\n", diry);

				enemyx += dirx*0.1;
				enemyy += diry*0.1;
				//GetSprite().move(enemyx,enemyy);
				alien1->SetPosition(enemyx,enemyy);
			}
		}

	//GetSprite().move(1,1);
	//GetSprite().move(moveTowardx,moveTowardy);
}