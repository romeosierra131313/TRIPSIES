#include "mainmenu.h" 

namespace rs
{
	
mainmenu::mainmenu(rs::texturemanager* texm,rs::state* astate)
{
	tm = texm;
	mstate = astate;

	p_menu      =new rs::panel(1,8,sf::Vector2i(13.75*Tilewidth,0),tm);
	p_home      = new rs::panel(1,8,sf::Vector2i(15*Tilewidth,0),tm);
b_home = new rs::button(sf::Vector2i(15,0.25),tm->getTexture(t_home),tm->getFont(),"NEW GAME OPTIONS");	
	b_zen = new rs::button(sf::Vector2i(13.75,0.25),tm->getTexture(t_b_zen),tm->getFont(),"ZEN");
	b_zen->setLocation(sf::Vector2i(13.75*Tilewidth,0.25*Tilewidth));
	b_soft = new rs::button(sf::Vector2i(13.75,1.5),tm->getTexture(t_b_soft),tm->getFont(),"SOFT");
	b_soft->setLocation(sf::Vector2i(13.75*Tilewidth,1.5*Tilewidth));
	b_hard = new rs::button(sf::Vector2i(13.75,2.75),tm->getTexture(t_b_hard),tm->getFont(),"HARD");
	b_hard->setLocation(sf::Vector2i(13.75*Tilewidth,2.75*Tilewidth));
	b_seed = new rs::button(sf::Vector2i(13.75,3),tm->getTexture(t_b_seed),tm->getFont(),"SET SEED");
	b_seed->setLocation(sf::Vector2i(13.75*Tilewidth,4*Tilewidth));
		b_seedEntry = new rs::button(sf::Vector2i(13.5,4.25),tm->getTexture(0),tm->getFont()," ");
		b_tick = new rs::button(sf::Vector2i(12.75,4.25),tm->getTexture(t_b_tick),tm->getFont(),"");
		b_tick->setLocation(sf::Vector2i(12.75*Tilewidth,4*Tilewidth));
b_settings = new rs::button(sf::Vector2i(15.5,1.5),tm->getTexture(t_settings),tm->getFont(),"SETTINGS");
	s_sfx = new rs::slider(sf::Vector2i(8,1.5),1.0f,tm->getFont(),"SFX");


b_about = new rs::button(sf::Vector2i(15.5,2.5),tm->getTexture(t_about),tm->getFont(),"ABOUT");
b_close = new rs::button(sf::Vector2i(15.5,7),tm->getTexture(t_b_close),tm->getFont(),"");




}
mainmenu::~mainmenu()
{
	delete s_sfx;
	delete b_tick;
	delete p_seedEntry;
	delete b_seedEntry;
	delete b_close;
	delete b_about;
	delete b_settings;
	delete b_seed;
	delete b_hard;
	delete b_soft;
	delete b_zen;
	delete b_home;
	delete p_menu;
	delete p_home;
}
void mainmenu::handleInput(sf::Event e,sf::Vector2i mcoord)
{
		if(e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left )
	{
	if(mcoord.x < 8*Tilewidth){b_close->setLocation(sf::Vector2i(15*Tilewidth,Tilewidth*7));*mstate = game;}	}
 	b_home->handleInput(e,mcoord);
 	b_settings->handleInput(e,mcoord);
 	b_about->handleInput(e,mcoord);
	b_close->handleInput(e,mcoord);
	if(b_tick != 0 ){b_tick->handleInput(e,mcoord);}
	
	if(*mstate == menu)
	{
		b_zen ->handleInput(e,mcoord);
		b_soft->handleInput(e,mcoord);
		b_hard->handleInput(e,mcoord);
		b_seed->handleInput(e,mcoord);
		
	}
	else if(*mstate == setting)
	{
		s_sfx->handleInput(e,mcoord);
	}
	
		if (e.type == sf::Event::TextEntered)
	{
								if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
			{
	
				
			}
			std::string temp("");
			temp +=e.text.unicode;	
			if(temp == "\b"){	
				entered = entered.substr(0,entered.size()-1);
				
			}else{
				try
				{
					if(entered.size() < 10 ){
					std::stoi(temp);
					entered+= temp;}
				}catch(std::invalid_argument e){}
		
			}
	}
}
void mainmenu::render(sf::RenderWindow* window,float delta)
{
		p_home->render(window);
	
 	b_home->render(window,delta);
 	b_settings->render(window,delta);
 	b_about->render(window,delta);
	b_close->render(window,delta);
	
	
	
	
 	if(b_home->onClick()){
		*mstate = menu;
		delete p_menu;
	//	b_close->setLocation(sf::Vector2i(13.75*Tilewidth,Tilewidth*7));
		p_menu = new rs::panel(1,8,sf::Vector2i(13.75*Tilewidth,0),tm);
	}
 	if(b_settings->onClick()){
		std::cout<< "settings \n";
		*mstate = setting;
		delete p_menu;
	//	b_close->setLocation(sf::Vector2i(13.75*Tilewidth,Tilewidth*7));
		p_menu =new rs::panel(7,8,sf::Vector2i(7.75*Tilewidth,0),tm);
	}
 	if(b_about->onClick()){
		std::cout<< "about \n";
		*mstate = about;
		delete p_menu;
	//	b_close->setLocation(sf::Vector2i(13.75*Tilewidth,Tilewidth*7));
		p_menu =new rs::panel(14,8,sf::Vector2i(0.75*Tilewidth,0),tm);
	}
	if(b_close ->onClick()){
		std::cout<< " new game : hard \n";
		if(p_seedEntry !=0){ 
			delete p_seedEntry;
			p_seedEntry = 0;
		}
		b_close->setLocation(sf::Vector2i(15*Tilewidth,Tilewidth*7));
		*mstate = game;
		
	}
	

	
	
	else if(*mstate == menu)
	{


	p_menu->render(window);
	
	b_zen->render(window,delta);
	b_soft->render(window,delta);
	b_hard->render(window,delta);
	b_seed->render(window,delta);
	if(p_seedEntry !=0){
		
		p_seedEntry->render(window);
		b_seedEntry->setString(entered);
		b_seedEntry->setEntered(true);
		b_seedEntry->render(window,delta);
		b_tick->render(window,delta);
		if(b_tick ->onClick())
		{
				try
				{
					seed =std::stoi(entered); 
				}catch(std::invalid_argument e){
					seed = 1;
				}catch(std::out_of_range e){
					seed = 1;
				}
		
			mode = 4;
			
		}
		
	}
	
	
	if(b_zen ->onClick()){mode = 1;}
 	if(b_soft->onClick()){mode = 2;}
 	if(b_hard->onClick()){mode = 3;}
 	if(b_seed->onClick()){
		b_close->setLocation(sf::Vector2i(12.75*Tilewidth,5*Tilewidth));
		p_seedEntry     = new rs::panel(8,3,sf::Vector2i(6*Tilewidth-onequarterTilewidth,3.5*Tilewidth+onequarterTilewidth),tm);

	}
	
		
	}
	else if(*mstate == setting)
	{
	p_menu->render(window);
	if(s_sfx->onRelease()){
		tm->setSfx(s_sfx->getValue());
		s_sfx->resetRelease();
	}
	s_sfx->render(window);
	if(b_close ->onClick()){std::cout<< "\n" ; *mstate = game;}
		
	}
	else if(*mstate == about)
	{
	p_menu->render(window);
	}
	if(b_close ->onClick()){std::cout<< " new game : hard \n";*mstate = game;}
		
	
	b_close->render(window,delta);
}
	
	
};
 
