#ifndef TEXTUREMANAGER_H 
#define TEXTUREMANAGER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>
#include "defs.h"



namespace rs{
class texturemanager{

private:
    sf::Image asset;
	sf::Font font;
    sf::Texture* allTextures;
	sf::SoundBuffer sb_spop;
	sf::SoundBuffer sb_mpop;
	sf::Sound s_spop;
	sf::Sound s_mpop;
	float v_sfx = 1.0f;

public :  

        texturemanager();
        texturemanager(uint8_t);
        ~texturemanager();
		bool loadFont(std::string);
		sf::Font* getFont();
        void loadBank(uint8_t);
        sf::Texture& getTexture(int index);
		sf::Texture* getFrames(int index);
		void setSfx(float);
		void play(int);
        
    };
    
    
};







#endif 

