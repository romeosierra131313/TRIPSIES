#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H
#include <iostream>
#include "texturemanager.h" 
#include "screen.h"
#include "test.h"

namespace rs{
class screenmanager
{
private:
    sf::RenderWindow* rwptr;
    rs::screen* screenptr;
    rs::texturemanager  textureManager;
    sf::Vector2f mouse;
    
public:
	sf::View v; 
    ~screenmanager();
    screenmanager(sf::RenderWindow*);
	void newGame(rs::gamestate,int);
    void handleInput(sf::Event);
    void render(float);
    rs::texturemanager* getTextureManagerPtr(){return &textureManager;}

    
    
};
};


#endif
