#pragma once
#include "stdafx.h"
#include "GameObjects.h"


class Alien :
	public GameObjects
{
public:
	Alien();
	~Alien();

void Update(float elapsedTime);
void Draw(sf::RenderWindow& rw);
   
float GetVelocity() const;

private:

	float velocity;
};