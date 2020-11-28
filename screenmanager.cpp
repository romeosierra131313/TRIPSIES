#include "screenmanager.h" 

namespace rs{
    
screenmanager::screenmanager(sf::RenderWindow* window)
{
    rwptr = window;
    screenptr = new rs::test(this);
	v.setSize(viewWidth*Tilewidth, viewHeight*Tilewidth);
	v.setCenter(sf::Vector2f(viewOffsetX*Tilewidth,viewOffsetY*Tilewidth));


}
screenmanager::~screenmanager()
{
delete screenptr;	
}
void screenmanager::newGame(rs::gamestate mode,int seed)
{
delete screenptr;
std::cout<< " new game : seed : " << std::to_string(seed) << "\n";
screenptr = new rs::test(this,mode , seed);
}

void screenmanager::handleInput(sf::Event e)
{
	if(screenptr != 0)
	{
		sf::Vector2f mc = rwptr->mapPixelToCoords(sf::Mouse::getPosition(*rwptr),v);
		screenptr->MouseCoords = sf::Vector2i((int)mc.x,(int)mc.y);  
		screenptr->handleInput(e);
		
	}

}
    
void screenmanager::render(float delta)
{
		if(screenptr != 0)
	{
screenptr->render(rwptr,delta);
}
}   
    
    
};
