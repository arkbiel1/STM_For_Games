#pragma once
#include "stdafx.h"
#include "GameObjects.h"

class Swarming :
	public GameObjects
{
public:
	Swarming();
	~Swarming();

void Update(float elapsedTime);
void Draw(sf::RenderWindow& rw);
   
sf::Vector2f GetVelocity() const;
sf::Vector2f Normalize(sf::Vector2f);
int GetAlienNo() const;

private:

	float maxSpeed;
	int alienNo;
	sf::Vector2f velocityV;
};