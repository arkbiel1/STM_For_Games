#include "stdafx.h"
#include "AlienF.h"
#include "Game.h"
//#define _USE_MATH_DEFINES
//#include <cmath>
//#include <math.h>

//Spaceship * Game::player;

float alienF1x = 0;
float alienF1y = 0;
float alienF2x = 0;
float alienF2y = 0;
float alienF3x = 0;
float alienF3y = 0;
float alienF4x = 0;
float alienF4y = 0;
float alienF5x = 0;
float alienF5y = 0;

//float alienSpeed = 0.2;

int neighborCount = 0;

sf::Vector2f alienF1Vect;
sf::Vector2f alienF2Vect;
sf::Vector2f alienF3Vect;
sf::Vector2f alienF4Vect;
sf::Vector2f alienF5Vect;

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
	float alien1Speed = 0.2;
	float alien2Speed = 0.2;
	float alien3Speed = 0.2;
	float alien4Speed = 0.2;
	float alien5Speed = 0.2;

	// load spaceship
	Spaceship* spaceship = dynamic_cast<Spaceship*>(Game::GetGameObjectsManager().Get("Spaceship"));
	sf::Vector2f spaceshipVect; 

	// load aliens
	AlienF* alien1 = dynamic_cast<AlienF*>(Game::GetGameObjectsManager().Get("Alien1"));
	AlienF* alien2 = dynamic_cast<AlienF*>(Game::GetGameObjectsManager().Get("Alien2"));
	AlienF* alien3 = dynamic_cast<AlienF*>(Game::GetGameObjectsManager().Get("Alien3"));
	AlienF* alien4 = dynamic_cast<AlienF*>(Game::GetGameObjectsManager().Get("Alien4"));
	AlienF* alien5 = dynamic_cast<AlienF*>(Game::GetGameObjectsManager().Get("Alien5"));

	// load alien coordinates
	alienF1Vect = alien1->GetPosition();
	alienF2Vect = alien2->GetPosition();
	alienF3Vect = alien3->GetPosition();
	alienF4Vect = alien4->GetPosition();
	alienF5Vect = alien5->GetPosition();
	
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

	// steer towards spaceship
	float dir1x = (spaceshipVect.x - alienF1Vect.x);
	float dir1y = (spaceshipVect.y - alienF1Vect.y);
	float dir2x = (spaceshipVect.x - alienF2Vect.x);
	float dir2y = (spaceshipVect.y - alienF2Vect.y);
	float dir3x = (spaceshipVect.x - alienF3Vect.x);
	float dir3y = (spaceshipVect.y - alienF3Vect.y);
	float dir4x = (spaceshipVect.x - alienF4Vect.x);
	float dir4y = (spaceshipVect.y - alienF4Vect.y);
	float dir5x = (spaceshipVect.x - alienF5Vect.x);
	float dir5y = (spaceshipVect.y - alienF5Vect.y);

	//// if any alien is near alien1
	//if (alienF1Vect.x - alienF2Vect.x < 30  && alienF1Vect.x - alienF2Vect.x > -30
	//	&& alienF1Vect.y - alienF2Vect.y < 30 && alienF1Vect.y - alienF2Vect.y > -30)	// alien2 near
	//	// steer towards alien2
	//{
	//	dir1x = (alienF2Vect.x - alienF1Vect.x);
	//	dir1y = (alienF2Vect.y - alienF1Vect.y);
	//	//alien1Speed = 0.05;
	//}

	//if (alienF1Vect.x - alienF3Vect.x < 30  && alienF1Vect.x - alienF3Vect.x > -30
	//	&& alienF1Vect.y - alienF3Vect.y < 30 && alienF1Vect.y - alienF3Vect.y > -30)	// alien3 near
	//	// steer towards alien3
	//{
	//	dir1x = (alienF3Vect.x - alienF1Vect.x);
	//	dir1y = (alienF3Vect.y - alienF1Vect.y);
	//}

	//if (alienF1Vect.x - alienF4Vect.x < 30  && alienF1Vect.x - alienF4Vect.x > -30
	//	&& alienF1Vect.y - alienF4Vect.y < 30 && alienF1Vect.y - alienF4Vect.y > -30)	// alien4 near
	//	// steer towards alien4
	//{
	//	dir1x = (alienF4Vect.x - alienF1Vect.x);
	//	dir1y = (alienF4Vect.y - alienF1Vect.y);
	//}

	//if (alienF1Vect.x - alienF5Vect.x < 30  && alienF1Vect.x - alienF5Vect.x > -30
	//	&& alienF1Vect.y - alienF5Vect.y < 30 && alienF1Vect.y - alienF5Vect.y > -30)	// alien5 near
	//	// steer towards alien5
	//{
	//	dir1x = (alienF5Vect.x - alienF1Vect.x);
	//	dir1y = (alienF5Vect.y - alienF1Vect.y);
	//}

	////if too close stop
	//if (alienF1Vect.x - alienF2Vect.x < 20  && alienF1Vect.x - alienF2Vect.x > -20
	//	&& alienF1Vect.y - alienF2Vect.y < 20 && alienF1Vect.y - alienF2Vect.y > -20	// alien2 near
	//	||
	//	alienF1Vect.x - alienF3Vect.x < 20  && alienF1Vect.x - alienF3Vect.x > -20
	//	&& alienF1Vect.y - alienF3Vect.y < 20 && alienF1Vect.y - alienF3Vect.y > -20	// alien3 near
	//	||
	//	alienF1Vect.x - alienF4Vect.x < 20  && alienF1Vect.x - alienF4Vect.x > -20
	//	&& alienF1Vect.y - alienF4Vect.y < 20 && alienF1Vect.y - alienF4Vect.y > -20	// alien4 near
	//	||
	//	alienF1Vect.x - alienF5Vect.x < 20  && alienF1Vect.x - alienF5Vect.x > -20
	//	&& alienF1Vect.y - alienF5Vect.y < 20 && alienF1Vect.y - alienF5Vect.y > -20)	// alien5 near
	//{
	//	dir1x = (spaceshipVect.x - alienF1Vect.x);
	//	dir1y = (spaceshipVect.y - alienF1Vect.y);
	//	if (alien2Speed != 0)
	//	{
	//		//alien1Speed = 0;
	//	}
	//}

	// if any alien is near alien2
	if (alienF2Vect.x - alienF1Vect.x < 30  && alienF2Vect.x - alienF1Vect.x > -30
		&& alienF2Vect.y - alienF1Vect.y < 30 && alienF2Vect.y - alienF1Vect.y > -30)	// alien1 near
		// steer towards alien1
	{
		dir2x = (alienF1Vect.x - alienF2Vect.x);
		dir2y = (alienF1Vect.y - alienF2Vect.y);
		//alien2Speed = 0.05;
	}
	if (alienF2Vect.x - alienF3Vect.x < 30  && alienF2Vect.x - alienF3Vect.x > -30
		&& alienF2Vect.y - alienF3Vect.y < 30 && alienF2Vect.y - alienF3Vect.y > -30)	// alien3 near
		// steer towards alien3
	{
		dir2x = (alienF3Vect.x - alienF2Vect.x);
		dir2y = (alienF3Vect.y - alienF2Vect.y);
	}

	if (alienF2Vect.x - alienF4Vect.x < 30  && alienF2Vect.x - alienF4Vect.x > -30
		&& alienF2Vect.y - alienF4Vect.y < 30 && alienF2Vect.y - alienF4Vect.y > -30)	// alien4 near
		// steer towards alien4
	{
		dir2x = (alienF4Vect.x - alienF2Vect.x);
		dir2y = (alienF4Vect.y - alienF2Vect.y);
	}

	if (alienF2Vect.x - alienF5Vect.x < 30  && alienF2Vect.x - alienF5Vect.x > -30
		&& alienF2Vect.y - alienF5Vect.y < 30 && alienF2Vect.y - alienF5Vect.y > -30)	// alien5 near
		// steer towards alien5
	{
		dir2x = (alienF5Vect.x - alienF2Vect.x);
		dir2y = (alienF5Vect.y - alienF2Vect.y);
	}

	//if too close stop
	if (alienF2Vect.x - alienF1Vect.x < 20  && alienF2Vect.x - alienF1Vect.x > -20
		&& alienF2Vect.y - alienF1Vect.y < 20 && alienF2Vect.y - alienF1Vect.y > -20	// alien1 near
		||
		alienF2Vect.x - alienF3Vect.x < 20  && alienF2Vect.x - alienF3Vect.x > -20
		&& alienF2Vect.y - alienF3Vect.y < 20 && alienF2Vect.y - alienF3Vect.y > -20	// alien3 near
		||
		alienF2Vect.x - alienF4Vect.x < 20  && alienF2Vect.x - alienF4Vect.x > -20
		&& alienF2Vect.y - alienF4Vect.y < 20 && alienF2Vect.y - alienF4Vect.y > -20	// alien4 near
		||
		alienF2Vect.x - alienF5Vect.x < 20  && alienF2Vect.x - alienF5Vect.x > -20
		&& alienF2Vect.y - alienF5Vect.y < 20 && alienF2Vect.y - alienF5Vect.y > -20)	// alien5 near
	{
		dir2x = (spaceshipVect.x - alienF2Vect.x);
		dir2y = (spaceshipVect.y - alienF2Vect.y);
		if (alien1Speed != 0 && alien3Speed != 0 && alien4Speed != 0 && alien5Speed != 0 )
		{
			alien2Speed = 0;
		}
	}

	// if any alien is near alien3
	if (alienF3Vect.x - alienF1Vect.x < 30  && alienF3Vect.x - alienF1Vect.x > -30
		&& alienF3Vect.y - alienF1Vect.y < 30 && alienF3Vect.y - alienF1Vect.y > -30)	// alien1 near
		// steer towards alien1
	{
		dir3x = (alienF1Vect.x - alienF3Vect.x);
		dir3y = (alienF1Vect.y - alienF3Vect.y);
	}
	if (alienF3Vect.x - alienF2Vect.x < 30  && alienF3Vect.x - alienF2Vect.x > -30
		&& alienF3Vect.y - alienF2Vect.y < 30 && alienF3Vect.y - alienF2Vect.y > -30)	// alien2 near
		// steer towards alien2
	{
		dir3x = (alienF2Vect.x - alienF3Vect.x);
		dir3y = (alienF2Vect.y - alienF3Vect.y);
	}

	if (alienF3Vect.x - alienF4Vect.x < 30  && alienF3Vect.x - alienF4Vect.x > -30
		&& alienF3Vect.y - alienF4Vect.y < 30 && alienF3Vect.y - alienF4Vect.y > -30)	// alien4 near
		// steer towards alien4
	{
		dir3x = (alienF4Vect.x - alienF3Vect.x);
		dir3y = (alienF4Vect.y - alienF3Vect.y);
	}

	if (alienF3Vect.x - alienF5Vect.x < 30  && alienF3Vect.x - alienF5Vect.x > -30
		&& alienF3Vect.y - alienF5Vect.y < 30 && alienF3Vect.y - alienF5Vect.y > -30)	// alien5 near
		// steer towards alien5
	{
		dir3x = (alienF5Vect.x - alienF3Vect.x);
		dir3y = (alienF5Vect.y - alienF3Vect.y);
	}

	//if too close stop
	if (alienF3Vect.x - alienF1Vect.x < 20  && alienF3Vect.x - alienF1Vect.x > -20
		&& alienF3Vect.y - alienF1Vect.y < 20 && alienF3Vect.y - alienF1Vect.y > -20	// alien1 near
		||
		alienF3Vect.x - alienF2Vect.x < 20  && alienF3Vect.x - alienF2Vect.x > -20
		&& alienF3Vect.y - alienF2Vect.y < 20 && alienF3Vect.y - alienF2Vect.y > -20	// alien2 near
		||
		alienF3Vect.x - alienF4Vect.x < 20  && alienF3Vect.x - alienF4Vect.x > -20
		&& alienF3Vect.y - alienF4Vect.y < 20 && alienF3Vect.y - alienF4Vect.y > -20	// alien4 near
		||
		alienF3Vect.x - alienF5Vect.x < 20  && alienF3Vect.x - alienF5Vect.x > -20
		&& alienF3Vect.y - alienF5Vect.y < 20 && alienF3Vect.y - alienF5Vect.y > -20)	// alien5 near
	{
		dir3x = (spaceshipVect.x - alienF3Vect.x);
		dir3y = (spaceshipVect.y - alienF3Vect.y);
		if (alien1Speed != 0 && alien2Speed != 0 && alien4Speed != 0 && alien5Speed != 0 )
		{
			alien3Speed = 0;
		}
	}
	
	// if any alien is near alien4
	if (alienF4Vect.x - alienF1Vect.x < 30  && alienF4Vect.x - alienF1Vect.x > -30
		&& alienF4Vect.y - alienF1Vect.y < 30 && alienF4Vect.y - alienF1Vect.y > -30)	// alien1 near
		// steer towards alien1
	{
		dir4x = (alienF1Vect.x - alienF4Vect.x);
		dir4y = (alienF1Vect.y - alienF4Vect.y);
	}
	if (alienF4Vect.x - alienF2Vect.x < 30  && alienF4Vect.x - alienF2Vect.x > -30
		&& alienF4Vect.y - alienF2Vect.y < 30 && alienF4Vect.y - alienF2Vect.y > -30)	// alien2 near
		// steer towards alien2
	{
		dir4x = (alienF2Vect.x - alienF4Vect.x);
		dir4y = (alienF2Vect.y - alienF4Vect.y);
	}

	if (alienF4Vect.x - alienF3Vect.x < 30  && alienF4Vect.x - alienF3Vect.x > -30
		&& alienF4Vect.y - alienF3Vect.y < 30 && alienF4Vect.y - alienF3Vect.y > -30)	// alien3 near
		// steer towards alien3
	{
		dir4x = (alienF3Vect.x - alienF4Vect.x);
		dir4y = (alienF3Vect.y - alienF4Vect.y);
	}

	if (alienF4Vect.x - alienF5Vect.x < 30  && alienF3Vect.x - alienF5Vect.x > -30
		&& alienF4Vect.y - alienF5Vect.y < 30 && alienF3Vect.y - alienF5Vect.y > -30)	// alien5 near
		// steer towards alien5
	{
		dir4x = (alienF5Vect.x - alienF4Vect.x);
		dir4y = (alienF5Vect.y - alienF4Vect.y);
	}

	//if too close stop
	if (alienF4Vect.x - alienF1Vect.x < 20  && alienF4Vect.x - alienF1Vect.x > -20
		&& alienF4Vect.y - alienF1Vect.y < 20 && alienF4Vect.y - alienF1Vect.y > -20	// alien1 near
		||
		alienF4Vect.x - alienF2Vect.x < 20  && alienF4Vect.x - alienF2Vect.x > -20
		&& alienF4Vect.y - alienF2Vect.y < 20 && alienF4Vect.y - alienF2Vect.y > -20	// alien2 near
		||
		alienF4Vect.x - alienF3Vect.x < 20  && alienF4Vect.x - alienF3Vect.x > -20
		&& alienF4Vect.y - alienF3Vect.y < 20 && alienF4Vect.y - alienF3Vect.y > -20	// alien3 near
		||
		alienF4Vect.x - alienF5Vect.x < 20  && alienF4Vect.x - alienF5Vect.x > -20
		&& alienF4Vect.y - alienF5Vect.y < 20 && alienF4Vect.y - alienF5Vect.y > -20)	// alien5 near
	{
		dir4x = (spaceshipVect.x - alienF4Vect.x);
		dir4y = (spaceshipVect.y - alienF4Vect.y);
		if (alien1Speed != 0 && alien2Speed != 0 && alien3Speed != 0 && alien4Speed != 0 )
		{
			alien4Speed = 0;
		}
	}

	// if any alien is near alien5
	if (alienF5Vect.x - alienF1Vect.x < 30  && alienF5Vect.x - alienF1Vect.x > -30
		&& alienF5Vect.y - alienF1Vect.y < 30 && alienF5Vect.y - alienF1Vect.y > -30)	// alien1 near
		// steer towards alien1
	{
		dir5x = (alienF1Vect.x - alienF5Vect.x);
		dir5y = (alienF1Vect.y - alienF5Vect.y);
	}
	if (alienF5Vect.x - alienF2Vect.x < 30  && alienF5Vect.x - alienF2Vect.x > -30
		&& alienF5Vect.y - alienF2Vect.y < 30 && alienF5Vect.y - alienF2Vect.y > -30)	// alien2 near
		// steer towards alien2
	{
		dir5x = (alienF2Vect.x - alienF5Vect.x);
		dir5y = (alienF2Vect.y - alienF5Vect.y);
	}

	if (alienF5Vect.x - alienF3Vect.x < 30  && alienF5Vect.x - alienF3Vect.x > -30
		&& alienF5Vect.y - alienF3Vect.y < 30 && alienF5Vect.y - alienF3Vect.y > -30)	// alien3 near
		// steer towards alien3
	{
		dir5x = (alienF3Vect.x - alienF5Vect.x);
		dir5y = (alienF3Vect.y - alienF5Vect.y);
	}

	if (alienF5Vect.x - alienF4Vect.x < 30  && alienF5Vect.x - alienF4Vect.x > -30
		&& alienF5Vect.y - alienF4Vect.y < 30 && alienF5Vect.y - alienF4Vect.y > -30)	// alien4 near
		// steer towards alien5
	{
		dir5x = (alienF4Vect.x - alienF5Vect.x);
		dir5y = (alienF4Vect.y - alienF5Vect.y);
	}

	//if too close stop
	if (alienF5Vect.x - alienF1Vect.x < 20  && alienF5Vect.x - alienF1Vect.x > -20
		&& alienF5Vect.y - alienF1Vect.y < 20 && alienF5Vect.y - alienF1Vect.y > -20	// alien1 near
		||
		alienF5Vect.x - alienF2Vect.x < 20  && alienF5Vect.x - alienF2Vect.x > -20
		&& alienF5Vect.y - alienF2Vect.y < 20 && alienF5Vect.y - alienF2Vect.y > -20	// alien2 near
		||
		alienF5Vect.x - alienF3Vect.x < 20  && alienF5Vect.x - alienF3Vect.x > -20
		&& alienF5Vect.y - alienF3Vect.y < 20 && alienF5Vect.y - alienF3Vect.y > -20	// alien3 near
		||
		alienF5Vect.x - alienF4Vect.x < 20  && alienF5Vect.x - alienF4Vect.x > -20
		&& alienF5Vect.y - alienF4Vect.y < 20 && alienF5Vect.y - alienF4Vect.y > -20)	// alien4 near
	{
		dir5x = (spaceshipVect.x - alienF5Vect.x);
		dir5y = (spaceshipVect.y - alienF5Vect.y);
		if (alien1Speed != 0 && alien2Speed != 0 && alien3Speed != 0 && alien4Speed != 0 )
		{
			alien5Speed = 0;
		}
	}

	// alien1 movement
	float hyp1 = sqrt(dir1x*dir1x + dir1y*dir1y);
	
	dir1x /= hyp1;
	dir1y /= hyp1;

	alienF1x += dir1x*alien1Speed;
	alienF1y += dir1y*alien1Speed;
	//GetSprite().move(enemyx,enemyy);
	alien1->SetPosition(alienF1x+50,alienF1y);	

	// alien2 movement
	float hyp2 = sqrt(dir2x*dir2x + dir2y*dir2y);

	dir2x /= hyp2;
	dir2y /= hyp2;

	alienF2x += dir2x*alien2Speed;
	alienF2y += dir2y*alien2Speed;
	//GetSprite().move(enemyx,enemyy);
	alien2->SetPosition(alienF2x+225,alienF2y);

	// alien3 movement
	float hyp3 = sqrt(dir3x*dir3x + dir3y*dir3y);
	
	dir3x /= hyp3;
	dir3y /= hyp3;

	alienF3x += dir3x*alien3Speed;
	alienF3y += dir3y*alien3Speed;
	////GetSprite().move(enemyx,enemyy);
	alien3->SetPosition(alienF3x+400,alienF3y);

	// alien4 movement
	float hyp4 = sqrt(dir4x*dir4x + dir4y*dir4y);

	dir4x /= hyp4;
	dir4y /= hyp4;

	alienF4x += dir4x*alien4Speed;
	alienF4y += dir4y*alien4Speed;
	//GetSprite().move(enemyx,enemyy);
	alien4->SetPosition(alienF4x+625,alienF4y);

	// alien5 movement
	float hyp5 = sqrt(dir5x*dir5x + dir5y*dir5y);

	dir5x /= hyp5;
	dir5y /= hyp5;

	alienF5x += dir5x*alien5Speed;
	alienF5y += dir5y*alien5Speed;
	//GetSprite().move(enemyx,enemyy);
	alien5->SetPosition(alienF5x+750,alienF5y);
	
	//GetSprite().move(1,1);
	//GetSprite().move(moveTowardx,moveTowardy);
}

	//Cohesion   Have each unit steer toward the average position of its neighbors.
	//Alignment  Have each unit steer so as to align itself to the average heading of its neighbors.
	//Separation Have each unit steer to avoid hitting its neighbors

	////if alien1 a neighbour
	//if (alienf2Vect.x - alienf1Vect.x < 100  && alienf2Vect.x - alienf1Vect.x > -100
	//	&& alienf2Vect.y - alienf1Vect.y < 100 && alienf2Vect.y - alienf1Vect.y > -100)
				
	//// separation
	//if (alienf2Vect.x - alienf1Vect.x < 30 && alienf2Vect.x - alienf1Vect.x > -30
	//	&& alienf2Vect.y - alienf1Vect.y < 30 && alienf2Vect.y - alienf1Vect.y > -30)
	//{
	//	alienSpeed = 0;
	//}

						