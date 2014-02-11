#include "stdafx.h"
#include "Spaceship.h"
#include "Game.h"


Spaceship::Spaceship():
	MaxAngAcc(60),
	MaxLAcc(100),
	LAcc(0),
	AngAcc(0),
	velocity(1,1),
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
		LAcc-=2;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		LAcc+=2;
	}

	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		AngAcc+=2;
		rotation++;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		AngAcc-=2;
		rotation--;
	} 

	rotation = AngAcc *elapsedTime;

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
	
	//GetSprite().setPosition(position.x, position.y +LAcc);

	//GetSprite().setPosition(position);

	//GetSprite().rotate(orientation);

	//GetSprite().setRotation(AngAcc);
	
	printf("position: %f,%f\n", position.x, position.y);

	float rotationLAcc = rotation + LAcc;
	printf("rotationLAcc: %f\n", rotationLAcc);

	printf("orientation: %f\n", orientation);

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

	printf(" LAcc: %f", LAcc);
	printf(" AngAcc: %f", AngAcc);

	//GetSprite().move(0, LAcc);

	//GetSprite().move(0, LAcc*elapsedTime);

	//printf(" Velocity: %f", velocity);
	/*printf(" ElapsedTime: %f", elapsedTime);
	printf(" LAcc: %f", LAcc);
	printf(" AngAcc: %f", AngAcc);*/



	//printf(" Acceleration: %f", acceleration);


}