#include "stdafx.h"
#include "AlienA.h"
#include "Game.h"


//#define _USE_MATH_DEFINES
//#include <cmath>
//#include <math.h>

//Spaceship * Game::player;

using namespace std;

AlienA * AlienA::*alienNo;

int offset2 = 50;

bool initialized = false;

float alienAx = 0;
float alienAy = 0;

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

//const int alienNo2 = 10;

sf::Vector2f alienA1Vect;
sf::Vector2f alienA2Vect;
sf::Vector2f alienA3Vect;
sf::Vector2f alienA4Vect;
sf::Vector2f alienA5Vect;

float * alienAxArray = new float[0] ();
float * alienAyArray = new float[0] ();
int * alienOffsetArray = new int[0] ();

//alien3->SetPosition(150,200);

AlienA::AlienA():
	velocity(0),
	alienNo(10)
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

int AlienA::GetAlienNo() const
{
	return alienNo;
}

void AlienA::Update(float elapsedTime)
{

	float alienSpeed = 0.2;

	// array of pointer to aliens
	AlienA** alien = new AlienA*[alienNo];

	// array of vectors
	//sf::Vector2f alienVectorArray = alien[alienNo]Vector;
	sf::Vector2f* alienAVect = new sf::Vector2f[alienNo]; 

	// load spaceship
	Spaceship* spaceship = dynamic_cast<Spaceship*>(Game::GetGameObjectsManager().Get(0));
	sf::Vector2f spaceshipVect;

	if(spaceship != NULL)
	{
		
		spaceshipVect = spaceship->GetPosition();

		//printf("spaceshipVect: %f, %f\n", spaceshipVect.x, spaceshipVect.y);
		//printf("spaceshipVect: %f, %f\n", spaceshipVect.x, spaceshipVect.y);
		//printf("spaceshipVect: %f, %f\n", spaceshipVect.x, spaceshipVect.y);
		//printf("spaceshipVect: %f, %f\n", spaceshipVect.x, spaceshipVect.y);

		sf::Rect<float> spaceshipBounds = spaceship->GetBoundingRect();

		if(spaceshipBounds.intersects(GetBoundingRect()))  //(GetPosition().x + moveByX + (GetSprite().GetSize().x /2),GetPosition().y + (GetSprite().GetSize().y /2) + moveByY))
		{ 
			spaceship->reduceHealth(1);
			//Spaceship::health->reduceHealth(1);
		}

	if (initialized == false)
	{

	float * alienAxArray = new float[alienNo] ();
	float * alienAyArray = new float[alienNo] ();
	int * alienOffsetArray = new int[alienNo] ();

	//// get offset
	//for (int index = 0; index < alienNo ; index++)
	//{
	//alienOffsetArray[index] = alien[index]->GetPosition().x;
	//}

	initialized = true;
	}

	//for (int index = 0; index < alienNo ; index++)
	//{
	//	alienAxArray[index] = 0;
	//	alienAyArray[index] = 0;
	//}

	for (int index = 1; index < alienNo+1 ; index++)
	{
		//AlienA** alien[index] = AlienA*[alienNo];
		//std::string s = std::to_string(index);
		alien[index] = dynamic_cast<AlienA*>(Game::GetGameObjectsManager().Get(index));

		/*printf("[index] AlienA.cpp: %i /n", index);*/
		
		alienAVect[index] = alien[index]->GetPosition();

		//printf("alienAVect[index].x : %i /n", alienAVect[index].x);
		
		//printf("AlienAvect %i :    X: %f     Y: %f \n" +index, alienAVect[index].x, alienAVect[index].y);
		//alienA1Vect = alien->GetPosition();

		//alien movement
		float dirx = (spaceshipVect.x - alienAVect[index].x);
		float diry = (spaceshipVect.y - alienAVect[index].y);
		float hyp = sqrt(dirx*dirx + diry*diry);
		
		dirx /= hyp;
		diry /= hyp;

		alienAxArray[index] += dirx*alienSpeed;
		alienAyArray[index] += diry*alienSpeed;
		//int offset = alien[index]->GetPosition().x;
		alien[index]->SetPosition(alienAxArray[index]+20*index/*+alienOffsetArray[index]*/,alienAyArray[index]);
		//printf("AlienAvect %i :    X: %f     Y: %f \n" +index, alienAVect[index].x, alienAVect[index].y);
	}
	}	
	 

	

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

	//// alien2 movement
	//float dir2x = (spaceshipVect.x - alienA2Vect.x);
	//float dir2y = (spaceshipVect.y - alienA2Vect.y);
	//float hyp2 = sqrt(dir2x*dir2x + dir2y*dir2y);

	//dir2x /= hyp2;
	//dir2y /= hyp2;

	//alienA2x += dir2x*alienSpeed;
	//alienA2y += dir2y*alienSpeed;
	////GetSprite().move(enemyx,enemyy);
	////alien2->SetPosition(alienA2x+225,alienA2y);

	//// alien3 movement
	//float dir3x = (spaceshipVect.x - alienA3Vect.x);
	//float dir3y = (spaceshipVect.y - alienA3Vect.y);
	//float hyp3 = sqrt(dir3x*dir3x + dir3y*dir3y);

	//dir3x /= hyp3;
	//dir3y /= hyp3;


	//alienA3x += dir3x*alienSpeed;
	//alienA3y += dir3y*alienSpeed;
	////GetSprite().move(enemyx,enemyy);
	////alien3->SetPosition(alienA3x+400,alienA3y);

	//// alien4 movement
	//float dir4x = (spaceshipVect.x - alienA4Vect.x);
	//float dir4y = (spaceshipVect.y - alienA4Vect.y);
	//
	//float hyp4 = sqrt(dir4x*dir4x + dir4y*dir4y);

	//dir4x /= hyp4;
	//dir4y /= hyp4;

	//alienA4x += dir4x*alienSpeed;
	//alienA4y += dir4y*alienSpeed;
	////GetSprite().move(enemyx,enemyy);
	////alien4->SetPosition(alienA4x+625,alienA4y);

	//// alien5 movement
	//float dir5x = (spaceshipVect.x - alienA5Vect.x);
	//float dir5y = (spaceshipVect.y - alienA5Vect.y);
	//float hyp5 = sqrt(dir5x*dir5x + dir5y*dir5y);

	//dir5x /= hyp5;
	//dir5y /= hyp5;

	//alienA5x += dir5x*alienSpeed;
	//alienA5y += dir5y*alienSpeed;
	//GetSprite().move(enemyx,enemyy);
				
	//alien5->SetPosition(alienA5x+750,alienA5y);
	
	//GetSprite().move(1,1);
	//GetSprite().move(moveTowardx,moveTowardy);
}