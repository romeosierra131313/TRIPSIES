
#include <iostream>
#include "triples.h" 
#define t_offset 110


namespace rs{

   
triples::triples(rs::texturemanager* tm,rs::highscore* hs)
{
    totalTiles = mapWidth*mapHeight;
	texMngr = tm;
	scorer = hs;
	
	triplets.reserve(totalTiles* sizeof(rs::triple));
        for(int x = 0 ; x < mapHeight ; x++)
		{
			for(int y = 0 ; y <mapWidth ; y++)
			{
				rs::triple t(sf::Vector2i((x*Tilewidth),(y*Tilewidth)),0.5f,tm->getFrames(TypeToTextureNumber(0,false)));
			//	rs::triple t(sf::Vector2i((x*Tilewidth),(y*Tilewidth)));

				triplets.push_back(t);
			}
		}
}
triples::~triples()
{
}

bool triples::addTriple(sf::Vector2i loc,uint16_t type)
{
//	emptySameNeighbours();
	if(isEmpty(loc))
	{
		getTriple(loc)->setType(type);
		changeTextureOf(loc,TypeToTextureNumber(type,false));
		
		if(type < chest)
		{
		scorer->getScoreValue(type,false,false);
			
		}
		
			if(checkForPromotion(loc))
			{
				texMngr->play(1);
				doPromotion(loc);
				return true;
			}
			else
			{
				texMngr->play(2);
				return true;
			}
	}
	else
	{
		
		//TODO :- cahnge to false for final release
		
		
		return true;
		//do nothing//
	}
	return false;
}
void triples::addGrave(sf::Vector2i loc)
{

		getTriple(loc)->setType(graveType);
		changeTextureOf(loc,TypeToTextureNumber(graveType,false));


}
bool triples::removeTriple(sf::Vector2i loc)
{
	if(!isEmpty(loc))
	{	
		rs::triple* t = getTriple(loc);
	//	uint16_t type = 
		scorer->getScoreValue(t->getType(),true,t->getSuper());
		t->setType(0);
		t->setSuper(false);
		t->setTexture(texMngr->getTexture(0));
		return true;
	}
	return false;
}

bool triples::isEmpty(sf::Vector2i loc)
{
	if( getTriple(loc)->getType() == 0 )
	{
	return true;
	}
 	return false;
}
rs::triple* triples::getTriple(sf::Vector2i loc)
{
		return &triplets[loc.x/Tilewidth * mapWidth + loc.y/Tilewidth ];
}
rs::triple* triples::getTriple(int index)
{
		return &triplets[index];
}
uint16_t triples::getType(sf::Vector2i loc)
{
return getTriple(loc)->getType();	
}
void triples::setType(sf::Vector2i loc,uint16_t newType)
{
	getTriple(loc)->setType((uint16_t)newType);
}
bool triples::checkNorth(sf::Vector2i loc,int t)
{

	if(loc.y-Tilewidth >=0)
	{
		if(getTriple(sf::Vector2i(loc.x,(loc.y-Tilewidth)))->getType() == t)
		{
			return true;
		}	
	}
	return false;
}
bool triples::checkSouth(sf::Vector2i loc,int t)
{
	if(loc.y+Tilewidth <=mapHeight*Tilewidth){
		if(getTriple(sf::Vector2i(loc.x,loc.y+Tilewidth))->getType() == t)
		{
			return true;
		}	
	}
	return false;
}
bool triples::checkWest(sf::Vector2i loc,int t)
{
	if(loc.x-Tilewidth >=0){
		if(getTriple(sf::Vector2i(loc.x-Tilewidth,loc.y))->getType() == t)
		{
			return true;	
		}
	}
	return false;
}
bool triples::checkEast(sf::Vector2i loc,int t)
{
	if(loc.x+Tilewidth <=mapWidth*Tilewidth){
		if(getTriple(sf::Vector2i(loc.x+Tilewidth,loc.y))->getType() == t)
		{
			return true;
		}
	}
	return false;
}
bool triples::checkNorthWest(sf::Vector2i loc,int t)
{
	if(getTriple(sf::Vector2i(loc.x-Tilewidth,loc.y-Tilewidth))->getType() == t)
	{
		return true;
	}
	return false;
}
bool triples::checkNorthEast(sf::Vector2i loc,int t)
{
	if(getTriple(sf::Vector2i(loc.x+Tilewidth,loc.y-Tilewidth))->getType() == t)
	{
		return true;
	}
	return false;
}
bool triples::checkSouthWest(sf::Vector2i loc,int t)
{
	if(getTriple(sf::Vector2i(loc.x-Tilewidth,loc.y+Tilewidth))->getType() == t)
	{
		return true;
	}
	return false;

}
bool triples::checkSouthEast(sf::Vector2i loc,int t)
{
	if(getTriple(sf::Vector2i(loc.x+Tilewidth,loc.y+Tilewidth))->getType() == t)
	{
		return true;
	}
	return false;
	
}
bool triples::checkNorthNorth(sf::Vector2i loc,int t)
{
	if(getTriple(sf::Vector2i(loc.x,loc.y-(2*Tilewidth)))->getType() == t)
	{
		return true;
	}
	return false;
}
bool triples::checkSouthSouth(sf::Vector2i loc,int t)
{
	if(getTriple(sf::Vector2i(loc.x,loc.y+(2*Tilewidth)))->getType() == t)
	{
		return true;
	}
	return false;
}
bool triples::checkWestWest(sf::Vector2i loc,int t)
{
	if(getTriple(sf::Vector2i(loc.x-(2*Tilewidth),loc.y))->getType() == t)
	{
		return true;
	}
	return false;	
}

bool triples::checkEastEast(sf::Vector2i loc,int t)
{
	if(getTriple(sf::Vector2i(loc.x+(2*Tilewidth),loc.y))->getType() == t)
	{
		return true;
	}
	return false;		
}

bool triples::checkForPromotion(sf::Vector2i loc)
{	
	int counter = 0 ;
	uint16_t t = getTriple(loc)->getType();
	
 	if(checkNorth(loc,t))
	{
		counter++;
		if(checkNorthNorth(loc,t)){counter++;}
		if(checkNorthEast(loc,t)){counter++;}
		if(checkNorthWest(loc,t)){counter++;}
	}
 	if(checkSouth(loc,t))
	{
		counter++;
		if(checkSouthSouth(loc,t)){counter++;}
		if(checkSouthEast(loc,t)){counter++;}
		if(checkSouthWest(loc,t)){counter++;}		
	}
 	if(checkWest(loc,t))
	{
		counter++;
		if(checkWestWest(loc,t)){counter++;}
		if(checkNorthWest(loc,t)){counter++;}
		if(checkSouthWest(loc,t)){counter++;}
	}
 	if(checkEast(loc,t))
	{
		counter++;
		if(checkEastEast(loc,t)){counter++;}
		if(checkNorthEast(loc,t)){counter++;}
		if(checkSouthEast(loc,t)){counter++;}		
	}	
	if(counter > 1){
		return true;
		
	}
	
	return false;
	
}
void triples::doPromotion(sf::Vector2i loc)
{
	
	uint16_t type = getTriple(loc)->getType();
	int localindex =(loc.x/Tilewidth) * mapWidth + (loc.y /Tilewidth);
	emptySameNeighbours();
	getNeighbours(loc);	
	int neighbours = sNeighbours.size();
	
	while(sNeighbours.size()>0)
	{
		if(sNeighbours.back() == localindex){sNeighbours.pop_back();}else{
			scorer->getScoreValue(getTriple(sNeighbours.back())->getType(),false,getTriple(sNeighbours.back())->getSuper());
		    std::cout<<sNeighbours.size() << "--size";
			
			getTriple(sNeighbours.back())->setType(0);
			getTriple(sNeighbours.back())->setTexture(texMngr->getTexture(0));
			sNeighbours.pop_back();}
	}
		if(type > 8)
	{
		switch (type)
		{
			case rock://rock
				getTriple(loc)->setType(b_rock);
				changeTextureOf(loc,161);				
				break;
			case b_rock://b_rock
				getTriple(loc)->setType(chest);
				changeTextureOf(loc,162);
				break;
			case graveType:
				getTriple(loc)->setType(church);
				changeTextureOf(loc,165);
				break;
			case church:
				getTriple(loc)->setType(b_church);
				changeTextureOf(loc,166);
				break;
			case b_church:
				getTriple(loc)->setType(chest);
				changeTextureOf(loc,162);
			case chest:
				getTriple(loc)->setType(b_chest);
				changeTextureOf(loc,163);
				break;
			
		}
	}else{
		

	if      (neighbours >= 3)
		{
			getTriple(loc)->setType(getTriple(loc)->getType()+1);
			getTriple(loc)->setSuper(true);
			scorer->getScoreValue(getTriple(loc)->getType(),false,true);
			changeTextureOf(loc,TypeToTextureNumber(getTriple(loc)->getType(),true));
			
		}
	else if (neighbours == 2)
		{
			getTriple(loc)->setType(getTriple(loc)->getType()+1);
			scorer->getScoreValue(getTriple(loc)->getType(),false,false);
	     	changeTextureOf(loc,TypeToTextureNumber(getTriple(loc)->getType(),false));
		}
	else if	(neighbours <  1)
		{
			changeTextureOf(loc,TypeToTextureNumber(rock,false));
			getTriple(loc)->setType(rock);
		}
	}
	if(checkForPromotion(loc)){doPromotion(loc);}
	
}
void triples::changeTextureOf(sf::Vector2i loc,int ntexIndex)
{
	getTriple(loc)->setFrames(texMngr->getFrames(ntexIndex));
}
int triples::TypeToTextureNumber(uint16_t type,bool isSuper)
{
		if(type > 8)
	{
		switch (type)
		{
			case rock:
				return 160;				
				break;
			case b_rock://b_rock
				return 161;
				break;
			case graveType:
				return 164;
				break;
			case church:
				return 165;
				break;
			case b_church:
				return 166;
			case chest:
				return 162;
			case b_chest:
				return 163;
				break;
			case crystal:
				return 209;
				break;
			case robot:
				return 208;
				break;
			
		}
	}else{
		if(isSuper== true)
		{
			return  t_offset +(type * 2 )+1  ;
		}
		else
		{
			return  t_offset +(type * 2 ) ;
		}
	}		
		std::cout<< "Failed to convert type to texture." << std::endl;
		return 1;
		
}
void triples::getNeighbours(sf::Vector2i loc)
{
	uint16_t t = getTriple(loc)->getType();
	//sNeighbours.erase(sNeighbours.begin(),sNeighbours.end());	
	
	int N = loc.x/Tilewidth * mapWidth + ((loc.y /Tilewidth)-1);
	int S = loc.x/Tilewidth * mapWidth + ((loc.y /Tilewidth)+1);
	int W = ((loc.x/Tilewidth)-1) * mapWidth + loc.y /Tilewidth;
	int E = ((loc.x/Tilewidth)+1) * mapWidth + loc.y /Tilewidth;
	
	int NN = loc.x/Tilewidth * mapWidth + ((loc.y /Tilewidth)-2);
	int SS = loc.x/Tilewidth * mapWidth + ((loc.y /Tilewidth)+2);
	int WW = ((loc.x/Tilewidth)-2) * mapWidth + loc.y /Tilewidth;
	int EE = ((loc.x/Tilewidth)+2) * mapWidth + loc.y /Tilewidth;
	
	int NE = ((loc.x/Tilewidth)+1) * mapWidth + ((loc.y /Tilewidth)-1);
	int NW = ((loc.x/Tilewidth)-1) * mapWidth + ((loc.y /Tilewidth)-1);
	int SE = ((loc.x/Tilewidth)+1) * mapWidth + ((loc.y /Tilewidth)+1);
	int SW = ((loc.x/Tilewidth)-1) * mapWidth + ((loc.y /Tilewidth)+1);	
	
 	if(checkNorth(loc,t))
	{
		sNeighbours.push_back(N);
		if(checkNorthNorth(loc,t)){sNeighbours.push_back(NN);}
		if(checkNorthEast(loc,t)){sNeighbours.push_back(NE);}
		if(checkNorthWest(loc,t)){sNeighbours.push_back(NW);}
	}
 	if(checkSouth(loc,t))
	{
		sNeighbours.push_back(S);
		if(checkSouthSouth(loc,t)){sNeighbours.push_back(SS);}
		if(checkSouthEast(loc,t)){sNeighbours.push_back(SE);}
		if(checkSouthWest(loc,t)){sNeighbours.push_back(SW);}		
	}
 	if(checkWest(loc,t))
	{
		sNeighbours.push_back(W);
		if(checkWestWest(loc,t)){sNeighbours.push_back(WW);}
		if(checkNorthWest(loc,t)){sNeighbours.push_back(NW);}
		if(checkSouthWest(loc,t)){sNeighbours.push_back(SW);}
	}
 	if(checkEast(loc,t))
	{
		sNeighbours.push_back(E);
		if(checkEastEast(loc,t)){sNeighbours.push_back(EE);}
		if(checkNorthEast(loc,t)){sNeighbours.push_back(NE);}
		if(checkSouthEast(loc,t)){sNeighbours.push_back(SE);}		
	}	
	
	
}
void triples::emptySameNeighbours()
{
	while(sameNeighbours.size()>0)
		{
		sameNeighbours.pop_back();
		}	
}
void triples::getNeighboursGrave(std::vector<rs::triple*>* ng,sf::Vector2i loc,uint16_t type)
{	
	std::cout<<std::to_string(uncheckedsameNeighbours.size())<< std::endl;
	if(uncheckedsameNeighbours.size() >0){uncheckedsameNeighbours.pop_back();}
	
	int iloc =loc.x/Tilewidth * mapWidth + (loc.y /Tilewidth);
	int iN = loc.x/Tilewidth * mapWidth + ((loc.y /Tilewidth)-1);
	int iS = loc.x/Tilewidth * mapWidth + ((loc.y /Tilewidth)+1);
	int iW = ((loc.x/Tilewidth)-1) * mapWidth + loc.y /Tilewidth;
	int iE = ((loc.x/Tilewidth)+1) * mapWidth + loc.y /Tilewidth;
	
	sf::Vector2i N(loc.x,(loc.y - Tilewidth));
	sf::Vector2i S(loc.x,(loc.y + Tilewidth));
	sf::Vector2i W((loc.x-Tilewidth), loc.y);	
	sf::Vector2i E((loc.x+Tilewidth), loc.y);	
	
	if(contains(ng,N)){}else{
		if(checkNorth(loc,type))
		{
			uncheckedsameNeighbours.push_back(getTriple(N));
		//	sNeighbours.push_back(iN);
		}	
	}
	if(contains(ng,S)){}else{
	 	if(checkSouth(loc,type))
		{
			uncheckedsameNeighbours.push_back(getTriple(S));
		//	sNeighbours.push_back(iS);
		}
	}
	if(contains(ng,W)){}else{
	 	if(checkWest(loc,type))
		{
			uncheckedsameNeighbours.push_back(getTriple(W));
		//	sNeighbours.push_back(iW);
		}
	}
	if(contains(ng,E)){}else{	
		if(checkEast(loc,type))
		{
			uncheckedsameNeighbours.push_back(getTriple(E));
		//	sNeighbours.push_back(iE);
		}
	}

	ng->push_back(getTriple(loc));
	//sNeighbours.push_back(iloc);
	if(uncheckedsameNeighbours.size() > 0)
	{
		getNeighboursGrave(ng,uncheckedsameNeighbours.back()->getLocation(),type);
	}
	
}
bool triples::contains(std::vector<rs::triple*>* ng,sf::Vector2i loc)
{
	for(int x = 0 ; x < ng->size() ; x++)
	{
		if(ng->at(x)->getLocation() == loc )
		{
			return true;
		}
	}
	return false;
}
std::vector<sf::Vector2i> triples::getFreeLocations()
{
	std::vector<sf::Vector2i> freePlaces;
	freePlaces.reserve((totalTiles)  * sizeof(rs::triple));
        for(int x = 1 ; x < mapHeight-1 ; x++)
		{
			for(int y = 1 ; y <mapWidth-1 ; y++)
			{
				sf::Vector2i loc((x*Tilewidth),(y*Tilewidth));
				if(isEmpty(loc))
				{
					freePlaces.push_back(loc);
				}
			
			}
		}
		return freePlaces;
}
bool triples::noFreeLocations()
{
        for(int x = 1 ; x < mapHeight-1 ; x++)
		{
			for(int y = 1 ; y <mapWidth-1 ; y++)
			{
				sf::Vector2i loc((x*Tilewidth),(y*Tilewidth));
				if(isEmpty(loc))
				{
					return false;
				}
			
			}
		}
		return true;
}
std::vector<rs::triple*> triples::getAllTriples()
{
	std::vector<rs::triple*> mytriples;
	for(int i =0 ;i < totalTiles ;i++)
	{
		mytriples.push_back(&triplets[i]);
	}
	return mytriples;
	
	
}
void triples::render(sf::RenderWindow* window,float delta)
{
	for(int i =0 ;i < totalTiles ;i++)
	{
		triplets[i].render(window,delta);
	}
 }
        

};
