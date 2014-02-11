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
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		window.draw(sprite);
        window.display();

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			// transform the mouse position from window coordinates to world coordinates
			sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			// retrieve the bounding box of the sprite
			//sf::FloatRect exitBounds = sprite.getGlobalBounds();
			float mouseY = mouse.y;
			// hit test
			if (mouseY > 300)
			{
				window.close();
			}

			else
			{
				 while (window.isOpen())
				{
					sf::Event event;
					while (window.pollEvent(event))
					{
						if (event.type == sf::Event::Closed)
							window.close();
					}
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
						// transform the mouse position from window coordinates to world coordinates
						sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

						// retrieve the bounding box of the sprite
						//sf::FloatRect exitBounds = sprite.getGlobalBounds();

						float mouseY = mouse.y;

						// hit test
						if (mouseY > 5 && mouseY < 150)
						{
							printf("FLOCKING");
							window.close();
							Game::Initialize();
						}
						else if (mouseY > 150 && mouseY < 300)
						{
							printf("SWARMING");
						}
						else if (mouseY > 300 && mouseY < 450)
						{
							printf("A*");
						}
						else if (mouseY > 450)
						{
							window.close();
						}
					}
				 }
			}
			printf("%f", mouseY);
		}
		
    }
    return 0;
}