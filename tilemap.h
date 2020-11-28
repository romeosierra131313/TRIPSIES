#ifndef TILEMAP_H 
#define TILEMAP_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "defs.h"
#include "string.h"
#include "texturemanager.h"
namespace rs{
class tilemap{


private:
    //rs::tile* tiles;
	std::vector<rs::tile> tiles;
    uint8_t offsetX;
    uint8_t offsetY;
    uint32_t totalTiles;
    rs::texturemanager* texMngr;
    
public :  
        
     tilemap(rs::texturemanager*);
	 ~tilemap();
    rs::tile getTile(sf::Vector2i);
    void randomMap();
    void applyPerlin();
    void doSmoothing();
    void changeTextureOf(sf::Vector2i,int);
    uint8_t getNeighbours(sf::Vector2i);
    void bitmaskit();
    bool saveMap();
    bool getMapFile(std::string);
    void render(sf::RenderWindow* window);
        
    };
    
    
};







#endif 
 
