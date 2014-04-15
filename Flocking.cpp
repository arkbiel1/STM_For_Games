#include "stdafx.h"
#include "Flocking.h"
#include "Game.h"
#include <omp.h>

#define PI 3.14159265

//	middle alien steer towards spaceship ->
//	average position of neibour aliens - centre of mass -> 
//	steer towards middle alien, and avoid collision

Flocking::Flocking(): maxSpeed(70), alienNo(8)
{
	//_maxVelocity(10.0f);
	Load("img/alien.png");

	//throws error window if file loading fails
	assert(IsLoaded());

	//GetSprite().setOrigin(GetSprite().getLocalBounds().width /2, GetSprite().getLocalBounds().height / 2 - 50); //50
}

Flocking::~Flocking()
{
}

void Flocking::Draw(sf::RenderWindow & rw)
{
	GameObjects::Draw(rw);
}

sf::Vector2f Flocking::GetMVelocity() const
{
	return velocityMidd;
}

sf::Vector2f Flocking::GetCVelocity() const
{
	return velocityCurr;
}

sf::Vector2f Flocking::GetGVelocity() const
{
	return velocityGroup;
}

sf::Vector2f Flocking::Normalize(sf::Vector2f velocity)
{
	 float length = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
	 if (length != 0) {
		velocity.x /= length;
		velocity.y /= length;
	 }
	 return velocity;
}

int Flocking::GetAlienNo() const
{
	return alienNo;
}

void Flocking::Update(float elapsedTime)
{
	// array of pointers to aliens
	Flocking** alien = new Flocking*[alienNo]; 

	bool direction = true;

	// load spaceship
	Spaceship* spaceship = dynamic_cast<Spaceship*>(Game::GetGameObjectsManager().Get(0));
	sf::Vector2f spaceshipPos;

	if(spaceship != NULL) {
		spaceshipPos = spaceship->GetPosition();
		sf::Rect<float> spaceshipBounds = spaceship->GetBoundingRect();

		if(spaceshipBounds.intersects(GetBoundingRect())) { //(GetPosition().x + moveByX + (GetSprite().GetSize().x /2),GetPosition().y + (GetSprite().GetSize().y /2) + moveByY))
			spaceship->reduceHealth(1);
		}

		int middleAlienInt = alienNo/2 +1;

		// middle alien movement
		if (alienNo < 3){
			middleAlienInt = 1;
		}

		alien[middleAlienInt] = dynamic_cast<Flocking*>(Game::GetGameObjectsManager().Get(middleAlienInt));
		sf::Vector2f middleAlienPos = alien[middleAlienInt]->GetPosition(); // position vector

		// head towards spaceship
		float dirx = (spaceshipPos.x - middleAlienPos.x);
		float diry = (spaceshipPos.y - middleAlienPos.y);

		// initial velocity
		sf::Vector2f velocityMidd(dirx, diry);

		// initial acceleration
		sf::Vector2f accelerationV(0.0f, 0.0f);
		sf::Vector2f separationV(0.0f, 0.0f);

		int neighbourCount = 0;
		int index = 1;
		int index2 = 1;
		#pragma omp parallel  
		#pragma omp for firstprivate(index2) lastprivate(index)
		// alien group movement
		for (index = 1 ; index < alienNo+1 ; index++) {
			alien[index] = dynamic_cast<Flocking*>(Game::GetGameObjectsManager().Get(index));
			sf::Vector2f currentAlienPos = alien[index]->GetPosition();
			
			// head towards middle spaceship
			float dirx = (middleAlienPos.x - currentAlienPos.x);
			float diry = (middleAlienPos.y - currentAlienPos.y);

			// initial velocity
			sf::Vector2f velocityGroup(dirx, diry);//(dirx+100, diry+100);
			sf::Vector2f velocityDiff(dirx, diry);
			sf::Vector2f velocitySepp(0.0f, 0.0f);
			
			// alignment & cohesion - line up & steer towards average position of neibours
			for (index2 = 1 ; index2 < alienNo+1 ; index2++) {
				if (index != index2) {//&& middleAlienInt != index2) {
				
				alien[index2] = dynamic_cast<Flocking*>(Game::GetGameObjectsManager().Get(index2));
				sf::Vector2f nextAlienPos = alien[index2]->GetPosition();

				// Calculate the difference between the two objects.
				sf::Vector2f differenceV = currentAlienPos - nextAlienPos;
				float distance1 = sqrt(differenceV.x*differenceV.x + differenceV.y*differenceV.y);
				// check for nearby aliens and steer towards them
				float neighbourDist = 100;

				if (neighbourCount == 0) velocityGroup = velocityCurr;

				// Check of the objects are closer that the collision distance.
				if (distance1 < neighbourDist) {
						neighbourCount++;
						// Calculate the difference between the two objects.
						sf::Vector2f differenceV2 = middleAlienPos - currentAlienPos;
						//float distance = sqrt(differenceV2.x*differenceV2.x + differenceV2.y*differenceV2.y);

						// when a neighbor is found, the position of the neighbour is added to the vector
						velocityGroup.x += (velocityCurr.x + differenceV2.x)*index*maxSpeed;
						velocityGroup.y += (velocityCurr.y + differenceV2.y)*index*maxSpeed;
						velocityGroup.x /= neighbourCount;
						velocityGroup.y /= neighbourCount;

						float separation = 40;
						// Check of the objects are closer that the collision distance.
						if (distance1 < separation) { 
							velocitySepp.x = currentAlienPos.x - nextAlienPos.x;
							velocitySepp.y = currentAlienPos.y - nextAlienPos.y;
							direction = false;
							}
					}
				}
			}
		

			velocityGroup += accelerationV*elapsedTime;
			if (((velocityGroup.x*velocityGroup.x)+(velocityGroup.y*velocityGroup.y))>maxSpeed*maxSpeed) {
				velocityGroup = Flocking::Normalize(velocityGroup);
				velocityGroup *= maxSpeed;
			}

			velocityDiff += accelerationV*elapsedTime;
			if (((velocityDiff.x*velocityDiff.x)+(velocityDiff.y*velocityDiff.y))>maxSpeed*maxSpeed) {
				velocityDiff = Flocking::Normalize(velocityDiff);
				velocityDiff *= maxSpeed;
			}

			if(direction == false && index != middleAlienInt) {
				velocityGroup = velocitySepp;
				velocityGroup += accelerationV*elapsedTime;
				velocityGroup *= -1.0f;
				if (((velocityGroup.x*velocityGroup.x)+(velocityGroup.y*velocityGroup.y))>maxSpeed*maxSpeed) {
				velocityGroup = Flocking::Normalize(velocityGroup);
				velocityGroup *= maxSpeed;
				}
				velocityGroup += velocityDiff;
				velocityGroup *= -1.0f;
			}

			if(direction == false && index == middleAlienInt) {
				velocityMidd += accelerationV*elapsedTime;
				if (((velocityMidd.x*velocityMidd.x)+(velocityMidd.y*velocityMidd.y))>maxSpeed*maxSpeed) {
				velocityMidd = Flocking::Normalize(velocityMidd);
				velocityMidd *= maxSpeed;
				}
			}

			else {
			velocityMidd += accelerationV*elapsedTime;
			if (((velocityMidd.x*velocityMidd.x)+(velocityMidd.y*velocityMidd.y))>maxSpeed*maxSpeed) {
				velocityMidd = Flocking::Normalize(velocityMidd);
				velocityMidd *= maxSpeed;
				}
			}

			alien[middleAlienInt]->SetPosition(middleAlienPos.x + velocityMidd.x*elapsedTime/alienNo,
			middleAlienPos.y + velocityMidd.y*elapsedTime/alienNo);

			//printf("\n");
			if (index != middleAlienInt) {
			alien[index]->SetPosition(currentAlienPos.x + (velocityGroup.x)*elapsedTime/alienNo
														+ (velocityDiff.x)*elapsedTime/alienNo,
									  currentAlienPos.y + (velocityGroup.y)*elapsedTime/alienNo
														+ (velocityDiff.y)*elapsedTime/alienNo);
			}
		  }
	} 
}