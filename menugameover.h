 
 
#ifndef MENUGAMEOVER_H 
#define MENUGAMEOVER_H
#include <SFML/Graphics.hpp> 
#include "texturemanager.h"
#include "defs.h"
#include "string.h"
#include "panel.h"


namespace rs{
class menugameover{

private:
	rs::button myButton;
	rs::panel* back_; 
	sf::Text t_turns;
	sf::Text t_score;
	sf::Font font;
	bool closed = false;
	rs::texturemanager* tm;
	

public :  
        menugameover(rs::texturemanager*,unsigned long , int);
        ~menugameover();
		bool onClose();
        void handleInput(sf::Event e,sf::Vector2i);
        void render(sf::RenderWindow* window,float);

        
    };
};
#endif 
