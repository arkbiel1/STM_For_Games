#include "stdafx.h"
#include "Flocking.h"
#include "Game.h"

#define PI 3.14159265

Flocking::Flocking(): speed(5), alienNo(10)
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

sf::Vector2f Flocking::GetVelocity() const
{
	return velocityV;
}

sf::Vector2f Flocking::Normalize(sf::Vector2f velocity)
{
	
  if (velocity.x*velocity.x + velocity.y*velocity.y == 0)
    {
      velocity.x = 0;
      velocity.y = 0;
    }
  if (velocity.x*velocity.x + velocity.y*velocity.y != 0)
    {
      velocity.x = velocity.x / sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
      velocity.y = velocity.y / sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
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
		sf::Vector2f alienMiddGetPos = alien[middleAlienInt]->GetPosition(); // position vector

		// head towards spaceship
		float dirx = (spaceshipPos.x - alienMiddGetPos.x);
		float diry = (spaceshipPos.y - alienMiddGetPos.y);

		//float initPosx = alienMiddGetPos.x;
		//float initPosy = alienMiddGetPos.y;

		float hyp = sqrt(dirx*dirx + diry*diry);
		dirx /= hyp;
		diry /= hyp;

		// acceleration updates velocity
		// velocity updates position
		//
		// positive velocity - move forward (x++ or y++)
		// negative velocity - move backwards (x-- or y--)

		float maxSpeed = speed*elapsedTime;
		// initial velocity
		sf::Vector2f velocityV(0.0f, 0.0f);
		// initial acceleration
		sf::Vector2f accelerationV(0.0f, 0.0f);

		velocityV.x = dirx;
		velocityV.y = diry;

		velocityV += accelerationV*elapsedTime;
		if (((velocityV.x*velocityV.x)+(velocityV.y*velocityV.y))>maxSpeed*maxSpeed) {
			velocityV = Flocking::Normalize(velocityV);
			velocityV *= maxSpeed;
		}

		//GetSprite().setPosition(GetSprite().getPosition+mVelocity);

		alien[middleAlienInt]->SetPosition(alienMiddGetPos.x + velocityV.x, alienMiddGetPos.y + velocityV.y);


		if (alienNo > 1) {
			// alien group movement
			for (int index = 1; index < alienNo+1 ; index++) {
				// except middle alien
				if (index != middleAlienInt) {
				// current alien position
				alien[index] = dynamic_cast<Flocking*>(Game::GetGameObjectsManager().Get(index));
				sf::Vector2f currentAlienPos = alien[index]->GetPosition();

				// move randomly until too far, then move towards follow alien
				if ((alienMiddGetPos.x - currentAlienPos.x) < 30 && (alienMiddGetPos.x - currentAlienPos.x) > -30
						&& (alienMiddGetPos.y - currentAlienPos.y) < 30 && (alienMiddGetPos.y - currentAlienPos.y) > -30) {
					//std::srand(Game::SCREEN_WIDTH);
					//int randX = rand() % Game::SCREEN_WIDTH;
					//dirx = (randX - currentAlienPos.x);
					//int randY = rand() % Game::SCREEN_HEIGHT;
					//diry = (randY - currentAlienPos.y);
				}
				else {
					//dirx = (alienMiddGetPos.x - currentAlienPos.x);
					//diry = (alienMiddGetPos.y - currentAlienPos.y);
				}

				// move towards middle alien
				float dirx2 = (alienMiddGetPos.x - currentAlienPos.x);
				float diry2 = (alienMiddGetPos.y - currentAlienPos.y);

				// acceleration at time t (elapsed time)
				//float acceleration = speed/elapsedTime;

				//float mMaxSpeed = 0.1;
				//float maxVelocity = 1;
				// initial velocity
				sf::Vector2f velocityV2(0.0f, 0.0f);
				sf::Vector2f accelerationV2(0.0f, 0.0f);

				velocityV2.x = dirx2;
				velocityV2.y = diry2;

				velocityV2 += accelerationV2*elapsedTime;
				if (((velocityV2.x*velocityV2.x)+(velocityV2.y*velocityV2.y))>maxSpeed*maxSpeed) {
					velocityV2 = Flocking::Normalize(velocityV2);
					velocityV2 *= maxSpeed;
				}

				//GetSprite().setPosition(GetSprite().getPosition+mVelocity);

				// calculate average velocity of surrounding entities 
				// acc = avg vel - curr vel

				alien[index]->SetPosition(currentAlienPos.x + velocityV2.x, currentAlienPos.y + velocityV2.y);
				}
			}
			
		}
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