#pragma once
#include "stdafx.h"
#include "GameObjects.h"

class AlienA :
	public GameObjects
{
public:
	AlienA();
	~AlienA();

void Update(float elapsedTime);
void Draw(sf::RenderWindow& rw);
   
float GetVelocity() const;

int GetAlienNo() const;

private:

	//static Spaceship * player;
	float velocity;
	int alienNo;
};