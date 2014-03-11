#include "stdafx.h"
#include "AlienA.h"
#include "Game.h"
//#define _USE_MATH_DEFINES
//#include <cmath>
//#include <math.h>

//Spaceship * Game::player;

int offset2 = 50;

float alienA1x = 0;
float alienA1y = 0;
float alienA2x = 0;
float alienA2y = 0;
float alienA3x = 0;
float alienA3y = 0;
float alienA4x = 0;
float alienA4y = 0;
float alienA5x = 0;
float alienA5y = 0;

sf::Vector2f alienA1Vect;
sf::Vector2f alienA2Vect;
sf::Vector2f alienA3Vect;
sf::Vector2f alienA4Vect;
sf::Vector2f alienA5Vect;

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

	// load spaceship
	Spaceship* spaceship = dynamic_cast<Spaceship*>(Game::GetGameObjectsManager().Get("Spaceship"));
	sf::Vector2f spaceshipVect; 

	//for (int index = 1; index < 10; index++)
	//{
	//	//std::string s = std::to_string(index);
	//	AlienA* alien = dynamic_cast<AlienA*>(Game::GetGameObjectsManager().Get("Alien"));
	//	//alienA1Vect = alien->GetPosition();

	//	////alien1 movement
	//	//float dir1x = (spaceshipVect.x - alienA1Vect.x);
	//	//float dir1y = (spaceshipVect.y - alienA1Vect.y);
	//	//float hyp1 = sqrt(dir1x*dir1x + dir1y*dir1y);
	//	//
	//	//dir1x /= hyp1;
	//	//dir1y /= hyp1;

	//	//alienA1x += dir1x*alienSpeed;
	//	//alienA1y += dir1y*alienSpeed;
	//	//GetSprite().move(enemyx,enemyy);
	//	alien->SetPosition(50+offset2,0);
	//	offset2+50;
	//}

	
	// load aliens
	//AlienA* alien1 = dynamic_cast<AlienA*>(Game::GetGameObjectsManager().Get("Alien1"));
	//AlienA* alien2 = dynamic_cast<AlienA*>(Game::GetGameObjectsManager().Get("Alien2"));
	//AlienA* alien3 = dynamic_cast<AlienA*>(Game::GetGameObjectsManager().Get("Alien3"));
	//AlienA* alien4 = dynamic_cast<AlienA*>(Game::GetGameObjectsManager().Get("Alien4"));
	//AlienA* alien5 = dynamic_cast<AlienA*>(Game::GetGameObjectsManager().Get("Alien5"));

	//// load alien coordinates
	//alienA1Vect = alien1->GetPosition();
	//alienA2Vect = alien2->GetPosition();
	//alienA3Vect = alien3->GetPosition();
	//alienA4Vect = alien4->GetPosition();
	//alienA5Vect = alien5->GetPosition();
	
	spaceshipVect = spaceship->GetPosition();

	printf("spaceshipVect: %f, %f\n", spaceshipVect.x, spaceshipVect.y);
	printf("spaceshipVect: %f, %f\n", spaceshipVect.x, spaceshipVect.y);
	printf("spaceshipVect: %f, %f\n", spaceshipVect.x, spaceshipVect.y);
	printf("spaceshipVect: %f, %f\n", spaceshipVect.x, spaceshipVect.y);

	sf::Rect<float> spaceshipBounds = spaceship->GetBoundingRect();

	if(spaceshipBounds.intersects(GetBoundingRect()))  //(GetPosition().x + moveByX + (GetSprite().GetSize().x /2),GetPosition().y + (GetSprite().GetSize().y /2) + moveByY))
	{ 
		spaceship->reduceHealth(1);
		//Spaceship::health->reduceHealth(1);
	}

	//// alien1 movement
	//float dir1x = (spaceshipVect.x - alienA1Vect.x);
	//float dir1y = (spaceshipVect.y - alienA1Vect.y);
	//float hyp1 = sqrt(dir1x*dir1x + dir1y*dir1y);
	//
	//dir1x /= hyp1;
	//dir1y /= hyp1;

	//alienA1x += dir1x*alienSpeed;
	//alienA1y += dir1y*alienSpeed;
	////GetSprite().move(enemyx,enemyy);
	//alien1->SetPosition(alienA1x+50,alienA1y);

	// alien2 movement
	float dir2x = (spaceshipVect.x - alienA2Vect.x);
	float dir2y = (spaceshipVect.y - alienA2Vect.y);
	float hyp2 = sqrt(dir2x*dir2x + dir2y*dir2y);

	dir2x /= hyp2;
	dir2y /= hyp2;

	alienA2x += dir2x*alienSpeed;
	alienA2y += dir2y*alienSpeed;
	//GetSprite().move(enemyx,enemyy);
	//alien2->SetPosition(alienA2x+225,alienA2y);

	// alien3 movement
	float dir3x = (spaceshipVect.x - alienA3Vect.x);
	float dir3y = (spaceshipVect.y - alienA3Vect.y);
	float hyp3 = sqrt(dir3x*dir3x + dir3y*dir3y);

	dir3x /= hyp3;
	dir3y /= hyp3;


	alienA3x += dir3x*alienSpeed;
	alienA3y += dir3y*alienSpeed;
	//GetSprite().move(enemyx,enemyy);
	//alien3->SetPosition(alienA3x+400,alienA3y);

	// alien4 movement
	float dir4x = (spaceshipVect.x - alienA4Vect.x);
	float dir4y = (spaceshipVect.y - alienA4Vect.y);
	
	float hyp4 = sqrt(dir4x*dir4x + dir4y*dir4y);

	dir4x /= hyp4;
	dir4y /= hyp4;

	alienA4x += dir4x*alienSpeed;
	alienA4y += dir4y*alienSpeed;
	//GetSprite().move(enemyx,enemyy);
	//alien4->SetPosition(alienA4x+625,alienA4y);

	// alien5 movement
	float dir5x = (spaceshipVect.x - alienA5Vect.x);
	float dir5y = (spaceshipVect.y - alienA5Vect.y);
	float hyp5 = sqrt(dir5x*dir5x + dir5y*dir5y);

	dir5x /= hyp5;
	dir5y /= hyp5;

	alienA5x += dir5x*alienSpeed;
	alienA5y += dir5y*alienSpeed;
	//GetSprite().move(enemyx,enemyy);
				
	//alien5->SetPosition(alienA5x+750,alienA5y);
	
	//GetSprite().move(1,1);
	//GetSprite().move(moveTowardx,moveTowardy);
}