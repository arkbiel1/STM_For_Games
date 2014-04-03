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
   
sf::Vector2f GetMVelocity() const;
sf::Vector2f GetCVelocity() const;
sf::Vector2f GetGVelocity() const;
sf::Vector2f Normalize(sf::Vector2f);
int GetAlienNo() const;

private:

	float maxSpeed;
	int alienNo;
	sf::Vector2f velocityMidd;
	sf::Vector2f velocityCurr;
	sf::Vector2f velocityGroup;
};