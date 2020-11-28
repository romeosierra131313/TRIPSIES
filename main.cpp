

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "defs.h"
#include "screenmanager.h"




int main()
{

    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode()), "TRIPSIES!");
	sf::Color clearColor(54,180,105,128);
//	sf::Color clearColor(0,0,0,255);
	sf::Clock clock;
    rs::state gamestate;
    window.setFramerateLimit(60);
    rs::screenmanager manager(&window);
	window.setView(manager.v);
    
    
    while (window.isOpen())
    {
		sf::Time delta = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        { 
             
                
            
            manager.handleInput(event);
            if (event.type == sf::Event::Closed)
            {
				
                window.close();
				
            }


        }

        window.clear(clearColor);
        manager.render(delta.asSeconds());
        window.display();
    }

    return 0;
}
