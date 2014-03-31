#include "stdafx.h"
#include "AlienS.h"
#include "Game.h"

float dirx = 0;
float diry = 0;

AlienS::AlienS(): speed(80), alienNo(3)
{
	//_maxVelocity(10.0f);
	Load("img/alien.png");

	//throws error window if file loading fails
	assert(IsLoaded());

	//GetSprite().setOrigin(GetSprite().getLocalBounds().width /2, GetSprite().getLocalBounds().height / 2 - 50); //50
}

AlienS::~AlienS()
{
}

void AlienS::Draw(sf::RenderWindow & rw)
{
	GameObjects::Draw(rw);
}

float AlienS::GetVelocity() const
{
	return speed;
}

int AlienS::GetAlienNo() const
{
	return alienNo;
}

void AlienS::Update(float elapsedTime)
{
	// array of pointers to aliens
	AlienS** alien = new AlienS*[alienNo];

	// array of vectors
	//sf::Vector2f alienVectorArray = alien[alienNo]Vector;
	//sf::Vector2f* alienAVect = new sf::Vector2f[alienNo]; 

	// load spaceship
	Spaceship* spaceship = dynamic_cast<Spaceship*>(Game::GetGameObjectsManager().Get(0));
	sf::Vector2f spaceshipPos;

	if(spaceship != NULL)
	{
		
		spaceshipPos = spaceship->GetPosition();

		sf::Rect<float> spaceshipBounds = spaceship->GetBoundingRect();

		if(spaceshipBounds.intersects(GetBoundingRect()))  //(GetPosition().x + moveByX + (GetSprite().GetSize().x /2),GetPosition().y + (GetSprite().GetSize().y /2) + moveByY))
		{ 
			spaceship->reduceHealth(1);
		}

		float alienSpeed = speed*elapsedTime;

		for (int index = 1; index < alienNo+1 ; index++)
		{
			alien[index] = dynamic_cast<AlienS*>(Game::GetGameObjectsManager().Get(index));
			sf::Vector2f alienGetPos = alien[index]->GetPosition(); // position vector

			for (int index = 1; index < alienNo+1 ; index++)
			{
			alien[index] = dynamic_cast<AlienS*>(Game::GetGameObjectsManager().Get(index));
			alienGetPos = alien[index]->GetPosition(); // position vector
			// alien movement towards group average
			dirx += (alienGetPos.x/alienNo); // average x
			diry += (alienGetPos.y/alienNo); // average y
			}
			
			//for (int index2 = 1; index2 < alienNo+1 ; index2++)
			//	{
			//		if (index2 != index) //&& index2 != middleAlienInt)
			//		{
			//		alien[index2] = dynamic_cast<AlienF*>(Game::GetGameObjectsManager().Get(index2));
			//		sf::Vector2f AlienPos = alien[index2]->GetPosition(); // position vector
			//		// avoid collision
			//		if ((AlienPos.x - currentAlienPos.x) < 25 && (AlienPos.x - currentAlienPos.x) > -25
			//		&& (AlienPos.y - currentAlienPos.y) < 25 && (AlienPos.y - currentAlienPos.y) > -25)
			//			{
			//				//alienSpeed = 0;
			//				dirx = (currentAlienPos.x - AlienPos.x);
			//				diry = (currentAlienPos.y - AlienPos.y);
			//			}
			//		}
			//	}

			// group average movement towards spaceship
			dirx = (spaceshipPos.x - dirx);
			diry = (spaceshipPos.y - diry);

			float hyp = sqrt(dirx*dirx + diry*diry);

			dirx /= hyp;
			diry /= hyp;

			alien[index]->SetPosition(alienGetPos.x + (dirx*alienSpeed)/alienNo, alienGetPos.y + (diry*alienSpeed)/alienNo);
		}
	}	
}

//
//	//Swarming   Have each unit steer toward the average position of the group
//  //			 Have the average position of the group steer towards the spaceship
//	
						