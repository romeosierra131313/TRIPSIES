#include "texturemanager.h" 
#include "panel.h" 


namespace rs{



panel::panel(int w , int h, sf::Vector2i loc ,rs::texturemanager* tx)
{
	width = w; 
	height = h;
	tm = tx;
	total =4 + (2*width)+(2*height)+(width*height);
	myLocation = loc;
	side = tm->getTexture(90);
	back = tm->getTexture(91);
	m_border.reserve(total* sizeof(rs::tile));
	setupPanel();
}
panel::~panel(){}
void panel::setupPanel()
{
			/////top left  tm->getTexture(89)////
		rs::tile t;
		t.setOrigin(Tilewidth,Tilewidth);
		t.setRotation(0.0f);
		t.setLocation(sf::Vector2i(getLocation().x,getLocation().y));
		t.setTexture(tm->getTexture(89));
		m_border.push_back(t);  
				////top right  tm->getTexture(89)
		rs::tile u;
		u.setOrigin(Tilewidth,Tilewidth);
		u.setRotation(90.0f);
		u.setLocation(sf::Vector2i((width*Tilewidth)+getLocation().x,getLocation().y));
		u.setTexture(tm->getTexture(89));
		m_border.push_back(u); 
				////bottom right  tm->getTexture(89)
		rs::tile v;
		v.setOrigin(Tilewidth,Tilewidth);
		v.setRotation(180.0f);
		v.setLocation(sf::Vector2i((width*Tilewidth)+getLocation().x,(height*Tilewidth)+getLocation().y));
		v.setTexture(tm->getTexture(89));
		m_border.push_back(v);
				////bottom left  tm->getTexture(89)
		rs::tile w;
		w.setOrigin(Tilewidth,Tilewidth);
		w.setRotation(270.0f);
		w.setLocation(sf::Vector2i(getLocation().x,(height*Tilewidth)+getLocation().y));
		w.setTexture(tm->getTexture(89));
		m_border.push_back(w);
	///left colom
		for(int i = 1 ; i <= height ; i++)
		{
			rs::tile t;
			t.setOrigin(Tilewidth,Tilewidth);
			t.setRotation(270.0f);
			t.setLocation(sf::Vector2i(getLocation().x,(i*Tilewidth)-Tilewidth+getLocation().y));
			t.setTexture(side);
			m_border.push_back(t);  
			  
		}

		//////right colom
		for(int i = 1 ; i <= height ; i++)
		{
			rs::tile t;
			t.setOrigin(Tilewidth,Tilewidth);
			t.setRotation(90.0f);
			t.setLocation(sf::Vector2i((width*Tilewidth)+getLocation().x,(i*Tilewidth)+getLocation().y));
			t.setTexture(side);
			m_border.push_back(t);  
			  
		}
		/////top row
		for(int i = 1 ; i <= width ; i++)
		{
			rs::tile t;
			t.setOrigin(Tilewidth,Tilewidth);
			t.setRotation(0.0f);
			t.setLocation(sf::Vector2i((i*Tilewidth)+getLocation().x,getLocation().y));
			t.setTexture(side);
			m_border.push_back(t);  
			  
		}
		////bamsy row
		for(int i = 1 ; i <= width ; i++)
		{
			rs::tile t;
			t.setOrigin(Tilewidth,Tilewidth);
			t.setRotation(180.0f);
			t.setLocation(sf::Vector2i((i*Tilewidth)-Tilewidth+getLocation().x ,(height*Tilewidth)+getLocation().y));
			t.setTexture(side);
			m_border.push_back(t);  
			  
		}
		for(int x = 0 ; x < width ; x++)
		{
		for(int y = 0 ; y < height ; y++)
		{
			rs::tile t;
			t.setLocation(sf::Vector2i((x*Tilewidth)+getLocation().x ,(y*Tilewidth)+getLocation().y ));
			t.setTexture(back);
			m_border.push_back(t);  
			  
		}
		}
	
	
	
	
}
void panel::setLocation(sf::Vector2i newLocation)
{
	
	int dx,dy;
	if(myLocation.x > newLocation.x){dx =myLocation.x - newLocation.x; }else{newLocation.x - myLocation.x; }
	if(myLocation.y > newLocation.y){dy =myLocation.y - newLocation.y; }else{newLocation.y - myLocation.y; }
	
	for(int i = 0 ; i < total ; i++)
	{
		sf::Vector2i tloc = m_border[i].getLocation2i();
		m_border[i].setLocation(sf::Vector2i(tloc.x+dx,tloc.y+dy));
	}
	myLocation = newLocation;
	
}
sf::Vector2i panel::getLocation(){return myLocation;}
void panel::render(sf::RenderWindow* window){
  		for(int i = 0; i < total; i ++)
	{
		m_border[i].render(window);
	}
}
}
