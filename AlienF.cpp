#include "stdafx.h"
#include "AlienF.h"
#include "Game.h"

AlienF::AlienF():
	speed(80),
	alienNo(10)
{
	//_maxVelocity(10.0f);
	Load("img/alien.png");

	//throws error window if file loading fails
	assert(IsLoaded());

	//GetSprite().setOrigin(GetSprite().getLocalBounds().width /2, GetSprite().getLocalBounds().height / 2 - 50); //50
}

AlienF::~AlienF()
{
}

void AlienF::Draw(sf::RenderWindow & rw)
{
	GameObjects::Draw(rw);
}

float AlienF::GetVelocity() const
{
	return speed;
}

int AlienF::GetAlienNo() const
{
	return alienNo;
}

void AlienF::Update(float elapsedTime)
{
	// array of pointers to aliens
	AlienF** alien = new AlienF*[alienNo];

	// array of vectors
	//sf::Vector2f alienVectorArray = alien[alienNo]Vector;
	//sf::Vector2f* alienAVect = new sf::Vector2f[alienNo]; 

	// load spaceship
	Spaceship* spaceship = dynamic_cast<Spaceship*>(Game::GetGameObjectsManager().Get(0));
	sf::Vector2f spaceshipVect;

	if(spaceship != NULL)
	{
		
		spaceshipVect = spaceship->GetPosition();

		sf::Rect<float> spaceshipBounds = spaceship->GetBoundingRect();

		if(spaceshipBounds.intersects(GetBoundingRect()))  //(GetPosition().x + moveByX + (GetSprite().GetSize().x /2),GetPosition().y + (GetSprite().GetSize().y /2) + moveByY))
		{ 
			spaceship->reduceHealth(1);
		}

		float alienSpeed = speed*elapsedTime;

		// first alien movement
		alien[1] = dynamic_cast<AlienF*>(Game::GetGameObjectsManager().Get(1));
		sf::Vector2f alien1GetPos = alien[1]->GetPosition(); // position vector

		// default next alien is 1st alien
		sf::Vector2f nextAlienPos = alien[1]->GetPosition(); // position vector

		float dirx = (spaceshipVect.x - alien1GetPos.x);
		float diry = (spaceshipVect.y - alien1GetPos.y);

		float hyp = sqrt(dirx*dirx + diry*diry);
		dirx /= hyp;
		diry /= hyp;

		alien[1]->SetPosition(alien1GetPos.x + (dirx*alienSpeed)/alienNo, alien1GetPos.y + (diry*alienSpeed)/alienNo);

		if (alienNo > 1)
		{
			// alien group movement
			for (int index = 2; index < alienNo+1 ; index++)
			{
				// default move towards alien1
				sf::Vector2f firstAlienPos = alien[1]->GetPosition();

				// current alien position
				alien[index] = dynamic_cast<AlienF*>(Game::GetGameObjectsManager().Get(index));
				sf::Vector2f currentAlienPos = alien[index]->GetPosition();

				// move towards next
				dirx = (nextAlienPos.x - currentAlienPos.x);
				diry = (nextAlienPos.y - currentAlienPos.y);
				// avoid collision
				if (dirx < 10 && dirx > -10
					&& diry < 10 && diry > -10)
				{
					alienSpeed = 0;
				}

				hyp = sqrt(dirx*dirx + diry*diry);
				dirx /= hyp;
				diry /= hyp;
				alien[index]->SetPosition(currentAlienPos.x + (dirx*alienSpeed)/alienNo, currentAlienPos.y + (diry*alienSpeed)/alienNo);

				// next alien - move towards it, and it moves towards first
				if (index > 2 && alienNo > 2)
				{
					alien[index] = dynamic_cast<AlienF*>(Game::GetGameObjectsManager().Get(index));
					nextAlienPos = alien[index]->GetPosition();
					// move towards first
					dirx = (firstAlienPos.x - nextAlienPos.x);
					diry = (firstAlienPos.y - nextAlienPos.y);
					// avoid collision
					if (dirx < 10 && dirx > -10
						&& diry < 10 && diry > -10)
					{
						alienSpeed = 0;
					}

					hyp = sqrt(dirx*dirx + diry*diry);
					dirx /= hyp;
					diry /= hyp;
					alien[index]->SetPosition(nextAlienPos.x + (dirx*alienSpeed)/alienNo, nextAlienPos.y + (diry*alienSpeed)/alienNo);
				}
			
				
			}
		}
	}	
}
//				 Have first alien steer toward spaceship
//	//Cohesion   Have each unit steer toward the average position of its neighbors.
//	//Alignment  Have each unit steer so as to align itself to the average heading of its neighbors.
//	//Separation Have each unit steer to avoid hitting its neighbors
				