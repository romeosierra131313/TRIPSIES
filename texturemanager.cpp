#include "texturemanager.h" 
#include <iostream>

namespace rs{
    
texturemanager::texturemanager()
{
    int totalTextures = ( AssetDim/Tilewidth)*( AssetDim/Tilewidth);
    allTextures = new sf::Texture[totalTextures];
    if(asset.loadFromFile("assets/2.png"))
    {
       int index = 0;
       for(int y = 0; y < AssetDim/Tilewidth ; y ++){
           for(int x = 0; x <  AssetDim/Tilewidth ; x ++){
      
               allTextures[index].loadFromImage(asset,sf::IntRect(x*Tilewidth,y*Tilewidth,Tilewidth,Tilewidth));
               index++;
       }    
       }
    
        
    }else{std::cout << "falied to load image ";}
    
loadFont("font/8bitOperatorPlus-Bold.ttf");
    
  // loadBank(uint8_t(2)); 


	if(sb_spop.loadFromFile("assets/sfx/1pop.wav"))
	{
	//	s_spop.setPlayingOffset(sf::seconds(3.0f));
			s_spop.setBuffer(sb_spop);
			
		s_spop.setVolume(100.0f);
	}else{std::cout << "error pop sfx";}
	if(sb_mpop.loadFromFile("assets/sfx/2pop.wav"))
	{
	//	s_spop.setPlayingOffset(sf::seconds(3.0f));
			s_mpop.setBuffer(sb_mpop);
			
		s_mpop.setVolume(100.0f);
	}else{std::cout << "error pop sfx";}


}
texturemanager::texturemanager(uint8_t bank)
{
    loadBank(bank);
    
}
        
texturemanager::~texturemanager(){
   
    
}
bool texturemanager::loadFont(std::string g)
{
	if(font.loadFromFile(g)){return true;}else{return false;}
}
sf::Font* texturemanager::getFont(){return &font;}
void texturemanager::loadBank(uint8_t bank)
{
//     allTextures = 0;
//     std::string path = "assets/";
//     path += std::to_string(bank) + ".png";
//         int totalTextures = ( AssetDim/Tilewidth)*( AssetDim/Tilewidth);
//     allTextures = new sf::Texture[totalTextures];
//     if(asset.loadFromFile(path))
//     {
//        int index = 0;
//        for(int y = 0; y < AssetDim/Tilewidth ; y ++){
//            for(int x = 0; x <  AssetDim/Tilewidth ; x ++){
//       
//                allTextures[index].loadFromImage(asset,sf::IntRect(x*Tilewidth,y*Tilewidth,Tilewidth,Tilewidth));
//                index++;
//        }    
//        }
//     
//         
//     }else{std::cout << "falied to load image ";}
    
}
sf::Texture& texturemanager::getTexture(int index){

    
     return allTextures[index]; 
}
sf::Texture* texturemanager::getFrames(int index)
{
	 sf::Texture* frames[3];
	 frames[0]= &allTextures[index];
	 frames[1]= &allTextures[index+1];
	 frames[2]= &allTextures[index+2];
	 return *frames;
}
void texturemanager::setSfx(float v)
{
	v_sfx = v;
	std::cout << "volume :" << std::to_string(v)  << "\n";
	s_spop.setVolume(v_sfx);
	s_mpop.setVolume(v_sfx);
	
}
void texturemanager::play(int num)
{
	
switch (num){
	case 1:
		s_spop.play();
		break;
	case 2:
		s_mpop.play();
		break;
}
}    
    
};
