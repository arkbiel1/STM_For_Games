#include "stdafx.h"
#include "AlienA.h"
#include "Game.h"
//#define _USE_MATH_DEFINES
//#include <cmath>
//#include <math.h>

//Spaceship * Game::player;

float aliena1x = 0;
float aliena1y = 0;
float aliena2x = 0;
float aliena2y = 0;
float aliena3x = 0;
float aliena3y = 0;
float aliena4x = 0;
float aliena4y = 0;
float aliena5x = 0;
float aliena5y = 0;

sf::Vector2f aliena1Vect;
sf::Vector2f aliena2Vect;
sf::Vector2f aliena3Vect;
sf::Vector2f aliena4Vect;
sf::Vector2f aliena5Vect;


//alien3->SetPosition(150,200);

AlienA::AlienA():
	velocity(0)
{
	//_maxVelocity(10.0f);
	Load("img/alien.png");

	//throws error window if file loading fails
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getLocalBounds().width /2, GetSprite().getLocalBounds().height / 2 - 50); //50
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
	return velocity;
}

void AlienA::Update(float elapsedTime)
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

			AlienA* alien1 = dynamic_cast<AlienA*>(Game::GetGameObjectsManager().Get("Alien1"));
			if(alien1 != NULL)
				{
				// first alien position
				aliena1Vect = alien1->GetPosition();

				float dir1x = (spaceshipVect.x - aliena1Vect.x);
				float dir1y = (spaceshipVect.y - aliena1Vect.y);

				float hyp1 = sqrt(dir1x*dir1x + dir1y*dir1y);

				dir1x /= hyp1;
				dir1y /= hyp1;

				//printf("dirx: %f\n", dir1x);
				//printf("diry: %f\n", dir1y);

				aliena1x += dir1x*0.2;
				aliena1y += dir1y*0.2;
				//GetSprite().move(enemyx,enemyy);
				alien1->SetPosition(aliena1x+50,aliena1y);
			}

			AlienA* alien2 = dynamic_cast<AlienA*>(Game::GetGameObjectsManager().Get("Alien2"));
			if(alien2 != NULL)
				{
				// first alien position
				aliena2Vect = alien2->GetPosition();

				//printf("aliena2Vect: %f\n", aliena2Vect);

				float dir2x = (spaceshipVect.x - aliena2Vect.x);
				float dir2y = (spaceshipVect.y - aliena2Vect.y);

				float hyp2 = sqrt(dir2x*dir2x + dir2y*dir2y);

				dir2x /= hyp2;
				dir2y /= hyp2;

				//printf("dirx: %f\n", dir2x);
				//printf("diry: %f\n", dir2y);

				aliena2x += dir2x*0.2;
				aliena2y += dir2y*0.2;
				//GetSprite().move(enemyx,enemyy);
				alien2->SetPosition(aliena2x+225,aliena2y);

				//printf("aliena2Vect: %f\n", aliena2Vect);
			}

			AlienA* alien3 = dynamic_cast<AlienA*>(Game::GetGameObjectsManager().Get("Alien3"));
			if(alien3 != NULL)
				{
				// first alien position
				aliena3Vect = alien3->GetPosition();

				//printf("aliena2Vect: %f\n", aliena2Vect);

				float dir3x = (spaceshipVect.x - aliena3Vect.x);
				float dir3y = (spaceshipVect.y - aliena3Vect.y);

				float hyp3 = sqrt(dir3x*dir3x + dir3y*dir3y);

				dir3x /= hyp3;
				dir3y /= hyp3;

				//printf("dirx: %f\n", dir2x);
				//printf("diry: %f\n", dir2y);

				aliena3x += dir3x*0.2;
				aliena3y += dir3y*0.2;
				//GetSprite().move(enemyx,enemyy);
				alien3->SetPosition(aliena3x+400,aliena3y);

				//printf("aliena2Vect: %f\n", aliena2Vect);
			}

			AlienA* alien4 = dynamic_cast<AlienA*>(Game::GetGameObjectsManager().Get("Alien4"));
			if(alien4 != NULL)
				{
				// first alien position
				aliena4Vect = alien4->GetPosition();

				//printf("aliena2Vect: %f\n", aliena2Vect);

				float dir4x = (spaceshipVect.x - aliena4Vect.x);
				float dir4y = (spaceshipVect.y - aliena4Vect.y);

				float hyp4 = sqrt(dir4x*dir4x + dir4y*dir4y);

				dir4x /= hyp4;
				dir4y /= hyp4;

				//printf("dirx: %f\n", dir2x);
				//printf("diry: %f\n", dir2y);

				aliena4x += dir4x*0.2;
				aliena4y += dir4y*0.2;
				//GetSprite().move(enemyx,enemyy);
				alien4->SetPosition(aliena4x+625,aliena4y);

				//printf("aliena2Vect: %f\n", aliena2Vect);
			}

			AlienA* alien5 = dynamic_cast<AlienA*>(Game::GetGameObjectsManager().Get("Alien5"));
			if(alien5 != NULL)
				{
				// first alien position
				aliena5Vect = alien5->GetPosition();

				//printf("aliena2Vect: %f\n", aliena2Vect);

				float dir5x = (spaceshipVect.x - aliena5Vect.x);
				float dir5y = (spaceshipVect.y - aliena5Vect.y);

				float hyp5 = sqrt(dir5x*dir5x + dir5y*dir5y);

				dir5x /= hyp5;
				dir5y /= hyp5;

				//printf("dirx: %f\n", dir2x);
				//printf("diry: %f\n", dir2y);

				aliena5x += dir5x*0.2;
				aliena5y += dir5y*0.2;
				//GetSprite().move(enemyx,enemyy);
				
				alien5->SetPosition(aliena5x+750,aliena5y);

				//printf("aliena2Vect: %f\n", aliena2Vect);
			}
		}

	//GetSprite().move(1,1);
	//GetSprite().move(moveTowardx,moveTowardy);
}