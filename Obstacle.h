#pragma once
#include "stdafx.h"
#include "GameObjects.h"

class Obstacle :
	public GameObjects
{
public:
	Obstacle();
	~Obstacle();

//void Update(float elapsedTime);
void Draw(sf::RenderWindow& rw);
   
sf::Vector2f GetPosition() const;
void Randomize();

private:

	sf::Vector2f position;
};