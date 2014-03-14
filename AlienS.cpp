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
	float alien1Speed = 0.2;
	float alien2Speed = 0;
	float alien3Speed = 0;
	float alien4Speed = 0;
	//float alien5Speed = 0;

	//// load spaceship
	//Spaceship* spaceship = dynamic_cast<Spaceship*>(Game::GetGameObjectsManager().Get("Spaceship"));
	//sf::Vector2f spaceshipVect; 

	//// load aliens
	//AlienS* alien1 = dynamic_cast<AlienS*>(Game::GetGameObjectsManager().Get("Alien1"));
	//AlienS* alien2 = dynamic_cast<AlienS*>(Game::GetGameObjectsManager().Get("Alien2"));
	//AlienS* alien3 = dynamic_cast<AlienS*>(Game::GetGameObjectsManager().Get("Alien3"));
	//AlienS* alien4 = dynamic_cast<AlienS*>(Game::GetGameObjectsManager().Get("Alien4"));
	//AlienS* alien5 = dynamic_cast<AlienS*>(Game::GetGameObjectsManager().Get("Alien5"));

//	// load alien coordinates
//	alienS1Vect = alien1->GetPosition();
//	alienS2Vect = alien2->GetPosition();
//	alienS3Vect = alien3->GetPosition();
//	alienS4Vect = alien4->GetPosition();
//	alienS5Vect = alien5->GetPosition();
//	
//	spaceshipVect = spaceship->GetPosition();
//
//	/*printf("spaceshipVect: %f, %f\n", spaceshipVect.x, spaceshipVect.y);
//	printf("spaceshipVect: %f, %f\n", spaceshipVect.x, spaceshipVect.y);
//	printf("spaceshipVect: %f, %f\n", spaceshipVect.x, spaceshipVect.y);
//	printf("spaceshipVect: %f, %f\n", spaceshipVect.x, spaceshipVect.y);*/
//
//	sf::Rect<float> spaceshipBounds = spaceship->GetBoundingRect();
//
//	if(spaceshipBounds.intersects(GetBoundingRect()))  //(GetPosition().x + moveByX + (GetSprite().GetSize().x /2),GetPosition().y + (GetSprite().GetSize().y /2) + moveByY))
//	{ 
//		spaceship->reduceHealth(1);
//		//Spaceship::health->reduceHealth(1);
//	}
//
//	// if any alien is near alien2
//	if (alienS2Vect.x - alienS1Vect.x < 100  && alienS2Vect.x - alienS1Vect.x > -100
//		&& alienS2Vect.y - alienS1Vect.y < 100 && alienS2Vect.y - alienS1Vect.y > -100	// alien1 near
//		||
//		alienS2Vect.x - alienS3Vect.x < 100  && alienS2Vect.x - alienS3Vect.x > -100
//		&& alienS2Vect.y - alienS3Vect.y < 100 && alienS2Vect.y - alienS3Vect.y > -100	// alien3 near
//		||
//		alienS2Vect.x - alienS4Vect.x < 100  && alienS2Vect.x - alienS4Vect.x > -100
//		&& alienS2Vect.y - alienS4Vect.y < 100 && alienS2Vect.y - alienS4Vect.y > -100	// alien4 near
//		||
//		alienS2Vect.x - alienS5Vect.x < 100  && alienS2Vect.x - alienS5Vect.x > -100
//		&& alienS2Vect.y - alienS5Vect.y < 100 && alienS2Vect.y - alienS5Vect.y > -100)	// alien5 near
//	{
//		alien2Speed = 0.2;
//	}
//
//	// if any alien is near alien3
//	if (alienS3Vect.x - alienS1Vect.x < 100  && alienS3Vect.x - alienS1Vect.x > -100
//		&& alienS3Vect.y - alienS1Vect.y < 100 && alienS3Vect.y - alienS1Vect.y > -100	// alien1 near
//		||
//		alienS3Vect.x - alienS2Vect.x < 100  && alienS3Vect.x - alienS2Vect.x > -100
//		&& alienS3Vect.y - alienS2Vect.y < 100 && alienS3Vect.y - alienS2Vect.y > -100	// alien2 near
//		||
//		alienS3Vect.x - alienS4Vect.x < 100  && alienS3Vect.x - alienS4Vect.x > -100
//		&& alienS3Vect.y - alienS4Vect.y < 100 && alienS3Vect.y - alienS4Vect.y > -100	// alien4 near
//		||
//		alienS3Vect.x - alienS5Vect.x < 100  && alienS3Vect.x - alienS5Vect.x > -100
//		&& alienS3Vect.y - alienS5Vect.y < 100 && alienS3Vect.y - alienS5Vect.y > -100)	// alien5 near
//	{
//		alien3Speed = 0.2;
//	}
//
//	// if any alien is near alien4
//	if (alienS4Vect.x - alienS1Vect.x < 100  && alienS4Vect.x - alienS1Vect.x > -100
//		&& alienS4Vect.y - alienS1Vect.y < 100 && alienS4Vect.y - alienS1Vect.y > -100	// alien1 near
//		||
//		alienS4Vect.x - alienS2Vect.x < 100  && alienS4Vect.x - alienS2Vect.x > -100
//		&& alienS4Vect.y - alienS2Vect.y < 100 && alienS4Vect.y - alienS2Vect.y > -100	// alien2 near
//		||
//		alienS4Vect.x - alienS3Vect.x < 100  && alienS4Vect.x - alienS3Vect.x > -100
//		&& alienS4Vect.y - alienS3Vect.y < 100 && alienS4Vect.y - alienS3Vect.y > -100	// alien3 near
//		||
//		alienS4Vect.x - alienS5Vect.x < 100  && alienS4Vect.x - alienS5Vect.x > -100
//		&& alienS4Vect.y - alienS5Vect.y < 100 && alienS4Vect.y - alienS5Vect.y > -100)	// alien5 near
//	{
//		alien4Speed = 0.2;
//	}
//
//	// if any alien is near alien5
//	if (alienS5Vect.x - alienS1Vect.x < 100  && alienS5Vect.x - alienS1Vect.x > -100
//		&& alienS5Vect.y - alienS1Vect.y < 100 && alienS5Vect.y - alienS1Vect.y > -100	// alien1 near
//		||
//		alienS5Vect.x - alienS2Vect.x < 100  && alienS5Vect.x - alienS2Vect.x > -100
//		&& alienS5Vect.y - alienS2Vect.y < 100 && alienS5Vect.y - alienS2Vect.y > -100	// alien2 near
//		||
//		alienS5Vect.x - alienS3Vect.x < 100  && alienS5Vect.x - alienS3Vect.x > -100
//		&& alienS5Vect.y - alienS3Vect.y < 100 && alienS5Vect.y - alienS3Vect.y > -100	// alien3 near
//		||
//		alienS5Vect.x - alienS4Vect.x < 100  && alienS5Vect.x - alienS4Vect.x > -100
//		&& alienS5Vect.y - alienS4Vect.y < 100 && alienS5Vect.y - alienS4Vect.y > -100)	// alien4 near
//	{
//		alien5Speed = 0.2;
//	}
//	
//
//	// alien1 movement
//	float dir1x = (spaceshipVect.x - alienS1Vect.x);
//	float dir1y = (spaceshipVect.y - alienS1Vect.y);
//	float hyp1 = sqrt(dir1x*dir1x + dir1y*dir1y);
//	
//	dir1x /= hyp1;
//	dir1y /= hyp1;
//
//	alienS1x += dir1x*alien1Speed;
//	alienS1y += dir1y*alien1Speed;
//	//GetSprite().move(enemyx,enemyy);
//	alien1->SetPosition(alienS1x+50,alienS1y);
//
//	// alien2 movement
//	float dir2x = (spaceshipVect.x - alienS2Vect.x);
//	float dir2y = (spaceshipVect.y - alienS2Vect.y);
//	float hyp2 = sqrt(dir2x*dir2x + dir2y*dir2y);
//
//	dir2x /= hyp2;
//	dir2y /= hyp2;
//
//	alienS2x += dir2x*alien2Speed;
//	alienS2y += dir2y*alien2Speed;
//	//GetSprite().move(enemyx,enemyy);
//	alien2->SetPosition(alienS2x+225,alienS2y);
//
//	// alien3 movement
//	float dir3x = (spaceshipVect.x - alienS3Vect.x);
//	float dir3y = (spaceshipVect.y - alienS3Vect.y);
//	float hyp3 = sqrt(dir3x*dir3x + dir3y*dir3y);
//
//	dir3x /= hyp3;
//	dir3y /= hyp3;
//
//
//	alienS3x += dir3x*alien3Speed;
//	alienS3y += dir3y*alien3Speed;
//	//GetSprite().move(enemyx,enemyy);
//	alien3->SetPosition(alienS3x+400,alienS3y);
//
//	// alien4 movement
//	float dir4x = (spaceshipVect.x - alienS4Vect.x);
//	float dir4y = (spaceshipVect.y - alienS4Vect.y);
//	
//	float hyp4 = sqrt(dir4x*dir4x + dir4y*dir4y);
//
//	dir4x /= hyp4;
//	dir4y /= hyp4;
//
//	alienS4x += dir4x*alien4Speed;
//	alienS4y += dir4y*alien4Speed;
//	//GetSprite().move(enemyx,enemyy);
//	alien4->SetPosition(alienS4x+625,alienS4y);
//
//	// alien5 movement
//	float dir5x = (spaceshipVect.x - alienS5Vect.x);
//	float dir5y = (spaceshipVect.y - alienS5Vect.y);
//	float hyp5 = sqrt(dir5x*dir5x + dir5y*dir5y);
//
//	dir5x /= hyp5;
//	dir5y /= hyp5;
//
//	alienS5x += dir5x*alien5Speed;
//	alienS5y += dir5y*alien5Speed;
//	//GetSprite().move(enemyx,enemyy);
//				
//	alien5->SetPosition(alienS5x+750,alienS5y);
//	
//	//GetSprite().move(1,1);
//	//GetSprite().move(moveTowardx,moveTowardy);
//}
//
//	//Cohesion   Have each unit steer toward the average position of its neighbors.
//	//Alignment  Have each unit steer so as to align itself to the average heading of its neighbors.
//	//Separation Have each unit steer to avoid hitting its neighbors
//
//	////if alien1 a neighbour
//	//if (alienS2Vect.x - alienS1Vect.x < 100  && alienS2Vect.x - alienS1Vect.x > -100
//	//	&& alienS2Vect.y - alienS1Vect.y < 100 && alienS2Vect.y - alienS1Vect.y > -100)
//				
//	//// separation
//	//if (alienS2Vect.x - alienS1Vect.x < 30 && alienS2Vect.x - alienS1Vect.x > -30
//	//	&& alienS2Vect.y - alienS1Vect.y < 30 && alienS2Vect.y - alienS1Vect.y > -30)
//	//{
//	//	alienSpeed = 0;
//	//}
}
						