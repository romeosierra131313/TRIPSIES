#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp> 

#include "texturemanager.h" 
#include "defs.h"
#include "triples.h"


namespace rs{
class entitymanager
{
private:
    rs::texturemanager*  textureManager;
	rs::triples* triplemap;
	rs::triple* b;
	sf::Texture* bearFrames;
	bool noSpace = false;
	sf::Texture* ninjaFrames;
    std::vector<rs::triple> enemys;
	std::vector<rs::triple*> sameNeighbours;
	std::vector<rs::triple*> uncheckedsameNeighbours;

    
public:


    entitymanager(rs::texturemanager*,rs::triples*);
    ~entitymanager();
	bool addBear(uint16_t,sf::Vector2i);
	void emptySameNeighbours();
	bool removeBear(sf::Vector2i);
	bool removeBearNoCheck(sf::Vector2i at);
	void addBearToCheckList(rs::triple*);
	bool updateTrapped();
	void moveEnemys();
	sf::Vector2i findPlace(rs::triple& bear);
	bool isEmpty(sf::Vector2i);
	bool isEmptyCheckNinja(sf::Vector2i loc);
	bool isBear(sf::Vector2i loc);
	rs::triple* getBear(sf::Vector2i loc);
	bool checkLoc(sf::Vector2i loc,int t);

	void getNeighbours(sf::Vector2i loc);
	bool areNeighboursTrapped(sf::Vector2i);
	std::vector<rs::triple*> getAllTriples();
    void render(sf::RenderWindow*,float);
    
    
};
};


#endif

