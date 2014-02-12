#include "stdafx.h"
#include "Spaceship.h"
#include "Game.h"
#define _USE_MATH_DEFINES
//#include <cmath>
#include <math.h>


Spaceship::Spaceship():
	MaxAngAcc(80),
	MaxLAcc(150),
	LAcc(0),
	AngAcc(0),
	rotation(0)
	//maxSpeed(100.0)
	//acceleration(0,0), 
	//maxAcceleration(100.0)
	//movement(0)
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
		AngAcc-=4;
		rotation-=2;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		AngAcc+=4;
		rotation+=2;
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


	printf(" LAcc: %f \n", LAcc);
	printf(" AngAcc: %f \n", AngAcc);
	printf("position: %f,%f \n", position.x, position.y);
	//printf("rotationLAcc: %f \n", rotationLAcc);
	printf("orientation: %f \n", orientation);

	printf("rotation: %f\n", rotation);
	printf("speed: %f\n", speed);

	

	printf("SCREEN_WIDTH: %int \n ", Game::SCREEN_WIDTH);
	printf("SCREEN_HEIGHT: %int \n ", Game::SCREEN_HEIGHT);

	GetSprite().move(movementX, movementY);


	if(position.x > Game::SCREEN_WIDTH)
	{
		position.x = Game::SCREEN_WIDTH; 
	}

	if(position.x < 0)
	{
		position.x = 0; 
	}

	if(position.y > Game::SCREEN_HEIGHT)
	{
		position.y = Game::SCREEN_HEIGHT; 
	}

	if(position.y < 0)
	{
		position.y = 0; 
	}

	//position = position + velocity * elapsedTime;



	//float movementY += speed * Math.Sin(angle);

	//float velocity = 0;
	// Rotation

	// LAcc		behavious update these
	// AngAcc	MaxLAcc MaxAngAcc

	//velocity.x = velocity.x, velocity.y;

	//position.x = (velocity.x -LAcc *elapsedTime);

	//velocity.x = (velocity.x + LAcc * elapsedTime);

	//velocity.y = (velocity.x + AngAcc * elapsedTime);

	//printf("velocity: %f,%f\n", velocity.x, velocity.y);

	// Rotation = Rotation + AngAcc * elapsedTime (in sec)
	//position = position + velocity * elapsedTime;
	
	//GetSprite().setPosition(100, movementY);

	//GetSprite().move(movementX, movementY);

	//GetSprite().setPosition(position);

	//GetSprite().rotate(orientation);

	//GetSprite().setRotation(AngAcc);
	
	// Orientation = Orientation + Rotation * elapsedTime (in sec)

	//sf::Vector2f pos = this->GetPosition();

	//if(pos.x  < GetSprite().getLocalBounds().width/2 || pos.x > (Game::SCREEN_WIDTH - GetSprite().getLocalBounds().width/2))
	//{
	//	_velocity = -_velocity; // Bounce by current velocity in opposite direction
	//}


	GetSprite().rotate(rotation);


	if(rotation > 0)
		rotation--;

	if(rotation < 0)
		rotation++;



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

	

	//GetSprite().move(0, LAcc);

	//GetSprite().move(0, LAcc*elapsedTime);

	//printf(" Velocity: %f", velocity);
	/*printf(" ElapsedTime: %f", elapsedTime);
	printf(" LAcc: %f", LAcc);
	printf(" AngAcc: %f", AngAcc);*/



	//printf(" Acceleration: %f", acceleration);


}