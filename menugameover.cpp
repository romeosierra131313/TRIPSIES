#include "menugameover.h" 

namespace rs
{
	
menugameover::menugameover(rs::texturemanager* texm,unsigned long score, int turns)
{
	tm = texm;
	back_   =new rs::panel(7,8,sf::Vector2i(272,0),texm);
	//sf::Font m_font;
	//font.loadFromFile("font/8bitOperatorPlus-Bold.ttf");
	
	std::string s_score= "Score \n";
	s_score.append(std::to_string(score));
		auto& texture = const_cast<sf::Texture&>(font.getTexture(l_fontSize));
	texture.setSmooth(false);
	t_score.setString(s_score);
	t_score.setFont(*tm->getFont());
	t_score.setCharacterSize(l_fontSize);
	t_score.setStyle(sf::Text::Regular);
	t_score.setOutlineColor(sf::Color::Black);
	t_score.setOutlineThickness(1.0f);
	t_score.setPosition(9*Tilewidth-onequarterTilewidth,0);
	
	
		std::string s_turns= "Trurns \n";
	s_turns.append(std::to_string(turns));
	texture.setSmooth(false);
	t_turns.setString(s_turns);
	t_turns.setFont(*tm->getFont());
	t_turns.setCharacterSize(l_fontSize);
	t_turns.setStyle(sf::Text::Regular);
	t_turns.setOutlineColor(sf::Color::Black);
	t_turns.setOutlineThickness(1.0f);
	t_turns.setPosition(9*Tilewidth-onequarterTilewidth,64);
	
 	myButton.setLocation(sf::Vector2i(13.75*Tilewidth,Tilewidth*7));
 //	myButton.setString(std::string("X"));
	myButton.setTexture(texm->getTexture(99));	
}
menugameover::~menugameover()
{
 delete back_;	
}
bool menugameover::onClose(){return closed;};
void menugameover::handleInput(sf::Event e,sf::Vector2i mcoord)
{
	myButton.handleInput(e,mcoord);
}
void menugameover::render(sf::RenderWindow* window,float delta)
{
	back_->render(window);
	window->draw(t_score);
	window->draw(t_turns);
	myButton.render(window,delta);
	
	if(myButton.onClick())
	{
		closed = true;

	}
}
	
	
};
