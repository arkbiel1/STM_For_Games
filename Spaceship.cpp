#include "stdafx.h"
#include "Spaceship.h"
#include "Game.h"


Spaceship::Spaceship():
	MaxAngAcc(30),
	MaxLAcc(30),
	LAcc(0),
	AngAcc(0),
	velocity(1,1), 
	maxSpeed(100.0),
	acceleration(0,0), 
	maxAcceleration(100.0)
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

	sf::Vector2f position = GetSprite().getPosition();

	//printf(" positionX: %f", positionX);

	// Orientation

	float orientation = GetSprite().getRotation();
	//printf(" orientation: %f", orientation);


	//float velocity = 0;
	// Rotation

	// LAcc		behavious update these
	// AngAcc	MaxLAcc MaxAngAcc

	// Velocity = Velocity + LAcc * elapsedTime (in sec)
	// Rotation = Rotation + AngAcc * elapsedTime (in sec)
	position = position + velocity * elapsedTime;
	GetSprite().setPosition(position.x, position.y);
	printf("position: %f,%f\n", position.x,position.y);
	// Orientation = Orientation + Rotation * elapsedTime (in sec)



	/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		//int leftBoundry = GetSprite().getPosition().x;
		//if (leftBoundry > 42)
		//	GetSprite().move(-10,0);
		positionX--;
		
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		//int rightBoundry = GetSprite().getPosition().x;
		//if (rightBoundry < 982)
			//GetSprite().move(10,0);
		positionX++;
	}*/

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		LAcc-=2;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		LAcc+=2;
	}  

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		AngAcc--;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		AngAcc++;
	} 

	/*if(velocity > maxVelocity)
		velocity = maxVelocity;

	if(velocity < 0)
		velocity = 0;

	if(acceleration > maxAcceleration)
		acceleration = maxAcceleration;

	if(acceleration < -100)
		acceleration = -100; */


	//sf::Vector2f pos = this->GetPosition();

	//if(pos.x  < GetSprite().getLocalBounds().width/2 || pos.x > (Game::SCREEN_WIDTH - GetSprite().getLocalBounds().width/2))
	//{
	//	_velocity = -_velocity; // Bounce by current velocity in opposite direction
	//}
	
	//GetSprite().move(0, velocity);

	if(LAcc > 300)
		LAcc = MaxLAcc;

	if(LAcc < -30)
		LAcc = -30; 

	if(AngAcc > 100)
		LAcc = MaxLAcc;

	if(AngAcc < -100)
		AngAcc = -100; 

	
	//GetSprite().move(0, LAcc);

	//GetSprite().move(0, LAcc*elapsedTime);

	//printf(" Velocity: %f", velocity);
	/*printf(" ElapsedTime: %f", elapsedTime);
	printf(" LAcc: %f", LAcc);
	printf(" AngAcc: %f", AngAcc);*/



	//printf(" Acceleration: %f", acceleration);


}