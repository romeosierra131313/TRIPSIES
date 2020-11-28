 
#ifndef HIGHSCORE_H 
#define HIGHSCORE_H
#include <SFML/Graphics.hpp> 
#include "texturemanager.h"
#include "defs.h"
#include "string.h"
#include "panel.h"


namespace rs{
class highscore{

private:
	rs::panel* back_score_label_; 
	rs::panel* back_score_ ;
	sf::Text t_score_label;
	sf::Text t_score;
	sf::Font font;
	
	//max  100000000000000000
	long hscore =0;
	int turnCounter = 0;
	std::string s_score;
	std::string s_score_label;
	bool stored = false;
	sf::Sprite scoreBack;
	rs::texturemanager* tm;
	

public :  
        highscore(rs::texturemanager*);
        ~highscore();
		inline void addTurn(){turnCounter ++;}
		inline void setTurns(int turns){turnCounter = turns;}
		inline void setScore(long nscore){hscore = nscore;}
		long getScore(){return hscore;};
		int getTurns(){return turnCounter-1;};
		void getScoreValue(uint16_t type,bool,bool );
		void addScore(int);
		void minusScore(int);
        void handleInput(sf::Event e);
        void render(sf::RenderWindow* window,float);

        
    };
};
#endif 
