#include "highscore.h"
#include <sstream>

namespace rs{


highscore::highscore(rs::texturemanager* texM)
{
	tm = texM;
	
	s_score_label = "SCORE";
	font.loadFromFile("font/8bitOperatorPlus-Bold.ttf");
	auto& texture = const_cast<sf::Texture&>(font.getTexture(l_fontSize));
	texture.setSmooth(false);
	t_score_label.setString(s_score_label);
	t_score_label.setFont(font);
	t_score_label.setCharacterSize(l_fontSize);
	t_score_label.setStyle(sf::Text::Regular);
	t_score_label.setOutlineColor(sf::Color::Black);
	t_score_label.setOutlineThickness(1.0f);
	t_score_label.setPosition(9*Tilewidth,0);
	
	auto& texturee = const_cast<sf::Texture&>(font.getTexture(fontSize));
	texturee.setSmooth(false);
	t_score.setString(s_score);
	t_score.setFont(font);
	t_score.setCharacterSize(fontSize);
	t_score.setStyle(sf::Text::Regular);
	t_score.setOutlineColor(sf::Color::Black);
	t_score.setOutlineThickness(1.0f);
	//t_score.setFillColor(sf::Color::Black);
	t_score.setPosition(9*Tilewidth,halfTilewidth);
	

	
	back_score_label_   =new rs::panel(6,1,sf::Vector2i(8.5*Tilewidth,0),tm);
	back_score_         =new rs::panel(6,1,sf::Vector2i(8.5*Tilewidth,Tilewidth + halfTilewidth),tm);
	
}
highscore::~highscore()
{
	delete back_score_;
	delete back_score_label_;
}

void highscore::getScoreValue(uint16_t type,bool isMinus,bool isSuper)
{
	int mod;
	if(isMinus){mod = -1;}else{mod = 1;}
			
		switch(type)
		{
			case 1:
				if(isSuper){
				 addScore(mod *  5);}else{ addScore(mod *5);}
				break;
			case 2:
				if(isSuper){
				 addScore(  mod *25);}else{ addScore(  mod *15);}
				break;
			case 3:
				if(isSuper){
				 addScore(  mod *75);}else{ addScore(  mod *50);}
				break;
			case 4:
				if(isSuper){
				 addScore(  mod *200);}else{ addScore(  mod *150);}
				break;
			case 5:
				if(isSuper){
				 addScore(  mod *500);}else{ addScore(  mod *450);}
				break;
			case 6:
				if(isSuper){
				 addScore(  mod *1500);}else{ addScore(  mod *1350);}
				break;
			case 7:
				if(isSuper){
				 addScore(  mod *4500);}else{ addScore(  mod *4050);}
				break;
			case 8:
				if(isSuper){
				 addScore(  mod *15000);}else{ addScore(  mod *12150);}
				break;
			case 11:
				 addScore(  mod *50);
				break;
			case 12:
				 addScore(  mod *350);
				break;
			case 13:
				 addScore(  mod *1500);
				break;
			case 14:
				 addScore(5000);
				break;
			case 15:
				 addScore(20000);
				break;
			default:
				 std::cout <<"mod:"<<std::to_string(mod)<<"\n";
				break;
		}
}
void highscore::addScore(int value)
{
	hscore += value;
}
void highscore::minusScore(int value)
{
	hscore -= value;
}
void highscore::handleInput(sf::Event e)
{
	//TODO//
	//on select draw table showing values for each ///
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		{
			hscore +=100;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		{
			hscore +=150;
		}
}
void highscore::render(sf::RenderWindow* window,float delta)
{


	back_score_->render(window);
	back_score_label_->render(window);
	window->draw(t_score_label);
	t_score.setString(std::to_string(hscore));
	window->draw(t_score);
}

        
};
