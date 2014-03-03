#include "stdafx.h"
#include "AlienS.h"
#include "Game.h"
//#define _USE_MATH_DEFINES
//#include <cmath>
//#include <math.h>

//Spaceship * Game::player;

float alienS1x = 0;
float alienS1y = 0;
float alienS2x = 0;
float alienS2y = 0;
float alienS3x = 0;
float alienS3y = 0;
float alienS4x = 0;
float alienS4y = 0;
float alienS5x = 0;
float alienS5y = 0;

//float alienSpeed = 0.2;

//int neighborCount = 0;

sf::Vector2f alienS1Vect;
sf::Vector2f alienS2Vect;
sf::Vector2f alienS3Vect;
sf::Vector2f alienS4Vect;
sf::Vector2f alienS5Vect;


//alien3->SetPosition(150,200);

AlienS::AlienS():
	velocity(0)
{
	//_maxVelocity(10.0f);
	Load("img/alien.png");

	//throws error window if file loading fails
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getLocalBounds().width /2, GetSprite().getLocalBounds().height / 2 - 50); //50
}

AlienS::~AlienS()
{
}

void AlienS::Draw(sf::RenderWindow & rw)
{
	GameObjects::Draw(rw);
}

float AlienS::GetVelocity() const
{
	return velocity;
}

void AlienS::Update(float elapsedTime)
{

	float alienSpeed = 0.2;
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

			AlienS* alien1 = dynamic_cast<AlienS*>(Game::GetGameObjectsManager().Get("Alien1"));
			if(alien1 != NULL)
				{
				// first alien position
				alienS1Vect = alien1->GetPosition();

				float dir1x = (spaceshipVect.x - alienS1Vect.x);
				float dir1y = (spaceshipVect.y - alienS1Vect.y);

				float hyp1 = sqrt(dir1x*dir1x + dir1y*dir1y);

				dir1x /= hyp1;
				dir1y /= hyp1;

				if (alienS2Vect.x - alienS1Vect.x < 30 && alienS2Vect.x - alienS1Vect.x > -30
					&& alienS2Vect.y - alienS1Vect.y < 30 && alienS2Vect.y - alienS1Vect.y > -30)
				{
					alienSpeed = 0;
				}
				//printf("dirx: %f\n", dir1x);
				//printf("diry: %f\n", dir1y);

				alienS1x += dir1x*alienSpeed;
				alienS1y += dir1y*alienSpeed;
				//GetSprite().move(enemyx,enemyy);
				alien1->SetPosition(alienS1x+50,alienS1y);
			}

			AlienS* alien2 = dynamic_cast<AlienS*>(Game::GetGameObjectsManager().Get("Alien2"));
			if(alien2 != NULL)
				{
				// first alien position
				alienS2Vect = alien2->GetPosition();

				//printf("aliena2Vect: %f\n", aliena2Vect);

				float dir2x = (spaceshipVect.x - alienS2Vect.x);
				float dir2y = (spaceshipVect.y - alienS2Vect.y);

				float hyp2 = sqrt(dir2x*dir2x + dir2y*dir2y);

				dir2x /= hyp2;
				dir2y /= hyp2;

				//printf("dirx: %f\n", dir2x);
				//printf("diry: %f\n", dir2y);

				alienS2x += dir2x*0.2;
				alienS2y += dir2y*0.2;
				//GetSprite().move(enemyx,enemyy);
				alien2->SetPosition(alienS2x+225,alienS2y);

				//printf("aliena2Vect: %f\n", aliena2Vect);
			}

			AlienS* alien3 = dynamic_cast<AlienS*>(Game::GetGameObjectsManager().Get("Alien3"));
			if(alien3 != NULL)
				{
				// first alien position
				alienS3Vect = alien3->GetPosition();

				//printf("aliena2Vect: %f\n", aliena2Vect);

				float dir3x = (spaceshipVect.x - alienS3Vect.x);
				float dir3y = (spaceshipVect.y - alienS3Vect.y);

				float hyp3 = sqrt(dir3x*dir3x + dir3y*dir3y);

				dir3x /= hyp3;
				dir3y /= hyp3;

				//printf("dirx: %f\n", dir2x);
				//printf("diry: %f\n", dir2y);

				alienS3x += dir3x*0.2;
				alienS3y += dir3y*0.2;
				//GetSprite().move(enemyx,enemyy);
				alien3->SetPosition(alienS3x+400,alienS3y);

				//printf("aliena2Vect: %f\n", aliena2Vect);
			}

			AlienS* alien4 = dynamic_cast<AlienS*>(Game::GetGameObjectsManager().Get("Alien4"));
			if(alien4 != NULL)
				{
				// first alien position
				alienS4Vect = alien4->GetPosition();

				//printf("aliena2Vect: %f\n", aliena2Vect);

				float dir4x = (spaceshipVect.x - alienS4Vect.x);
				float dir4y = (spaceshipVect.y - alienS4Vect.y);

				float hyp4 = sqrt(dir4x*dir4x + dir4y*dir4y);

				dir4x /= hyp4;
				dir4y /= hyp4;

				//printf("dirx: %f\n", dir2x);
				//printf("diry: %f\n", dir2y);

				alienS4x += dir4x*0.2;
				alienS4y += dir4y*0.2;
				//GetSprite().move(enemyx,enemyy);
				alien4->SetPosition(alienS4x+625,alienS4y);

				//printf("aliena2Vect: %f\n", aliena2Vect);
			}

			AlienS* alien5 = dynamic_cast<AlienS*>(Game::GetGameObjectsManager().Get("Alien5"));
			if(alien5 != NULL)
				{
				// first alien position
				alienS5Vect = alien5->GetPosition();

				//printf("aliena2Vect: %f\n", aliena2Vect);

				float dir5x = (spaceshipVect.x - alienS5Vect.x);
				float dir5y = (spaceshipVect.y - alienS5Vect.y);

				float hyp5 = sqrt(dir5x*dir5x + dir5y*dir5y);

				dir5x /= hyp5;
				dir5y /= hyp5;

				//printf("dirx: %f\n", dir2x);
				//printf("diry: %f\n", dir2y);

				alienS5x += dir5x*0.2;
				alienS5y += dir5y*0.2;
				//GetSprite().move(enemyx,enemyy);
				
				alien5->SetPosition(alienS5x+750,alienS5y);

				//printf("aliena2Vect: %f\n", aliena2Vect);
			}
		}

	//GetSprite().move(1,1);
	//GetSprite().move(moveTowardx,moveTowardy);
}