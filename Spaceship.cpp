#include "stdafx.h"
#include "Spaceship.h"
#include "Game.h"
#define _USE_MATH_DEFINES
//#include <cmath>
#include <math.h>


Spaceship::Spaceship():
	MaxAngAcc(60),
	MaxLAcc(150),
	LAcc(0),
	AngAcc(0),
	rotation(0)
{
	//_maxVelocity(10.0f);
	Load("img/spaceship.png");

	//throws error window if file loading fails
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getLocalBounds().width /2, GetSprite().getLocalBounds().height / 2 - 50);
}

Spaceship::~Spaceship()
{
}

void Spaceship::Draw(sf::RenderWindow & rw)
{
	GameObjects::Draw(rw);
}

float Spaceship::GetLAcc() const
{
	return LAcc;
}

float Spaceship::GetAngAcc() const
{
	return AngAcc;
}



void Spaceship::Update(float elapsedTime)
{

	// Position

	sf::Vector2f position = GetSprite().getPosition(); // position vector

	//printf(" positionX: %f", positionX);

	// Orientation

	float orientation = GetSprite().getRotation(); // angle

	//printf(" orientation: %f", orientation);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		LAcc+=15;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		LAcc-=15;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		AngAcc-=10;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		AngAcc+=10;
	} 

	rotation = AngAcc *elapsedTime;

	float speed = LAcc *elapsedTime;

	float orientInRad = (M_PI/ 180) * (orientation -90) ;
	
	// convert to radians
	//pos.Z += PLAYER_SPEED * cos(roty_rad);
	//pos.X += PLAYER_SPEED * sin(roty_rad);


	float movementX = cos(orientInRad)*speed;

	float movementY = sin(orientInRad)*speed;

	
	//float rotationLAcc = rotation + LAcc;

	//printf(" movementX: %f \n", movementX);
	//printf(" movementY: %f \n", movementY);


	printf(" LAcc: %f\n", LAcc);
	printf(" AngAcc: %f\n", AngAcc);
	printf(" position: %f,%f\n", position.x, position.y);
	//printf("rotationLAcc: %f \n", rotationLAcc);
	printf(" orientation: %f\n", orientation);

	printf(" rotation: %f\n", rotation);
	printf(" speed: %f\n", speed);


	printf(" SCREEN_WIDTH: %i\n ", Game::SCREEN_WIDTH);
	printf(" SCREEN_HEIGHT: %i\n ", Game::SCREEN_HEIGHT);

	float localbx = GetSprite().getLocalBounds().width/8;
	float localby = GetSprite().getLocalBounds().height/8;

	printf(" localbx: %f\n", localbx);
	printf(" localby: %f\n", localby);


	if(position.x < localbx)
	{
		LAcc = 0; 
		//LAcc = 0; 
		movementX = 1.5; 
	}

	if(position.x > (Game::SCREEN_WIDTH - localbx))
	{
		LAcc = 0; 
		//LAcc = 0; 
		movementX = -1.5; 
	}

	if(position.y < localby)
	{
		LAcc = 0; 
		//LAcc = 0; 
		movementY = 1.5; 
	}

	if(position.y > (Game::SCREEN_HEIGHT - localby))
	{
		LAcc = 0; 
		//LAcc = 0; 
		movementY = -1.5; 
	}
	//sf::Vector2f pos = this->GetPosition();

	//if(pos.x  < GetSprite().getLocalBounds().width/2 || pos.x > (Game::SCREEN_WIDTH - GetSprite().getLocalBounds().width/2))
	//{
	//	_velocity = -_velocity; // Bounce by current velocity in opposite direction
	//}


	GetSprite().move(movementX, movementY);


	GetSprite().rotate(rotation);


	if(LAcc > 0)
		LAcc--;

	if(LAcc < 0)
		LAcc++;

	if(LAcc > MaxLAcc)
		LAcc = MaxLAcc;

	if(LAcc < -100)
		LAcc = -100; 



	if(AngAcc > 0)
		AngAcc--;

	if(AngAcc < 0)
		AngAcc++;

	if(AngAcc > MaxAngAcc)
		AngAcc = MaxAngAcc;

	if(AngAcc < -50)
		AngAcc = -50; 

}