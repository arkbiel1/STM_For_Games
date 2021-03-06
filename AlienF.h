#pragma once
#include "stdafx.h"
#include "GameObjects.h"

class AlienF :
	public GameObjects
{
public:
	AlienF();
	~AlienF();

void Update(float elapsedTime);
void Draw(sf::RenderWindow& rw);
   
float GetVelocity() const;
int GetAlienNo() const;

private:

	float speed;
	int alienNo;
};