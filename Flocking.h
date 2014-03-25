#pragma once
#include "stdafx.h"
#include "GameObjects.h"

class Flocking :
	public GameObjects
{
public:
	Flocking();
	~Flocking();

void Update(float elapsedTime);
void Draw(sf::RenderWindow& rw);
   
sf::Vector2f GetVelocity() const;
int GetAlienNo() const;

private:

	float speed;
	int alienNo;
	sf::Vector2f velocity;
};