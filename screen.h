#ifndef SCREEN_H 
#define SCREEN_H
#include <SFML/Graphics.hpp>

namespace rs{
    
    class screenmanager; 
    class screen{
   
    public:
         rs::screenmanager* screenManager;
         sf::Vector2i MouseCoords;
         screen(rs::screenmanager* sm){screenManager = sm;}
        
        virtual void handleInput(sf::Event e)= 0;
        virtual void render(sf::RenderWindow* window,float)=0;
        
        
        
    };
    
    
};







#endif
