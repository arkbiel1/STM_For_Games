#pragma once
#include "stdafx.h"
#include "GameObjects.h"


class Alien2 :
	public GameObjects
{
public:
	Alien2();
	~Alien2();

void Update(float elapsedTime);
void Draw(sf::RenderWindow& rw);
   
float GetVelocity() const;

private:

	float velocity;
};