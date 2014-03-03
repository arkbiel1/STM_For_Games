#include "stdafx.h"
#include "AlienF.h"
#include "Game.h"
//#define _USE_MATH_DEFINES
//#include <cmath>
//#include <math.h>

//Spaceship * Game::player;

float alienf1x = 0;
float alienf1y = 0;
float alienf2x = 0;
float alienf2y = 0;
float alienf3x = 0;
float alienf3y = 0;
float alienf4x = 0;
float alienf4y = 0;
float alienf5x = 0;
float alienf5y = 0;

float alienSpeed = 0.2;

int neighborCount = 0;

sf::Vector2f alienf1Vect;
sf::Vector2f alienf2Vect;
sf::Vector2f alienf3Vect;
sf::Vector2f alienf4Vect;
sf::Vector2f alienf5Vect;


//alien3->SetPosition(150,200);

AlienF::AlienF():
	velocity(0)
{
	//_maxVelocity(10.0f);
	Load("img/alien.png");

	//throws error window if file loading fails
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getLocalBounds().width /2, GetSprite().getLocalBounds().height / 2 - 50); //50
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
	return velocity;
}

void AlienF::Update(float elapsedTime)
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

			// first alien in flocking steers towards the spaceship
			AlienF* alien1 = dynamic_cast<AlienF*>(Game::GetGameObjectsManager().Get("Alien1"));
			if(alien1 != NULL)
				{
				// first alien position
				alienf1Vect = alien1->GetPosition();

				float dir1x = (spaceshipVect.x - alienf1Vect.x);
				float dir1y = (spaceshipVect.y - alienf1Vect.y);

				float hyp1 = sqrt(dir1x*dir1x + dir1y*dir1y);

				dir1x /= hyp1;
				dir1y /= hyp1;

				//printf("dirx: %f\n", dir1x);
				//printf("diry: %f\n", dir1y);

				alienf1x += dir1x*0.2;
				alienf1y += dir1y*0.2;
				//GetSprite().move(enemyx,enemyy);
				alien1->SetPosition(alienf1x+50,alienf1y);
			}

			AlienF* alien2 = dynamic_cast<AlienF*>(Game::GetGameObjectsManager().Get("Alien2"));
			if(alien2 != NULL)
				{
				// first alien position
				alienf2Vect = alien2->GetPosition();

				//printf("alienf2Vect: %f\n", alienf2Vect);

				//Cohesion   Have each unit steer toward the average position of its neighbors.
				//Alignment  Have each unit steer so as to align itself to the average heading of its neighbors.
				//Separation Have each unit steer to avoid hitting its neighbors

				//if alien1 a neighbour
				if (alienf2Vect.x - alienf1Vect.x < 100  && alienf2Vect.x - alienf1Vect.x > -100
					&& alienf2Vect.y - alienf1Vect.y < 100 && alienf2Vect.y - alienf1Vect.y > -100)
					{
						//alienf2x += alienf1Vect.x;
						/*printf("Neighbors !\n");
						printf("Neighbors !\n");
						printf("Neighbors !\n");*/
						/*printf("alienf1Vect.x %f\n", alienf1Vect.x);
						printf("alienf1Vect.y %f\n", alienf1Vect.y);
						printf("alienf2Vect.x %f\n", alienf2Vect.x);
						printf("alienf2Vect.y %f\n", alienf2Vect.y);
						alienf2x++;
						alienf2y++;*/

						// cohesion & alignment
						float dir2x = (alienf1Vect.x - alienf2Vect.x);
						float dir2y = (alienf1Vect.y - alienf2Vect.y);

						float hyp2 = sqrt(dir2x*dir2x + dir2y*dir2y);

						dir2x /= hyp2;
						dir2y /= hyp2;

						//printf("dirx: %f\n", dir1x);
						//printf("diry: %f\n", dir1y);

						
						//GetSprite().move(enemyx,enemyy);
						

						// separation
						if (alienf2Vect.x - alienf1Vect.x < 30 && alienf2Vect.x - alienf1Vect.x > -30
							&& alienf2Vect.y - alienf1Vect.y < 30 && alienf2Vect.y - alienf1Vect.y > -30)
						{
							alienSpeed = 0;
						}

						alienf2x += dir2x*alienSpeed;
						alienf2y += dir2y*alienSpeed;

						/*printf("TOO CLOSE!\n");
						printf("TOO CLOSE!\n");
						printf("TOO CLOSE!\n");*/

						// move
						alien2->SetPosition(alienf2x+225,alienf2y);

						alienSpeed = 0.2;

						//alienf2y += alien2->GetPosition.y;
						//neighborCount++;
					}
 
				//printf("alienf2x: %f\n", alienf2x);
				//printf("alienf2y: %f\n", alienf2y);

				/*float dir2x = (spaceshipVect.x - alienf2Vect.x);
				float dir2y = (spaceshipVect.y - alienf2Vect.y);

				float hyp2 = sqrt(dir2x*dir2x + dir2y*dir2y);

				dir2x /= hyp2;
				dir2y /= hyp2;*/

				//printf("dirx: %f\n", dir2x);
				//printf("diry: %f\n", dir2y);

				/*alienf2x += dir2x*0.2;
				alienf2y += dir2y*0.2;*/
				//GetSprite().move(enemyx,enemyy);
				//alien2->SetPosition(225,0);
				//alien2->SetPosition(alienf2x+225,alienf2y);

				alien2->SetPosition(alienf2x+225,alienf2y);

				//printf("alienf2Vect: %f\n", alienf2Vect);
			}

			AlienF* alien3 = dynamic_cast<AlienF*>(Game::GetGameObjectsManager().Get("Alien3"));
			if(alien3 != NULL)
				{
				// first alien position
				alienf3Vect = alien3->GetPosition();

				//printf("alienf2Vect: %f\n", alienf2Vect);

				float dir3x = (spaceshipVect.x - alienf3Vect.x);
				float dir3y = (spaceshipVect.y - alienf3Vect.y);

				float hyp3 = sqrt(dir3x*dir3x + dir3y*dir3y);

				dir3x /= hyp3;
				dir3y /= hyp3;

				//printf("dirx: %f\n", dir2x);
				//printf("diry: %f\n", dir2y);

				alienf3x += dir3x*0.2;
				alienf3y += dir3y*0.2;
				//GetSprite().move(enemyx,enemyy);
				//alien3->SetPosition(alienf3x+400,alienf3y);
				alien3->SetPosition(400,0);

				//printf("alienf2Vect: %f\n", alienf2Vect);
			}

			AlienF* alien4 = dynamic_cast<AlienF*>(Game::GetGameObjectsManager().Get("Alien4"));
			if(alien4 != NULL)
				{
				// first alien position
				alienf4Vect = alien4->GetPosition();

				//printf("alienf2Vect: %f\n", alienf2Vect);

				float dir4x = (spaceshipVect.x - alienf4Vect.x);
				float dir4y = (spaceshipVect.y - alienf4Vect.y);

				float hyp4 = sqrt(dir4x*dir4x + dir4y*dir4y);

				dir4x /= hyp4;
				dir4y /= hyp4;

				//printf("dirx: %f\n", dir2x);
				//printf("diry: %f\n", dir2y);

				alienf4x += dir4x*0.2;
				alienf4y += dir4y*0.2;
				//GetSprite().move(enemyx,enemyy);
				alien4->SetPosition(625,0);
				//alien4->SetPosition(alienf4x+625,alienf4y);

				//printf("alienf2Vect: %f\n", alienf2Vect);
			}

			AlienF* alien5 = dynamic_cast<AlienF*>(Game::GetGameObjectsManager().Get("Alien5"));
			if(alien5 != NULL)
				{
				// first alien position
				alienf5Vect = alien5->GetPosition();

				//printf("alienf2Vect: %f\n", alienf2Vect);

				float dir5x = (spaceshipVect.x - alienf5Vect.x);
				float dir5y = (spaceshipVect.y - alienf5Vect.y);

				float hyp5 = sqrt(dir5x*dir5x + dir5y*dir5y);

				dir5x /= hyp5;
				dir5y /= hyp5;

				//printf("dirx: %f\n", dir2x);
				//printf("diry: %f\n", dir2y);

				alienf5x += dir5x*0.2;
				alienf5y += dir5y*0.2;
				//GetSprite().move(enemyx,enemyy);
				
				//CHANGED TO CHECK FLOCKING
				alien5->SetPosition(750,0);
				//alien5->SetPosition(alienf5x+750,alienf5y);

				//printf("alienf2Vect: %f\n", alienf2Vect);
			}
		}

	//GetSprite().move(1,1);
	//GetSprite().move(moveTowardx,moveTowardy);
}