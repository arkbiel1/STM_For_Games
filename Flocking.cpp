#include "stdafx.h"
#include "Flocking.h"
#include "Game.h"

#define PI 3.14159265

//	middle alien steer towards spaceship ->
//	average position of neibour aliens - centre of mass -> 
//	steer towards middle alien, and avoid collision

Flocking::Flocking(): maxSpeed(70), alienNo(4)
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

		//float initPosx = alienMiddGetPos.x;
		//float initPosy = alienMiddGetPos.y;

		//float hyp = sqrt(dirx*dirx + diry*diry);
		//dirx /= hyp;
		//diry /= hyp;

		// initial velocity
		sf::Vector2f velocityMidd(dirx, diry);
		// initial acceleration
		sf::Vector2f accelerationV(0.0f, 0.0f);

		velocityMidd += accelerationV*elapsedTime;
		if (((velocityMidd.x*velocityMidd.x)+(velocityMidd.y*velocityMidd.y))>maxSpeed*maxSpeed) {
			velocityMidd = Flocking::Normalize(velocityMidd);
			velocityMidd *= maxSpeed;
		}

		alien[middleAlienInt]->SetPosition(middleAlienPos.x + velocityMidd.x*elapsedTime/alienNo,
			middleAlienPos.y + velocityMidd.y*elapsedTime/alienNo);
		
		int neighbourCount = 0;

		// alien group movement
		for (int index = 1; index < alienNo+1 ; index++) {
			// except middle alien
			//if (index != middleAlienInt) {
			// current alien position
			alien[index] = dynamic_cast<Flocking*>(Game::GetGameObjectsManager().Get(index));
			sf::Vector2f currentAlienPos = alien[index]->GetPosition();
			
			// initial velocity
			sf::Vector2f velocityCurr(velocityMidd.x, velocityMidd.y);
			sf::Vector2f velocityGroup(velocityCurr.x, velocityCurr.y);
			//sf::Vector2f velocityGroupCoh(0.0f, 0.0f);

			// alignment & cohesion - line up & steer towards average position of neibours
			for (int index2 = 1; index2 < alienNo+1 ; index2++) {
				if (index != index2) {//&& middleAlienInt != index2) {
				
				alien[index2] = dynamic_cast<Flocking*>(Game::GetGameObjectsManager().Get(index2));
				sf::Vector2f nextAlienPos = alien[index2]->GetPosition();

				// Calculate the difference between the two objects.
				sf::Vector2f differenceV = currentAlienPos - nextAlienPos;
				float distance = sqrt(differenceV.x*differenceV.x + differenceV.y*differenceV.y);
				// check for nearby aliens and steer towards them
				float neighbourDist = 50;

				if (neighbourCount == 0) velocityGroup = velocityCurr;

				// Check of the objects are closer that the collision distance.
				if (distance < neighbourDist) {
						neighbourCount++;
						// when a neighbor is found, the position of the neighbour is added to the vector
						velocityGroup.x += velocityCurr.x;
						velocityGroup.y += velocityCurr.y;

						velocityGroup.x /= neighbourCount;
						velocityGroup.y /= neighbourCount;

						// vector is divided by the neighbor count, resulting in the position that corresponds to the center of mass

						// direction towards the center of mass
						//sf::Vector2f centerOfMassV(velocityV2.x - currentAlienPos.x, velocityV2.y - currentAlienPos.y);
						//centerOfMassV = Flocking::Normalize(centerOfMassV);
						//velocityV2.x = velocityV2.x - currentAlienPos.x;
						//velocityV2.y = velocityV2.y - currentAlienPos.y;
						//printf("neibourCount alien[%i]: %i\n", index, neighbourCount);
						//printf("centerOfMassV X: %f,  Y: %f\n", centerOfMassV.x, centerOfMassV.y);
						//centerOfMassV += velocityV;
						//velocityV2 += centerOfMassV;
					   //}
					}


				}
			}

			// separation
			for (int index2 = 1; index2 < alienNo+1 ; index2++) {
				if (index != index2 && index2 != middleAlienInt) {
				alien[index2] = dynamic_cast<Flocking*>(Game::GetGameObjectsManager().Get(index2));
				sf::Vector2f nextAlienPos = alien[index2]->GetPosition();

				/*printf("currAlien index: %i\n", index);
				printf("nextAlien index2: %i\n", index2);
				printf("middAlienInt: %i\n", middleAlienInt);*/

				// Calculate the difference between the two objects.
				sf::Vector2f differenceV = currentAlienPos - nextAlienPos;
				float distance = sqrt(differenceV.x*differenceV.x + differenceV.y*differenceV.y);
				// separation - check for nearby aliens and steer way
				float separation = 50;

				// Check of the objects are closer that the collision distance.
				if (distance < separation) {
					//// when a neighbor is found, the distance from the agent to the neighbor is added to the vector
					//velocityV2.x += nextAlienPos.x - currentAlienPos.x;
					//velocityV2.y += nextAlienPos.y - currentAlienPos.y;
					//// vector need to be negated in order to steer away
					//velocityV2.x *= -1;
					//velocityV2.y *= -1;
					////printf("neib currAlien index: %i\n", index);
					////printf("neib nextAlien index2: %i\n", index2);
					////printf("velocityV2 *= -1;\n");
					}
				}
			}
			velocityGroup += accelerationV*elapsedTime;
			if (((velocityGroup.x*velocityGroup.x)+(velocityGroup.y*velocityGroup.y))>maxSpeed*maxSpeed) {
				velocityGroup = Flocking::Normalize(velocityGroup);
				velocityGroup *= maxSpeed;
			}
			//printf("\n");
			if (index != middleAlienInt) {
			alien[index]->SetPosition(currentAlienPos.x + (velocityGroup.x)*elapsedTime/alienNo, 
				currentAlienPos.y + (velocityGroup.y)*elapsedTime/alienNo);
			}
			//	printf("\n");
			//	velocityV2 += accelerationV2*elapsedTime;
			//	if (((velocityV2.x*velocityV2.x)+(velocityV2.y*velocityV2.y))>maxSpeed*maxSpeed) {
			//		velocityV2 = Flocking::Normalize(velocityV2);
			//		velocityV2 *= maxSpeed;
			//	}
			//	if (index != middleAlienInt) {
			//	//alien[index]->SetPosition(currentAlienPos.x + velocityV2.x*elapsedTime, currentAlienPos.y + velocityV2.y*elapsedTime);
			//	}
			//  }
			//}
			
			// velocity x & y
			//sf::Vector2f velocity;
			//velocity.x = elapsedTime*acceleration;
			//velocity.y = elapsedTime*acceleration;
			//printf("velocity.x :%f \nvelocity.y:%f\n", velocity.x, velocity.y);

			//// BC triangle side - change on x-axis
			//float BC = dirx;
			//// AC triangle side - change on y-axis
			//float AC = diry;
			//// angle
			//float ANG = atan(BC/AC) * 180 / PI;
			//// velocity vector
			//float AB = AC/cos(ANG);

			//printf("BC: %f\nAC: %f\nANG: %f\nAB(vector): %f\n", BC,  AC, ANG, AB);

			// velocity value = velocity vector * acceleration
			//float velocity = AB*acceleration;

			//printf("Velocity: %f\n", velocity);

			// velocity updates position
		
			//alien[middleAlienInt]->SetPosition(alienMiddGetPos.x + velocity/alienNo, alienMiddGetPos.y + velocity/alienNo);

			// just for checking after movement
			//float movex = initPosx - alien[middleAlienInt]->GetPosition().x;
			//float movey = initPosy - alien[middleAlienInt]->GetPosition().y;


			//printf("BC: %f\nAC: %f\nANG: %f\nAB(v): %f\n", BC,  AC, ANG, AB);
	  }
	}
}