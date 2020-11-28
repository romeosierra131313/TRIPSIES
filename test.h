#ifndef TEST_H 
#define TEST_H
#include <SFML/Graphics.hpp>  
#include <fstream>
#include <stdio.h>
#include "screen.h"
#include "screenmanager.h"
#include "texturemanager.h"
#include "tilemap.h"
#include "triples.h"
#include "entitymanager.h" 
#include "highscore.h"
#include "menugameover.h"
#include "mainmenu.h"
#include "panel.h"
#include "defs.h"



namespace rs{
class test: public screen{

private:
//	rs::ui* m_gameover; 
	std::string entered;
	rs::gamestate gstate;
	rs::state State;
	uint16_t difficulty;
	int seed = 1;
	rs::highscore* m_score;
    rs::tilemap* m_map;
	rs::triples* m_triplemap;
	rs::entitymanager* m_entitymanager;
	rs::menugameover* m_go=0;
	rs::mainmenu* m_menu=0;
	rs::panel* p_mypanel;
	
	rs::panel* p_extra;

    rs::screenmanager* smptr;
	rs::tile storage;
	rs::tile cursorTex;
	sf::Vector2i normalCoords,Tilespace;
	sf::Sprite cursor;
	rs::triple* randomTriple;
	rs::triple* storedTriple;
	uint16_t n =0;
	bool stored = false;
	float rt_scaleAcum =0.5f;
	float hintTimer = 0.0f;
	bool biggening = true;
	std::vector<rs::triple> enemys;
	rs::texturemanager* tm;

public :  
        test(rs::screenmanager* sm,rs::gamestate mode,int iseed );
		test(rs::screenmanager* sm);
        ~test();
		void checkForHint();
		void setDifficulty(rs::gamestate);
		bool queryGameOver();
		void buildGameOverPanel();
		void newGame(uint8_t,int);
		uint16_t getNewTriple();
		void resetTriple();
		void resetTripleType(rs::triple*,uint16_t);
		rs::triple* getFreeBear();
		bool addBear(uint16_t,sf::Vector2i);
		bool removeBear(sf::Vector2i);
		bool updateTrapped();
		void moveEnemys();
		sf::Vector2i findPlace(rs::triple& bear);
		bool isEmpty(sf::Vector2i);
		uint16_t swapStored(rs::triple*);
		void updateMap(int);
		void matchMap();
		sf::Vector2i getN(sf::Vector2i loc);
		sf::Vector2i getS(sf::Vector2i loc);
		sf::Vector2i getE(sf::Vector2i loc);
		sf::Vector2i getW(sf::Vector2i loc);
		
		void checkBearAt(sf::Vector2i aLoction);
        void handleInput(sf::Event e)override;
		void updateCursor(sf::Vector2i,float);
		void saveGame(std::vector<rs::triple*>,std::vector<rs::triple*>,long,int,uint16_t,uint16_t);
		bool loadGame();
        void render(sf::RenderWindow* window,float)override;

        
    };
};
#endif 
