#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Game.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 600), "STM for Games");
    sf::Texture mainMenu;
	if (!mainMenu.loadFromFile("img/mainMenu.png"))
		{
			// error...
			printf("File not found");
		}
	sf::Sprite sprite;
	sprite.setTexture(mainMenu);

    while (window.isOpen()) //MainMenu
    {
		sf::Event event;
		window.draw(sprite);
		window.display();

		while (window.pollEvent(event))
		{
        window.display();

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			// transform the mouse position from window coordinates to world coordinates
			sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			// retrieve the bounding box of the sprite
			//sf::FloatRect exitBounds = sprite.getGlobalBounds();
			float mouseY = mouse.y;
			
			if (mouseY > 300)
			{
				window.close();
			}

			if (mouseY < 300)
			{
				while (window.isOpen()) // STMMenu
				{
				sf::Event event;
				while (window.pollEvent(event))
				{
				// transform the mouse position from window coordinates to world coordinates
				sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				// retrieve the bounding box of the sprite
				//sf::FloatRect exitBounds = sprite.getGlobalBounds();
				float mouseY = mouse.y;
				sf::Texture STMMainMenu;
				if (!STMMainMenu.loadFromFile("img/STMMainMenu.png"))
					{
					// error...
						printf("File not found");
					}
				sf::Sprite sprite;
				sprite.setTexture(STMMainMenu);
				window.clear();
				window.draw(sprite);
				window.display();

				if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (mouseY > 5 && mouseY < 150)
					{
						printf("FLOCKING");
						window.close();
						Game::Initialize(1);
						
					}
					else if (mouseY > 150 && mouseY < 300)
					{
						printf("SWARMING");
						window.close();
						Game::Initialize(2);
					}
					else if (mouseY > 300 && mouseY < 450)
					{
						printf("A*");
						window.close();
						Game::Initialize(3);
					}
					else if (mouseY > 450)
					{
						window.close();
					}
				}
				if (event.type == sf::Event::Closed)
				window.close();
				}
				}
			}
			printf("%f", mouseY);
		}
		if (event.type == sf::Event::Closed)
		 window.close();
		}
		
    }
    return 0;
}