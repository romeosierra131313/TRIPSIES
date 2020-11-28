#ifndef TRIPLES_H 
#define TRIPLES_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "defs.h"
#include "texturemanager.h"
#include "highscore.h"
namespace rs{
class triples{


private:
    uint32_t totalTiles;
    rs::texturemanager* texMngr;
	rs::highscore* scorer;
	std::vector<rs::triple> triplets;
	std::vector<rs::triple*> sameNeighbours;
	std::vector<rs::triple*> uncheckedsameNeighbours;
	std::vector<int> sNeighbours;


    
public :  
        
     triples(rs::texturemanager*,rs::highscore*);
	 ~triples();
	bool addTriple(sf::Vector2i,uint16_t);
	void addGrave(sf::Vector2i loc);
	bool removeTriple(sf::Vector2i);
	bool isEmpty(sf::Vector2i);
	rs::triple* getTriple(sf::Vector2i);
	rs::triple* getTriple(int);
	uint16_t getType(sf::Vector2i);
	void setType(sf::Vector2i,uint16_t);
	bool checkForPromotion(sf::Vector2i);
	bool checkNorth(sf::Vector2i loc,int t);
	bool checkSouth(sf::Vector2i loc,int t);
	bool checkWest(sf::Vector2i loc,int t);
	bool checkEast(sf::Vector2i loc,int t);
	bool checkNorthWest(sf::Vector2i loc,int t);
	bool checkNorthEast(sf::Vector2i loc,int t);
	bool checkSouthWest(sf::Vector2i loc,int t);
	bool checkSouthEast(sf::Vector2i loc,int t);
	bool checkNorthNorth(sf::Vector2i loc,int t);
	bool checkSouthSouth(sf::Vector2i loc,int t);
	bool checkWestWest(sf::Vector2i loc,int t);
	bool checkEastEast(sf::Vector2i loc,int t);
	void doPromotion(sf::Vector2i);
    void changeTextureOf(sf::Vector2i,int);
	int TypeToTextureNumber(uint16_t,bool);
    void getNeighbours(sf::Vector2i);
	void getNeighboursGrave(std::vector<rs::triple*>*,sf::Vector2i,uint16_t);
	void emptySameNeighbours();
	std::vector<rs::triple*>* getSameNeighbours(){return &sameNeighbours; }
	bool contains(std::vector<rs::triple*>*,sf::Vector2i);
	std::vector<sf::Vector2i> getFreeLocations();
	bool noFreeLocations();
	std::vector<rs::triple*> getAllTriples();
    void render(sf::RenderWindow* window,float delta);
        
    };
    
    
};







#endif  
