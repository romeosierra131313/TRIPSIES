#ifndef PANEL_H 
#define PANEL_H
#include <SFML/Graphics.hpp> 
#include "texturemanager.h" 
#include <vector>

namespace rs{
	
class panel
{
private:
	rs::texturemanager* tm;
    sf::Texture corner;
	sf::Texture side;
	sf::Texture back;
	int height,width,total;
	sf::Vector2i myLocation;
    std::vector<rs::tile> m_border ;
public:
    panel(int w , int h, sf::Vector2i loc ,rs::texturemanager* tm);
    ~panel();
    void setupPanel();
    void setLocation(sf::Vector2i newLocation);
    sf::Vector2i getLocation();
    void render(sf::RenderWindow* window);
};  
};
#endif 
