#ifndef DEFS_H
#define DEFS_H
#include <SFML/Graphics.hpp>
#define Tilewidth  32
#define onequarterTilewidth  8
#define oneeigthTilewidth  8
#define halfTilewidth  16
#define threequarterTilewidth  24

#define AssetDim  512
#define maxMapDim 128 //px
#define mapWidth 8
#define mapHeight 8
#define viewOffsetX 8.25
#define viewOffsetY 4
#define viewHeight 8.5
#define viewWidth 17



#define grass 1
#define bush 2
#define tree 3
#define smallHouse 4
#define mediumHouse 5
#define castle 6
#define f_castle 7
#define m_castle 8
#define rock 9
#define b_rock 10

#define crystal 17
#define robot 16

#define graveType 11
#define church 12
#define b_church 13
#define chest 14
#define b_chest 15
#define bearType 19
#define ninjaType 20
#define maxEnemys 37

#define l_fontSize 16
#define fontSize 16
#define t_cursor 80
#define t_storage 83
#define t_home 92
#define t_settings 93
#define t_about 94
#define t_b_zen 95
#define t_b_soft 96
#define t_b_hard 97
#define t_b_seed 98
#define t_b_close 99
#define t_b_tick 100

#include <iostream>
#include <functional>
#define emptyString ""
#define map01 "testmap"

#define gstate_zen 64324
#define gstate_soft 64235
#define gstate_hard 64880

/*TODO
 * implement queueof triples
 * implement timer & turncounter
 * 
 */













namespace rs{
	
	
	
	
class slider{
private:
	sf::Vector2i b_location,s_location;
	sf::Text b_text;
	float value = 1.0f;
	int w = 100;
	int h = 32;
	bool held = false;
	bool entered = false;
	bool released =false;
	sf::RectangleShape line;
	sf::RectangleShape box;
	sf::RectangleShape back;
	
	
	
public:	
	slider(sf::Vector2i loc,float val,sf::Font* font,std::string g)
	{
		b_location = sf::Vector2i (loc.x*Tilewidth,loc.y *Tilewidth);
		value = val;
		s_location = sf::Vector2i(b_location.x + (value * w),b_location.y);
		line.setPosition((float)loc.x*Tilewidth,(float)loc.y*Tilewidth);
		line.setSize(sf::Vector2f(100.0f,0.5f));
		line.setFillColor(sf::Color(150, 50, 250));
		
		box.setSize(sf::Vector2f(8.0f,4.0f));
		box.setPosition((float)s_location.x,(float)s_location.y);
		box.setFillColor(sf::Color(150, 50, 250));
		
		back.setSize(sf::Vector2f(100.0f,8.0f));
		back.setPosition((float)loc.x*Tilewidth,(float)loc.y*Tilewidth);
		back.setFillColor(sf::Color(100, 100, 100,100));
	//	box.setOutlineThickness(1.0f);
		b_text.setPosition(loc.x*Tilewidth,(loc.y*Tilewidth)-8);
		b_text.setCharacterSize(10);
		b_text.setStyle(sf::Text::Regular);
		b_text.setOutlineColor(sf::Color::Black);
		b_text.setOutlineThickness(1.0f);
		b_text.setString(g);
		auto& texturee = const_cast<sf::Texture&>(font->getTexture(10));
		texturee.setSmooth(false);
		b_text.setFont(*font);
	}
	~slider(){}
	void setSlider(sf::Vector2i mcoor)
	{
		s_location = sf::Vector2i(mcoor.x,b_location.y);
	    int	dx =mcoor.x-b_location.x;
		value =(float)dx;
		box.setPosition((float)mcoor.x,(float)s_location.y);
	}
	void resetRelease(){released = false;}
	bool onRelease(){return released;}
	float getValue(){return value;}
		bool amIHere(sf::Vector2i coor)
	{
		if(coor.x >= b_location.x && coor.x <= (b_location.x + w) )
		{
			if(coor.y >= b_location.y && coor.y <= (b_location.y + h) )
			{
					return true;
			}	
		}
		return false;
	}

	

	void handleInput(sf::Event e,sf::Vector2i mcoor)
	{
		if(e.type == sf::Event::MouseMoved )
		{
			entered = amIHere(mcoor);
			if(entered && held){setSlider(mcoor);}
		}
		if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left )
		{
				held = true;
		}
		if(e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left )
		{
				held = false;
				released = true;
		}
	}
		void render(sf::RenderWindow* window)
		{
			window->draw(back);
			window->draw(line);
			window->draw(box);
			window->draw(b_text);
		}
};
class tooltip
{
private:
	sf::Texture t;
	sf::Sprite mySprite;
	sf::Text b_text;
	sf::Vector2i b_location;
	sf::Uint8* px= new sf::Uint8[4096];
	
	
public:
	tooltip()
	{
		if(t.create(32,32)){}
		b_text.setCharacterSize(10);
		b_text.setStyle(sf::Text::Regular);
		b_text.setOutlineColor(sf::Color::Black);
		b_text.setOutlineThickness(1.0f);
		b_text.setString("");
		setTexture(t);
		
		
		for(int p = 0; p < 4096 ; p +=4)
		{
			px[p]  = 100;
			px[p+1]= 100;
			px[p+2]= 100;
			px[p+3]= 100;
		}
		
		t.update(px);
	}
	~tooltip(){delete px;}
	void setTexture(sf::Texture& t){mySprite.setTexture(t);}
	void setLocation(sf::Vector2i loc)
	{
		b_location = loc;
		mySprite.setPosition(loc.x-40,loc.y+8);
		b_text.setPosition(loc.x-220,loc.y+8);
		
	}
	void setString(std::string g){b_text.setString(g);}
	void setFont(sf::Font* font){
		auto& texturee = const_cast<sf::Texture&>(font->getTexture(10));
		texturee.setSmooth(false);
		b_text.setFont(*font);
		
	}
	void render(sf::RenderWindow* window,float delta)
		{
			mySprite.setPosition(b_location.x-32,b_location.y);
			window->draw(mySprite);
			mySprite.setPosition(b_location.x-64,b_location.y);
			window->draw(mySprite);
			mySprite.setPosition(b_location.x-96,b_location.y);
			window->draw(mySprite);
			mySprite.setPosition(b_location.x-128,b_location.y);
			window->draw(mySprite);
			mySprite.setPosition(b_location.x-160,b_location.y);
			window->draw(mySprite);
			mySprite.setPosition(b_location.x-192,b_location.y);
			window->draw(mySprite);
			mySprite.setPosition(b_location.x-224,b_location.y);
			window->draw(mySprite);
			window->draw(b_text);
		}	
};	
	
	
class button
{
private:
	sf::Sprite mySprite;
	sf::Vector2i b_location;
	sf::Font font;
	bool entered = false;
	bool oClick = false;
	rs::tooltip* tt=0 ;
	
	
public:
		button()
	{}
	button(sf::Vector2i loc ,sf::Texture& t,sf::Font* f,std::string g)
	{
		
	setLocation(sf::Vector2i(loc.x*Tilewidth,loc.y*Tilewidth));
	setTexture(t);	
	setFont(f);
	if(g == ""){}else{
	setString(g);}
	
	}
	~button(){delete tt;}
	void addToolTip(std::string g,sf::Vector2i loc){
		tt= new rs::tooltip;
		tt->setFont(&font);
		tt->setString(g);
		tt->setLocation(loc);
	}
	void setTexture(sf::Texture& t){mySprite.setTexture(t);}
	void setLocation(sf::Vector2i loc)
	{
		b_location = loc;
		mySprite.setPosition(loc.x,loc.y);
		if(tt !=0)tt->setLocation(loc);
	}
	void setEntered(bool b){entered = b;}
	void setString(std::string g)
	{
		if(tt!=0)
		{
			tt->setString(g);
		}else{
			addToolTip(g,b_location);
		}
	}
	void setFont(sf::Font* f){font = *f;}
	bool onClick(){
		return oClick;
	}
	bool amIHere(sf::Vector2i coor)
	{
		sf::Vector2u size = mySprite.getTexture()->getSize();
		if(coor.x >= b_location.x && coor.x <= (b_location.x + size.x) )
		{
			if(coor.y >= b_location.y && coor.y <= (b_location.y + size.y) )
			{
					return true;
			}	
		}
		return false;
	}

	

	void handleInput(sf::Event e,sf::Vector2i mcoor)
	{
		if(e.type == sf::Event::MouseMoved )
		{
			entered = amIHere(mcoor);
		}
		if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left )
		{
				if(entered){oClick = true;}else{oClick = false;}
		}
	}
	void render(sf::RenderWindow* window,float delta)
		{
			if(entered){
				mySprite.setScale(1.3f,1.3f);
				if(tt!=0){tt->render(window,delta);}
				
			}else{
				mySprite.setScale(1.0f,1.0f);
				
			}
		
			window->draw(mySprite);
			
			
		}
	
};
class tile
{
private:
    sf::Sprite mySprite;
    uint16_t type;
public:
    tile(){}
    ~tile(){}
    void setLocation(sf::Vector2i newLocation){mySprite.setPosition(newLocation.x ,newLocation.y);}
    sf::Vector2i getLocation2i(){return sf::Vector2i(mySprite.getPosition().x,mySprite.getPosition().y);}
    void setTexture(const sf::Texture& newTexture){mySprite.setTexture(newTexture);}
    void render(sf::RenderWindow* window){window->draw(mySprite);}
    void setOrigin(int centrex,int centrey){mySprite.setOrigin(sf::Vector2f(centrex,centrey));}
    void setRotation(float r){mySprite.setRotation(r);}
    void setType(uint16_t typ){type =typ;}
    uint16_t getType(){return type;}
};  



enum Dir{N,S,E,W,I};
class triple
{
private:
	rs::Dir m_dir = I;
    sf::Sprite mySprite;
	sf::Vector2i myLocation,myDestination;
    bool visible,isAnimated,isTrapped;
	bool isSuper = false;
    uint16_t type,moveSpeed;
	uint8_t currentFrame = 0;
	float animSpeed,animAccumulator;
	float s_moveSpeed = 0.2f;
	sf::Texture* myTextures[3];
public:
	triple(){}
    triple(sf::Vector2i loc)
	{
		visible = true;
		type = 0;
		myLocation = loc;
		setLocation(loc);
		isAnimated = false;
		
	}
    triple(sf::Vector2i loc,float speed,sf::Texture* nT1)
	{
		isAnimated = true;
		isTrapped = false;
		animSpeed = speed;
		setFrames(nT1);
		
		visible = true;
		type = 0;
		moveSpeed = 0;
		setLocation(loc);
		setDestination(loc);
		
		
	}
    ~triple(){}
    void setOrigin(int centrex,int centrey){mySprite.setOrigin(sf::Vector2f(centrex,centrey));}
  
    void setRotation(float r)
	{
		mySprite.setRotation(r);
	}
    void setScale(float fx,float fy)
	{
		mySprite.setScale(fx,fy);
	}
    void setColour(sf::Color c)
	{
		mySprite.setColor(c);
	}

    int setDir()
	{
		if(myLocation == myDestination)
		{
			m_dir = I;
			return 0;
		}
		else
		{
			if(myLocation.x > myDestination.x)
			{
				m_dir = W;
				return 1;
			}
			if(myLocation.x < myDestination.x)
			{
				m_dir = E;
				return 1;
			}
			if(myLocation.y > myDestination.y)
			{
				m_dir = N;
				return 1;
			}
			if(myLocation.y < myDestination.y)
			{
				m_dir = S;
				return 1;
			}
		}
return 16;
	}
	sf::Vector2i getLocation(){return myLocation;}
	sf::Vector2i getDestination(){return myDestination;}
    bool amIhere(sf::Vector2i here)
	{
		if(here.x >= myLocation.x && 
			here.x <= (myLocation.x + Tilewidth) && 
			here.y >= myLocation.y && 
			here.y <= (myLocation.y - Tilewidth) )
		{return true;}
		else
		{
			return false;
			
		}
		
	}
    void setTexture(sf::Texture& newTexture){
		mySprite.setTexture(newTexture);
		myTextures[0] = &newTexture;
	}
    
    void setAnimSpeed(float time)
	{
		animSpeed = time;
	}
    void setFrames(sf::Texture* nT1)
	{
		
		myTextures[0] = &nT1[0];
		myTextures[1] = &nT1[16];
		myTextures[2] = &nT1[32];
		mySprite.setTexture(*myTextures[0]);
		
	}
    
    sf::Sprite getSprite(){return mySprite;}
    
    void render(sf::RenderWindow* window,float delta)
	{
		if(isAnimated)
			{
			moveSpeed = setDir();
			if(moveSpeed > 0 && type == 20){moveSpeed = 4;}
			switch(m_dir)
			{
				case N:
				myLocation.y -= moveSpeed;	
				setLocation(myLocation);	
				break;
				case S:
				myLocation.y += moveSpeed;	
				setLocation(myLocation);	
				break;
				case E:
				myLocation.x += moveSpeed;	
				setLocation(myLocation);			
				break;
				case W:
				myLocation.x -= moveSpeed;	
				setLocation(myLocation);			
				break;
				case I:
				//do some idle anim//			
				break;
				default:
				std::cout << "defaulted" << std::endl;
				//do nothing //			
				break;
			}

			}
		if(visible)
		{
		if(mySprite.getPosition().x - myLocation.x > 1 ||mySprite.getPosition().x - myLocation.x < -1 )
		{
			if(mySprite.getPosition().x > myLocation.x)
			{
				mySprite.setPosition((mySprite.getPosition().x-s_moveSpeed),mySprite.getPosition().y);
			}else{
				mySprite.setPosition((mySprite.getPosition().x+s_moveSpeed),mySprite.getPosition().y);
			}
		}
		if(mySprite.getPosition().y - myLocation.y > 1 || mySprite.getPosition().y - myLocation.y < -1)
		{
			if(mySprite.getPosition().y > myLocation.y)
			{
				mySprite.setPosition(mySprite.getPosition().x,(mySprite.getPosition().y-s_moveSpeed));
			}else{
				mySprite.setPosition(mySprite.getPosition().x,(mySprite.getPosition().y+s_moveSpeed));
			}
		}
			

				animAccumulator += delta;
				if(animAccumulator > animSpeed)
				{
					currentFrame ++;
					if(currentFrame > 2)
					{
							currentFrame =0;
					}
					if(type == 0){mySprite.setTexture(*myTextures[0]);}else{
					mySprite.setTexture(*myTextures[currentFrame]);}
					animAccumulator = 0.0f;
				}
			window->draw(mySprite);
			
		}
		
	}
	void setSpeed(int speed){moveSpeed = speed;}
    void setTrapped(bool b){isTrapped = b;}
	bool getTrapped(){ return isTrapped;}
    void setVisible(bool b){visible = b;}
	bool getVisible(){ return visible;}
    void setAnimated(bool b){isAnimated = b;}
    bool getAnimated(){ return isAnimated;}
    void setLocation(sf::Vector2i newLocation){myLocation = newLocation; mySprite.setPosition(newLocation.x ,newLocation.y);}
    void setSpriteLocation(int x, int y )
	{
		sf::Vector2f ol(mySprite.getPosition());
		sf::Vector2f nl(ol.x+(float)x ,ol.y+(float)y);
		mySprite.setPosition(nl);
		
	}
    void setDestination(sf::Vector2i newLocation){myDestination = newLocation;}
    void setSuper(bool b){isSuper = b;}
    bool getSuper(){ return isSuper;}
    void setType(uint16_t typ){type =typ;}
    uint16_t getType(){return type;}
};  

enum state{gameover,menu,setting,about,game};
enum gamestate{zen,soft,hard,setseed};




};

#endif
