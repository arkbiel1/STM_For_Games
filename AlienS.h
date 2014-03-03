#pragma once
#include "stdafx.h"
#include "GameObjects.h"

class AlienS :
	public GameObjects
{
public:
	AlienS();
	~AlienS();

void Update(float elapsedTime);
void Draw(sf::RenderWindow& rw);
   
float GetVelocity() const;

private:

	//static Spaceship * player;
	float velocity;
};