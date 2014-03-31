#include "stdafx.h"
#include "AlienF.h"
#include "Game.h"

AlienF::AlienF(): speed(80), alienNo(8)
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

		int middleAlienInt = alienNo/2 +1;

		// middle alien movement
		if (alienNo < 3)
		{
			middleAlienInt = 1;
		}
		
		//printf("middlealienint: %i", middleAlienInt);

		alien[middleAlienInt] = dynamic_cast<AlienF*>(Game::GetGameObjectsManager().Get(middleAlienInt));
		sf::Vector2f alienMiddGetPos = alien[middleAlienInt]->GetPosition(); // position vector

		float dirx = (spaceshipPos.x - alienMiddGetPos.x);
		float diry = (spaceshipPos.y - alienMiddGetPos.y);

		float hyp = sqrt(dirx*dirx + diry*diry);
		dirx /= hyp;
		diry /= hyp;

		alien[middleAlienInt]->SetPosition(alienMiddGetPos.x + (dirx*alienSpeed)/alienNo, alienMiddGetPos.y + (diry*alienSpeed)/alienNo);

		if (alienNo > 1)
		{
			// alien group movement
			for (int index = 1; index < alienNo+1 ; index++)
			{
				// default follow middle alien
				sf::Vector2f followAlienPos = alien[middleAlienInt]->GetPosition(); // position vector

				if (middleAlienInt != index)
				{
				// current alien position
				alien[index] = dynamic_cast<AlienF*>(Game::GetGameObjectsManager().Get(index));
				sf::Vector2f currentAlienPos = alien[index]->GetPosition();
				
				if (index < middleAlienInt) // before half
				{ 
				// follow next alien
				alien[index+1] = dynamic_cast<AlienF*>(Game::GetGameObjectsManager().Get(index+1));
				followAlienPos = alien[index+1]->GetPosition(); // position vector
				}

				if (index > middleAlienInt) // after half
				{ 
					// follow previous alien
					alien[index-1] = dynamic_cast<AlienF*>(Game::GetGameObjectsManager().Get(index-1));
					followAlienPos = alien[index-1]->GetPosition(); // position vector
				}

				// move randomly until too far, then move towards follow alien
				if ((alienMiddGetPos.x - currentAlienPos.x) < 30 && (alienMiddGetPos.x - currentAlienPos.x) > -30
						&& (alienMiddGetPos.y - currentAlienPos.y) < 30 && (alienMiddGetPos.y - currentAlienPos.y) > -30)
				{
					std::srand(Game::SCREEN_WIDTH);
					int randX = rand() % Game::SCREEN_WIDTH;
					dirx = (randX - currentAlienPos.x);
					int randY = rand() % Game::SCREEN_HEIGHT;
					diry = (randY - currentAlienPos.y);
				}
				else 
				{
					dirx = (alienMiddGetPos.x - currentAlienPos.x);
					diry = (alienMiddGetPos.y - currentAlienPos.y);
				}
				
				for (int index2 = 1; index2 < alienNo+1 ; index2++)
				{
					if (index2 != index) //&& index2 != middleAlienInt)
					{
					alien[index2] = dynamic_cast<AlienF*>(Game::GetGameObjectsManager().Get(index2));
					sf::Vector2f AlienPos = alien[index2]->GetPosition(); // position vector
					// avoid collision
					if ((AlienPos.x - currentAlienPos.x) < 25 && (AlienPos.x - currentAlienPos.x) > -25
					&& (AlienPos.y - currentAlienPos.y) < 25 && (AlienPos.y - currentAlienPos.y) > -25)
						{
							//alienSpeed = 0;
							dirx = (currentAlienPos.x - AlienPos.x);
							diry = (currentAlienPos.y - AlienPos.y);
						}
					}
				}

				hyp = sqrt(dirx*dirx + diry*diry);
				dirx /= hyp;
				diry /= hyp;

				alien[index]->SetPosition(currentAlienPos.x + (dirx*alienSpeed)/alienNo, currentAlienPos.y + (diry*alienSpeed)/alienNo);

				//// next alien - move towards it, and it moves towards first
				//// move randomly until too far, then move towards neibour
				//if (index > 2 && alienNo > 2)
				//{
				//	alien[index] = dynamic_cast<AlienF*>(Game::GetGameObjectsManager().Get(index));
				//	nextAlienPos = alien[index]->GetPosition();

				//	// move randomly
				//	dirx = (firstAlienPos.x - nextAlienPos.x);
				//	diry = (firstAlienPos.y - nextAlienPos.y);

				//	// move towards neibour
				//	if (dirx > 30 && dirx < -30
				//		&& diry > 30 && diry < -30)
				//	{
				//		dirx = (firstAlienPos.x - nextAlienPos.x);
				//		diry = (firstAlienPos.y - nextAlienPos.y);
				//	}
				//	// avoid collision
				//	if (dirx < 20 && dirx > -20
				//		&& diry < 20 && diry > -20)
				//	{
				//		alienSpeed = 0;
				//	}

				//	hyp = sqrt(dirx*dirx + diry*diry);
				//	dirx /= hyp;
				//	diry /= hyp;
				//	alien[index]->SetPosition(nextAlienPos.x + (dirx*alienSpeed)/alienNo, nextAlienPos.y + (diry*alienSpeed)/alienNo);
				}
			}
		}
	}	
}
//				 Have middle alien steer toward spaceship,
//					before middle aliens steer towards aliens after them (when outside range), 
//					after middle aliens steer towards aliens before them (when outside range).
//	//Cohesion   Have each unit steer toward the average position of its neighbors.
//	//Alignment  Have each unit steer so as to align itself to the average heading of its neighbors.
//	//Separation Have each unit steer to avoid hitting its neighbors
				