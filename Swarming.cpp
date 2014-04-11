#include "stdafx.h"
#include "Swarming.h"
#include "Game.h"

#define PI 3.14159265

// average position of all aliens - centre of mass -> steer towards spaceship, and avoid collision

Swarming::Swarming(): maxSpeed(70), alienNo(5)
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
		// velocity steers towards spaceship
		//velocityGroup.x = (spaceshipPos.x - velocityGroup.x);
		//velocityGroup.y = (spaceshipPos.y - velocityGroup.y);

		// initial acceleration
		sf::Vector2f accelerationV(0.0f, 0.0f);
		// initial velocity
		//sf::Vector2f centerOfMassV(0.0f, 0.0f);
		sf::Vector2f velocityToShip(0.0f, 0.0f);
		//sf::Vector2f velocitySepp(0.0f, 0.0f);

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
		printf("velocityAvg.x: %f\n", velocityAvg.x);

		// alien group movement - second part move towards average velocity
		for (int index = 1; index < alienNo+1 ; index++) {
			// current alien position
			alien[index] = dynamic_cast<Swarming*>(Game::GetGameObjectsManager().Get(index));
			sf::Vector2f currentAlienPos = alien[index]->GetPosition();

			// head towards average velocity
			float dirx = (velocityAvg.x - currentAlienPos.x);
			float diry = (velocityAvg.y - currentAlienPos.y);

			sf::Vector2f centerOfMassV(dirx, diry);

			centerOfMassV += accelerationV*elapsedTime;
			if (((centerOfMassV.x*centerOfMassV.x)+(centerOfMassV.y*centerOfMassV.y))>maxSpeed*maxSpeed) {
				centerOfMassV = Swarming::Normalize(centerOfMassV);
				centerOfMassV *= maxSpeed;
			}

			alien[index]->SetPosition(currentAlienPos.x + (centerOfMassV.x)*elapsedTime/alienNo,
									  currentAlienPos.y + (centerOfMassV.y)*elapsedTime/alienNo);
		}

		// alien group movement - third part steer towards spaceship
		for (int index = 1; index < alienNo+1 ; index++) {

			// current alien position
			alien[index] = dynamic_cast<Swarming*>(Game::GetGameObjectsManager().Get(index));
			sf::Vector2f currentAlienPos = alien[index]->GetPosition();

			float dirx = (spaceshipPos.x - centerOfMassV.x);
			float diry = (spaceshipPos.y - centerOfMassV.y);

			sf::Vector2f velocityToShip(dirx, diry);

			velocityToShip += accelerationV*elapsedTime;
			if (((velocityToShip.x*velocityToShip.x)+(velocityToShip.y*velocityToShip.y))>maxSpeed*maxSpeed) {
				velocityToShip = Swarming::Normalize(velocityToShip);
				velocityToShip *= maxSpeed;
			}

			alien[index]->SetPosition(currentAlienPos.x + (velocityToShip.x)*elapsedTime/alienNo,
									  currentAlienPos.y + (velocityToShip.y)*elapsedTime/alienNo);

			printf("velocityToShip.x: %f\n", velocityToShip.x);
			printf("velocityToShip.y: %f\n", velocityToShip.y);

		}
			//velocitySum += currentAlienPos;
			
			
			// direction (towards spaceship)
			/*float dirx = (spaceshipPos.x - velocitySum.x/alienNo);
			float diry = (spaceshipPos.y - velocitySum.y/alienNo);*/
/*
			printf("velocityGroup.x: %f\n", velocityGroup.x);
			printf("velocityGroup.y: %f\n", velocityGroup.y);*/

			//sf::Vector2f velocityToShip(dirx, diry);

			// alignment & cohesion - line up & steer towards average position of neibours
			//for (int index2 = 1; index2 < alienNo+1 ; index2++) {
			//	if (index != index2) {//&& middleAlienInt != index2) {
			//	
			//	alien[index2] = dynamic_cast<Swarming*>(Game::GetGameObjectsManager().Get(index2));
			//	sf::Vector2f nextAlienPos = alien[index2]->GetPosition();

			//	// Calculate the difference between the two objects.
			//	sf::Vector2f differenceV = currentAlienPos - nextAlienPos;
			//	float distance1 = sqrt(differenceV.x*differenceV.x + differenceV.y*differenceV.y);

			//	//if (neighbourCount == 0) velocityGroup = velocityCurr;

			//	// Calculate the difference between the two objects.
			//	sf::Vector2f differenceV2 = nextAlienPos - currentAlienPos;
			//	float distance = sqrt(differenceV2.x*differenceV2.x + differenceV2.y*differenceV2.y);

			//	// when a neighbor is found, the position of the neighbour is added to the vector
			//	//velocityGroup.x += (velocityCurr.x + differenceV2.x);
			//	//velocityGroup.y += (velocityCurr.y + differenceV2.y);

			//	//velocityGroup.x /= alienNo;
			//	//velocityGroup.y /= alienNo;

			//	float separation = 40;

			//	// Check of the objects are closer that the collision distance.
			//	if (distance1 < separation) { 

				//velocityGroup.x = currentAlienPos.x - nextAlienPos.x;
				//velocityGroup.y = currentAlienPos.y - nextAlienPos.y;
				//velocitySepp.x = currentAlienPos.x - nextAlienPos.x;
				//velocitySepp.y = currentAlienPos.y - nextAlienPos.y;

				//direction = false;

				//velocityV2.y *= -1;
				/*printf("neib currAlien index: %i\n", index);
				printf("velocitySepp.x: %f\n", velocitySepp.x);
				printf("velocitySepp.y: %f\n", velocitySepp.y);*/
				//printf("neib nextAlien index2: %i\n", index2);
				////printf("velocityV2 *= -1;\n");
		

		/*velocityToShip += accelerationV*elapsedTime;
		if (((velocityToShip.x*velocityToShip.x)+(velocityToShip.y*velocityToShip.y))>maxSpeed*maxSpeed) {
			velocityToShip = Swarming::Normalize(velocityToShip);
			velocityToShip *= maxSpeed;
		}*/

		//if(direction == false) {
		//	velocityGroup = velocitySepp;
		//	velocityGroup += accelerationV*elapsedTime;
		//	velocityGroup *= -1.0f;
		//	if (((velocityGroup.x*velocityGroup.x)+(velocityGroup.y*velocityGroup.y))>maxSpeed*maxSpeed) {
		//	velocityGroup = Swarming::Normalize(velocityGroup);
		//	velocityGroup *= maxSpeed;
		//	// vector need to be negated for that alien, in order to steer away
		//	//velocityGroup *= -1.0f;
		//	}
		//	velocityGroup += velocityDiff;
		//	velocityGroup *= -1.0f;
		//}

		//velocityGroup.x -= currentAlienPos.x;
		//velocityGroup.y -= currentAlienPos.y;

		/*velocityGroup += accelerationV*elapsedTime;
		if (((velocityGroup.x*velocityGroup.x)+(velocityGroup.y*velocityGroup.y))>maxSpeed*maxSpeed) {
			velocityGroup = Swarming::Normalize(velocityGroup);
			velocityGroup *= maxSpeed;
		}*/


		

		//alien[index]->SetPosition(currentAlienPos.x, //+ (velocityGroup.x)*elapsedTime/alienNo,
		//											//+ (velocityToShip.y)*elapsedTime/alienNo,
		//						  currentAlienPos.y); //+ (velocityGroup.y)*elapsedTime/alienNo);
		//											//+ (velocityToShip.y)*elapsedTime/alienNo);
	}
}