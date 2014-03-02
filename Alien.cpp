#include "stdafx.h"
#include "Alien.h"
#include "Game.h"
//#define _USE_MATH_DEFINES
//#include <cmath>
//#include <math.h>

//Spaceship * Game::player;

float alien1x = 0;
float alien1y = 0;
float alien2x = 0;
float alien2y = 0;
float alien3x = 0;
float alien3y = 0;
float alien4x = 0;
float alien4y = 0;
float alien5x = 0;
float alien5y = 0;

sf::Vector2f alien1Vect;
sf::Vector2f alien2Vect;
sf::Vector2f alien3Vect;
sf::Vector2f alien4Vect;
sf::Vector2f alien5Vect;


//alien3->SetPosition(150,200);

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

	//sf::Vector2f alienVect = GetSprite().getPosition(); // position vector

	/*printf(" alien position.x: %f \n", position.x);

	printf(" alien position.y: %f \n", position.y);*/

	//float move = 80*elapsedTime;

	sf::Vector2f spaceshipVect; 

	//GetSprite().move(2,0);

	//sf::Vector2f moveToward = Spaceship::GetPosition2();


	/*if (alienVect.x > 780)
	{
		GetSprite().move(-780,0);
	}

	if (alienVect.y > 550)
	{
		GetSprite().move(0,-500);
	}
*/
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
				alien1Vect = alien1->GetPosition();

				float dir1x = (spaceshipVect.x - alien1Vect.x);
				float dir1y = (spaceshipVect.y - alien1Vect.y);

				float hyp1 = sqrt(dir1x*dir1x + dir1y*dir1y);

				dir1x /= hyp1;
				dir1y /= hyp1;

				//printf("dirx: %f\n", dir1x);
				//printf("diry: %f\n", dir1y);

				alien1x += dir1x*0.2;
				alien1y += dir1y*0.2;
				//GetSprite().move(enemyx,enemyy);
				alien1->SetPosition(alien1x+50,alien1y);
			}

			Alien* alien2 = dynamic_cast<Alien*>(Game::GetGameObjectsManager().Get("Alien2"));
			if(alien2 != NULL)
				{
				// first alien position
				alien2Vect = alien2->GetPosition();

				//printf("alien2vect: %f\n", alien2Vect);

				float dir2x = (spaceshipVect.x - alien2Vect.x);
				float dir2y = (spaceshipVect.y - alien2Vect.y);

				float hyp2 = sqrt(dir2x*dir2x + dir2y*dir2y);

				dir2x /= hyp2;
				dir2y /= hyp2;

				//printf("dirx: %f\n", dir2x);
				//printf("diry: %f\n", dir2y);

				alien2x += dir2x*0.2;
				alien2y += dir2y*0.2;
				//GetSprite().move(enemyx,enemyy);
				alien2->SetPosition(alien2x+225,alien2y);

				//printf("alien2vect: %f\n", alien2Vect);
			}

			Alien* alien3 = dynamic_cast<Alien*>(Game::GetGameObjectsManager().Get("Alien3"));
			if(alien3 != NULL)
				{
				// first alien position
				alien3Vect = alien3->GetPosition();

				//printf("alien2vect: %f\n", alien2Vect);

				float dir3x = (spaceshipVect.x - alien3Vect.x);
				float dir3y = (spaceshipVect.y - alien3Vect.y);

				float hyp3 = sqrt(dir3x*dir3x + dir3y*dir3y);

				dir3x /= hyp3;
				dir3y /= hyp3;

				//printf("dirx: %f\n", dir2x);
				//printf("diry: %f\n", dir2y);

				alien3x += dir3x*0.2;
				alien3y += dir3y*0.2;
				//GetSprite().move(enemyx,enemyy);
				alien3->SetPosition(alien3x+400,alien3y);

				//printf("alien2vect: %f\n", alien2Vect);
			}

			Alien* alien4 = dynamic_cast<Alien*>(Game::GetGameObjectsManager().Get("Alien4"));
			if(alien4 != NULL)
				{
				// first alien position
				alien4Vect = alien4->GetPosition();

				//printf("alien2vect: %f\n", alien2Vect);

				float dir4x = (spaceshipVect.x - alien4Vect.x);
				float dir4y = (spaceshipVect.y - alien4Vect.y);

				float hyp4 = sqrt(dir4x*dir4x + dir4y*dir4y);

				dir4x /= hyp4;
				dir4y /= hyp4;

				//printf("dirx: %f\n", dir2x);
				//printf("diry: %f\n", dir2y);

				alien4x += dir4x*0.2;
				alien4y += dir4y*0.2;
				//GetSprite().move(enemyx,enemyy);
				alien4->SetPosition(alien4x+625,alien4y);

				//printf("alien2vect: %f\n", alien2Vect);
			}

			Alien* alien5 = dynamic_cast<Alien*>(Game::GetGameObjectsManager().Get("Alien5"));
			if(alien5 != NULL)
				{
				// first alien position
				alien5Vect = alien5->GetPosition();

				//printf("alien2vect: %f\n", alien2Vect);

				float dir5x = (spaceshipVect.x - alien5Vect.x);
				float dir5y = (spaceshipVect.y - alien5Vect.y);

				float hyp5 = sqrt(dir5x*dir5x + dir5y*dir5y);

				dir5x /= hyp5;
				dir5y /= hyp5;

				//printf("dirx: %f\n", dir2x);
				//printf("diry: %f\n", dir2y);

				alien5x += dir5x*0.2;
				alien5y += dir5y*0.2;
				//GetSprite().move(enemyx,enemyy);
				alien5->SetPosition(alien5x+750,alien5y);

				//printf("alien2vect: %f\n", alien2Vect);
			}
		}

	//GetSprite().move(1,1);
	//GetSprite().move(moveTowardx,moveTowardy);
}