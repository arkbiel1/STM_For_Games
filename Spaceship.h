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

	float LAcc;
	float AngAcc;
	float MaxAngAcc;
	float MaxLAcc;
    float rotation;
};