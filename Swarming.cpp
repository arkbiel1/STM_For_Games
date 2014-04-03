#include "stdafx.h"
#include "Swarming.h"
#include "Game.h"

#define PI 3.14159265

// average position of all aliens - centre of mass -> steer towards spaceship, and avoid collision

Swarming::Swarming(): maxSpeed(20), alienNo(3)
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

		alien[middleAlienInt] = dynamic_cast<Swarming*>(Game::GetGameObjectsManager().Get(middleAlienInt));
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
		sf::Vector2f velocityV(dirx, diry);
		// initial acceleration
		sf::Vector2f accelerationV(0.0f, 0.0f);

		velocityV += accelerationV*elapsedTime;
		if (((velocityV.x*velocityV.x)+(velocityV.y*velocityV.y))>maxSpeed*maxSpeed) {
			velocityV = Swarming::Normalize(velocityV);
			velocityV *= maxSpeed;
		}

		alien[middleAlienInt]->SetPosition(middleAlienPos.x + velocityV.x*elapsedTime, middleAlienPos.y + velocityV.y*elapsedTime);

		int neibourCount = 0;

		// alien group movement
		for (int index = 1; index < alienNo+1 ; index++) {
			// except middle alien
			//if (index != middleAlienInt) {
			// current alien position
			alien[index] = dynamic_cast<Swarming*>(Game::GetGameObjectsManager().Get(index));
			sf::Vector2f currentAlienPos = alien[index]->GetPosition();
			
			// initial velocity
			sf::Vector2f velocityV2(0.0f, 0.0f);
			sf::Vector2f accelerationV2(0.0f, 0.0f);

			//int neibourDist = 180;

			// cohesion - steer towards average position of neibours
			for (int index2 = 1; index2 < alienNo+1 ; index2++) {
				if (index != index2) {//&& middleAlienInt != index2) {
				
				alien[index2] = dynamic_cast<Swarming*>(Game::GetGameObjectsManager().Get(index2));
				sf::Vector2f nextAlienPos = alien[index2]->GetPosition();

					/*if (abs (currentAlienPos.x - nextAlienPos.x) < neibourDist
						&& abs (currentAlienPos.y - nextAlienPos.y) < neibourDist) {*/

						neibourCount++;

						//velocityV2.x = 1;
						//velocityV2.y = 1;

						// when a neighbor is found, the position of the neighbor is added to the vector
						velocityV2.x += nextAlienPos.x;
						velocityV2.y += nextAlienPos.y;
						// vector is divided by the neighbor count, resulting in the position that corresponds to the center of mass
						velocityV2.x /= neibourCount;
						velocityV2.y /= neibourCount;
						// direction towards the center of mass
						sf::Vector2f centerOfMassV(velocityV2.x - currentAlienPos.x, velocityV2.y - currentAlienPos.y);
						//centerOfMassV = Flocking::Normalize(centerOfMassV);
						//velocityV2.x = velocityV2.x - currentAlienPos.x;
						//velocityV2.y = velocityV2.y - currentAlienPos.y;
						//printf("neibourCount alien[%i]: %i\n", index, neibourCount);
						//printf("centerOfMassV X: %f,  Y: %f\n", centerOfMassV.x, centerOfMassV.y);
						centerOfMassV += velocityV;
						velocityV2 += centerOfMassV;
					   //}
				}
			}

			// separation
			for (int index2 = 1; index2 < alienNo+1 ; index2++) {
				if (index != index2) {
				alien[index2] = dynamic_cast<Swarming*>(Game::GetGameObjectsManager().Get(index2));
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
			velocityV2 += accelerationV*elapsedTime;
			if (((velocityV2.x*velocityV2.x)+(velocityV2.y*velocityV2.y))>maxSpeed*maxSpeed) {
				velocityV2 = Swarming::Normalize(velocityV2);
				velocityV2 *= maxSpeed;
			}
			printf("\n");
			alien[index]->SetPosition(currentAlienPos.x + velocityV2.x*elapsedTime, currentAlienPos.y + velocityV2.y*elapsedTime);
	  }
	}
}