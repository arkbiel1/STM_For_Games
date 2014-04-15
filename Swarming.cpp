#include "stdafx.h"
#include "Swarming.h"
#include "Game.h"
#include <omp.h>

#define PI 3.14159265


// average position of all aliens - centre of mass -> steer towards spaceship, avoid collision and steer randomly if too close

Swarming::Swarming(): maxSpeed(70), alienNo(15)
{
	//_maxVelocity(10.0f);
	Load("img/alien.png");

	//throws error window if file loading fails
	assert(IsLoaded());

	//GetSprite().setOrigin(GetSprite().getLocalBounds().width /2, GetSprite().getLocalBounds().height / 2 - 50); //50
}

Swarming::~Swarming()
{
}

void Swarming::Draw(sf::RenderWindow & rw)
{
	GameObjects::Draw(rw);
}

sf::Vector2f Swarming::GetVelocity() const
{
	return velocityV;
}

sf::Vector2f Swarming::Normalize(sf::Vector2f velocity)
{
	 float length = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
	 if (length != 0) {
		velocity.x /= length;
		velocity.y /= length;
	 }
	 return velocity;
}

int Swarming::GetAlienNo() const
{
	return alienNo;
}

void Swarming::Update(float elapsedTime)
{
	// array of pointers to aliens
	Swarming** alien = new Swarming*[alienNo]; 

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

		
		// initial velocity
		sf::Vector2f velocityGroup(0.0f, 0.0f);
		sf::Vector2f velocityAvg(0.0f, 0.0f);
		sf::Vector2f centerOfMassV(0.0f, 0.0f);
		sf::Vector2f centerOfMassPos(0.0f, 0.0f);
		sf::Vector2f velocitySepp(0.0f, 0.0f);
		sf::Vector2f velocityRandom(0.0f, 0.0f);
		// velocity steers towards spaceship
		//velocityGroup.x = (spaceshipPos.x - velocityGroup.x);
		//velocityGroup.y = (spaceshipPos.y - velocityGroup.y);

		// initial acceleration
		sf::Vector2f accelerationV(0.0f, 0.0f);
		// initial velocity
		//sf::Vector2f centerOfMassV(0.0f, 0.0f);
		sf::Vector2f velocityToShip(0.0f, 0.0f);
		//sf::Vector2f velocitySepp(0.0f, 0.0f);
		
		//#pragma omp parallel    
		//#pragma omp parallel for
		// alien group movement - first part get average velocity
		for (int index = 1; index < alienNo+1 ; index++) {
			// current alien position
			alien[index] = dynamic_cast<Swarming*>(Game::GetGameObjectsManager().Get(index));
			sf::Vector2f currentAlienPos = alien[index]->GetPosition();

			// add every alien to the average position of the group
			velocityGroup += currentAlienPos;

			//printf("currentAlienPos.x: %f, index: %i\n", currentAlienPos.x, index);
			//printf("velocityGroup.y: %f, index: %i\n", velocityGroup.y, index);
		}

		velocityAvg.x = velocityGroup.x/alienNo;
		velocityAvg.y = velocityGroup.y/alienNo;

		centerOfMassPos.x = velocityGroup.x/alienNo;
		centerOfMassPos.y = velocityGroup.y/alienNo;

		int index = 1;
		int index2 = 1;

		#pragma omp parallel    
		#pragma omp for firstprivate(index2) lastprivate(index)
		// alien group movement - second part move towards average velocity
		for (int index = 1; index < alienNo+1 ; index++) {
			// current alien position
			alien[index] = dynamic_cast<Swarming*>(Game::GetGameObjectsManager().Get(index));
			sf::Vector2f currentAlienPos = alien[index]->GetPosition();

			// head towards average velocity
			float dirx = (velocityAvg.x - currentAlienPos.x);
			float diry = (velocityAvg.y - currentAlienPos.y);

			sf::Vector2f centerOfMassV(dirx, diry);
			dirx = (spaceshipPos.x - centerOfMassPos.x);
			diry = (spaceshipPos.y - centerOfMassPos.y);

			sf::Vector2f velocityDiff(dirx, diry);
			sf::Vector2f velocityToShip(dirx, diry);

			//#pragma omp parallel for
			for (int index2 = 1; index2 < alienNo+1 ; index2++) {
				if (index != index2) {//&& middleAlienInt != index2) {
				
				alien[index2] = dynamic_cast<Swarming*>(Game::GetGameObjectsManager().Get(index2));
				sf::Vector2f nextAlienPos = alien[index2]->GetPosition();

				// Calculate the difference between the two objects.
				sf::Vector2f differenceV = currentAlienPos - nextAlienPos;
				float distance1 = sqrt(differenceV.x*differenceV.x + differenceV.y*differenceV.y);
				float separation = 50;

				// random y velocity for each alien in a swarm
				if (distance1 < 200) { 
					velocityRandom.y = spaceshipPos.y - (rand()+50) % (1000);
					}

				// Check of the objects are closer that the collision distance.
				if (distance1 < separation) { 
					velocitySepp.x = currentAlienPos.x - nextAlienPos.x;
					velocitySepp.y = currentAlienPos.y - nextAlienPos.y;
					direction = false;						
					}
				}
			}

			velocityToShip += accelerationV*elapsedTime;
			if (((velocityToShip.x*velocityToShip.x)+(velocityToShip.y*velocityToShip.y))>maxSpeed*maxSpeed) {
				velocityToShip = Swarming::Normalize(velocityToShip);
				velocityToShip *= maxSpeed;
			}

			velocitySepp += accelerationV*elapsedTime;
			if (((velocitySepp.x*velocitySepp.x)+(velocitySepp.y*velocitySepp.y))>maxSpeed*maxSpeed) {
				velocitySepp = Swarming::Normalize(velocitySepp);
				velocitySepp *= maxSpeed;
			}

			velocityRandom += velocityRandom*elapsedTime;
			if (((velocityRandom.x*velocityRandom.x)+(velocityRandom.y*velocityRandom.y))>maxSpeed*maxSpeed) {
				velocityRandom = Swarming::Normalize(velocityRandom);
				velocityRandom *= maxSpeed;
			}

			velocityDiff += accelerationV*elapsedTime;
			if (((velocityDiff.x*velocityDiff.x)+(velocityDiff.y*velocityDiff.y))>maxSpeed*maxSpeed) {
				velocityDiff = Swarming::Normalize(velocityDiff);
				velocityDiff *= maxSpeed;
			}

			if(direction == false) {
				centerOfMassV = velocitySepp;
				centerOfMassV += accelerationV*elapsedTime;
				centerOfMassV *= -1.0f;
				if (((centerOfMassV.x*centerOfMassV.x)+(centerOfMassV.y*centerOfMassV.y))>maxSpeed*maxSpeed) {
				centerOfMassV = Swarming::Normalize(centerOfMassV);
				centerOfMassV *= maxSpeed;
				}
				centerOfMassV += velocitySepp;
				centerOfMassV *= -1.0f;
			}

			else {
			centerOfMassV += accelerationV*elapsedTime;
			if (((centerOfMassV.x*centerOfMassV.x)+(centerOfMassV.y*centerOfMassV.y))>maxSpeed*maxSpeed) {
				centerOfMassV = Swarming::Normalize(centerOfMassV);
				centerOfMassV *= maxSpeed;
				}
			}
			alien[index]->SetPosition(currentAlienPos.x + (centerOfMassV.x)*elapsedTime/alienNo
														+ (velocityToShip.x)*elapsedTime/alienNo,
									  currentAlienPos.y + (centerOfMassV.y)*elapsedTime/alienNo
														+ (velocityToShip.y)*elapsedTime/alienNo
														+ (velocityRandom.y)*elapsedTime/alienNo);
		  }

		//} // end pragma openmp
	}
}