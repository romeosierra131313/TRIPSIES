
#include <iostream>
#include "entitymanager.h" 

namespace rs{

entitymanager::entitymanager(rs::texturemanager* tm,rs::triples* tmap)
	{
		textureManager = tm;
		bearFrames = textureManager->getFrames(215);
		ninjaFrames = textureManager->getFrames(167);
		triplemap = tmap;
		rs::triple beeee(sf::Vector2i(-1000,-1000),0.25f,textureManager->getFrames(73));
		b = &beeee;
		b->setTrapped(true);
		enemys.reserve(maxEnemys* sizeof(rs::triple));

		
		
	}
entitymanager::~entitymanager()
{
}

void entitymanager::emptySameNeighbours()
{
	while(sameNeighbours.size()>0)
		{
		sameNeighbours.pop_back();
		}	
}
bool entitymanager::addBear(uint16_t temp,sf::Vector2i at)
{
			emptySameNeighbours();
		if(temp == bearType	)
	{
		rs::triple bb(at,0.25f,bearFrames);
		bb.setType(temp);
		enemys.push_back(bb);
		addBearToCheckList(&bb);
		getNeighbours(at);	
		areNeighboursTrapped(at);
		return true;

		
	}
	else
	{
		rs::triple bb(at,0.25f,ninjaFrames);
		
		bb.setType(temp);
		enemys.push_back(bb);
		addBearToCheckList(&bb);
		getNeighbours(at);		
		areNeighboursTrapped(at);		
		return true;
	}
	return false;
}
bool entitymanager::removeBear(sf::Vector2i at)
{
	for(int i = 0; i < enemys.size(); i ++)
	{
		if(at == enemys[i].getLocation() )
		{
		triplemap->addTriple(enemys[i].getLocation(),graveType);
		enemys[i] = enemys.back();
		enemys.pop_back();
		return true;
		}
		
	}
	return false;
}
bool entitymanager::removeBearNoCheck(sf::Vector2i at)
{
	for(int i = 0; i < enemys.size(); i ++)
	{
		if(at == enemys[i].getLocation() )
		{	
			
			enemys[i] = enemys.back();
			enemys.pop_back();
			return true;
		}
	}
	return false;
}
void entitymanager::addBearToCheckList(rs::triple* t)
{
	uncheckedsameNeighbours.push_back(t);
}
bool entitymanager::updateTrapped()
{
	for(int i = 0; i < enemys.size(); i ++)
		{
			if(enemys[i].getVisible() && enemys[i].getTrapped())
			{
				removeBearNoCheck(enemys[i].getLocation());
				triplemap->addTriple(enemys[i].getLocation(),graveType);

			}
		}
	
}
void entitymanager::moveEnemys()
{
		std::vector<sf::Vector2i> freePlaces = triplemap->getFreeLocations();
		if(freePlaces.size() > 0){	
			for(int i = 0; i < enemys.size(); i ++)
			{
				for(int p = 0; p < freePlaces.size(); p ++){
				if(
				   freePlaces[p] == enemys[i].getDestination())
					{
						 freePlaces[p] = freePlaces.back();
						 freePlaces.pop_back();
					}
				}
			}
		}
if(freePlaces.size() > 0){	

	for(int i = 0; i < enemys.size(); i ++)
	{
			enemys[i].setDestination(findPlace(enemys[i]));

	}
}else{
			std::cout << "no free spacesfound killing enemys";
				//kill all enemys
			sf::Vector2i last;
			for(int i = enemys.size(); i >0 ; i --)
			{
				triplemap->addGrave(enemys.back().getLocation());
				last = enemys.back().getLocation();
				enemys.pop_back();
			
					
			}
			triplemap->removeTriple(last);
			triplemap->addTriple(last,graveType);
}
	
}
sf::Vector2i entitymanager::findPlace(rs::triple& bear)
{
	
		sf::Vector2i loc = bear.getLocation();
			loc.x = loc.x - loc.x % Tilewidth;
		loc.y = loc.y - loc.y % Tilewidth;
	std::vector<sf::Vector2i> freePlaces = triplemap->getFreeLocations();
			for(int i = 0; i < enemys.size(); i ++)
			{
				for(int p = 0; p < freePlaces.size(); p ++){
				if(
				   freePlaces[p] == enemys[i].getDestination())
					{
						 freePlaces[p] = freePlaces.back();
						 freePlaces.pop_back();
					}
				}
			}

	if(bear.getType() == bearType){
		

		
		
				for(int p = 0; p < freePlaces.size(); p ++)
				{
					if(freePlaces[p] == sf::Vector2i(loc.x- Tilewidth,loc.y))
					{return sf::Vector2i(loc.x- Tilewidth,loc.y);}
					else if(freePlaces[p] == sf::Vector2i(loc.x + Tilewidth,loc.y))
					{return sf::Vector2i(loc.x + Tilewidth,loc.y);}
					else if(freePlaces[p] == sf::Vector2i(loc.x,loc.y- Tilewidth))
					{return sf::Vector2i(loc.x,loc.y- Tilewidth);}
					else if(freePlaces[p] == sf::Vector2i(loc.x,loc.y + Tilewidth))
					{return sf::Vector2i(loc.x,loc.y + Tilewidth);}
				}

		}

			
		
		if(bear.getType() == ninjaType)
		{
if(freePlaces.size() > 0){	
				int output = std::rand()/((RAND_MAX + 1u)/freePlaces.size());
				if(isEmptyCheckNinja(freePlaces[output]))
					return freePlaces[output];}
				
			}
		
	

	return loc;
	
}
bool entitymanager::isEmpty(sf::Vector2i loc)
{
	if(triplemap->isEmpty(loc))
	{
		for(int i = 0; i < enemys.size(); i ++)
		{
				if(enemys[i].getDestination() == loc && enemys[i].getType() == bearType)
				{
						return false;
				}
				
			
		}
	}else{return false;}
	return true;
}
bool entitymanager::isEmptyCheckNinja(sf::Vector2i loc)
{
	if(triplemap->isEmpty(loc))
	{
		for(int i = 0; i < enemys.size(); i ++)
		{
				if(enemys[i].getDestination() == loc || enemys[i].getLocation() == loc)
				{
						return false;
				}
				
			
		}
	}else{return false;}
	return true;
}
bool entitymanager::isBear(sf::Vector2i loc)
{

		for(int i = 0; i < enemys.size(); i ++)
		{
			if(enemys[i].getLocation() == loc)
			{
					return true;
			}
		}
	
	return false;
}
rs::triple* entitymanager::getBear(sf::Vector2i loc)
{
		for(int i = 0; i < enemys.size(); i ++)
		{
			if(enemys[i].getLocation() == loc)
			{
					return &enemys[i];
					
			}
		}
		
		
		return b;
}
bool entitymanager::checkLoc(sf::Vector2i loc,int t)
{
	rs::triple* b = getBear(loc); 
	if(b->getType() == t)
	{
		for(int i = 0 ; i < sameNeighbours.size(); i++)
		{
			if(loc == sameNeighbours[i]->getLocation())
			{
				return false;
			}
			
		}
		addBearToCheckList(b);
		return true;
	
	}
	
	return false;
}
void entitymanager::getNeighbours(sf::Vector2i loc)
{	
	std::cout<<std::to_string(uncheckedsameNeighbours.size())<< std::endl;
	if(uncheckedsameNeighbours.size() >0){uncheckedsameNeighbours.pop_back();}
	if(loc.y - Tilewidth > 0){
	
		sf::Vector2i N(loc.x,(loc.y - Tilewidth));
		if(checkLoc(N,bearType))
		{
			std::cout<<"returning N "<< std::endl;
		}	
	
	}
	if(loc.y + Tilewidth < mapWidth*Tilewidth)
	{
		sf::Vector2i S(loc.x,(loc.y + Tilewidth));
	 	if(checkLoc(S,bearType))
		{
			std::cout<<"returning S " << std::to_string(loc.y + Tilewidth)<<"  " << std::to_string(loc.y)<< std::endl;
		}
	}
	if(loc.x - Tilewidth > 0 &&  loc.x - Tilewidth < mapWidth*Tilewidth){
	sf::Vector2i W((loc.x-Tilewidth), loc.y);
	 	if(checkLoc(W,bearType))
		{
			std::cout<<"returning W "<< std::endl;
		}
	}
	if(loc.x + Tilewidth < mapWidth*Tilewidth)
	{
		sf::Vector2i E((loc.x+Tilewidth), loc.y);	
		if(checkLoc(E,bearType))
		{
			std::cout<<"returning E "<< std::endl;
		}
	}

	sameNeighbours.push_back(getBear(loc));
	if(uncheckedsameNeighbours.size() > 0)
	{
		getNeighbours(uncheckedsameNeighbours.back()->getLocation());
	}
}

bool entitymanager::areNeighboursTrapped(sf::Vector2i normalCoords)
{
	sf::Vector2i loc(-1,-1);
	for(int i = 0 ; i < sameNeighbours.size(); i ++)
	{
		if(sameNeighbours.at(i)->getAnimated()){
		loc = sameNeighbours.at(i)->getLocation();
		
		if(loc == findPlace(*sameNeighbours.at(i)))
		{
			sameNeighbours.at(i)->setTrapped(true);
		}
		else
		{
			sameNeighbours.at(i)->setTrapped(false);
		}
	}
	}
					
	for(int i = 0 ; i < sameNeighbours.size(); i ++)
	{
		if( sameNeighbours.at(i)->getTrapped() == false)
		{
			for(int p = 0 ; p < sameNeighbours.size(); p ++)
			{
				sameNeighbours.at(p)->setTrapped(false);
			}
			return false;	
		}
	}	
	if(sameNeighbours.size()>2){
		while(sameNeighbours.size() > 0 )
		{
			triplemap->addGrave(sameNeighbours.back()->getLocation());
			removeBearNoCheck(sameNeighbours.back()->getLocation());
			sameNeighbours.pop_back();
		}
		triplemap->removeTriple(normalCoords);
		triplemap->addTriple(normalCoords,graveType);
	}
	else
	{
		while(sameNeighbours.size() > 0 )
		{
		//add graves///
		triplemap->addGrave(sameNeighbours.back()->getLocation());
		removeBearNoCheck(sameNeighbours.back()->getLocation());
		sameNeighbours.pop_back();
		}
	triplemap->removeTriple(normalCoords);
	triplemap->addTriple(normalCoords,graveType);
	}
	return true;
}
std::vector<rs::triple*> entitymanager::getAllTriples()
{
	std::vector<rs::triple*> mytriples;
	for(int i =0 ;i < enemys.size() ;i++)
	{
		mytriples.push_back(&enemys[i]);
	}
	return mytriples;
}
void entitymanager::render(sf::RenderWindow* window,float delta)
{	
	for(int i = 0; i < enemys.size(); i ++)
	{
		enemys[i].render(window,delta);
	}
}
    

};
