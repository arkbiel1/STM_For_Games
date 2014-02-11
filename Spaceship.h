#pragma once
#include "stdafx.h"
#include "GameObjects.h"


class Spaceship :
	public GameObjects
{
public:
	Spaceship();
	~Spaceship();

void Update(float elapsedTime);
void Draw(sf::RenderWindow& rw);
   
float GetLAcc() const;
float GetAngAcc() const;

private:
	//int movement;
	float LAcc;
	float AngAcc;
	float MaxAngAcc;
	float MaxLAcc;
   
	sf::Vector2f velocity;  
   float maxSpeed;
   sf::Vector2f acceleration;  
   float maxAcceleration;
};