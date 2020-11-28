  
 
#pragma once
#include <SFML/Graphics.hpp> 
#include "texturemanager.h"
#include "defs.h"
#include "string.h"
#include "panel.h"



namespace rs{
class mainmenu{

private:
	rs::state* mstate;
	rs::texturemanager* tm;
	rs::slider* s_sfx;
	rs::panel* p_home;
	rs::panel* p_menu;
	rs::panel* p_seedEntry=0;
	rs::button* b_home;
	rs::button* b_zen;
	rs::button* b_soft;
	rs::button* b_hard;
	rs::button* b_seed;
	rs::button* b_seedEntry=0;
	rs::button* b_settings;
	rs::button* b_about;
	rs::button* b_close;
	rs::button* b_tick=0;
	uint8_t mode = 0;
	int seed = 1;
	std::string entered;

public :  
        mainmenu(rs::texturemanager*,rs::state*);
        ~mainmenu();
		uint8_t newGame(){return mode;}
		int getSeed(){return seed;}
        void handleInput(sf::Event e,sf::Vector2i);
        void render(sf::RenderWindow* window,float);

        
    };
};

