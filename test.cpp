#include "test.h"
#include <iostream>
#include <vector>
#include <cstdlib>


	
using namespace rs;
   
test::test(rs::screenmanager* sm):screen(sm)
{ 
    smptr = sm;
	tm = sm->getTextureManagerPtr();
	m_score = new rs::highscore(tm);
	m_map = new rs::tilemap(tm);
 	m_triplemap =new rs::triples(tm,m_score);
	m_entitymanager = new rs::entitymanager(tm,m_triplemap);	
	State = rs::state::game;	
	randomTriple = new rs::triple(sf::Vector2i(0,0));
	randomTriple->setOrigin(16,16);
	storedTriple = new rs::triple(sf::Vector2i(0,0));

	
	if(loadGame()){
		
		std::cout<<"loaded info \n";
		getNewTriple();

		
	}else{
	
std::cout<<"default info \n";
	gstate= zen;
	setDifficulty(gstate);
	seed = 1;
	std::srand(1);
	resetTripleType(randomTriple,getNewTriple());
	resetTripleType(storedTriple,0);
	storedTriple->setTexture(tm->getTexture(0));	
	m_score->setScore(0);	

	}
	
	cursor.setTexture(tm->getTexture(t_cursor));
	storage.setTexture(tm->getTexture(t_storage));
	storage.setLocation(sf::Vector2i(0,0));
	m_menu = new rs::mainmenu(tm,&State);
	
	p_mypanel   =new rs::panel(8,8,sf::Vector2i(0,0),tm);
	p_extra     = new rs::panel(6,5,sf::Vector2i(8.5*Tilewidth,Tilewidth+Tilewidth +Tilewidth),tm);
}
   
test::test(rs::screenmanager* sm ,rs::gamestate mode,int iseed):screen(sm)
{ 
    smptr = sm;
	tm = sm->getTextureManagerPtr();
	m_score = new rs::highscore(tm);
	m_map = new rs::tilemap(tm);
 	m_triplemap =new rs::triples(tm,m_score);
	m_entitymanager = new rs::entitymanager(tm,m_triplemap);	
	State = rs::state::game;	
	randomTriple = new rs::triple(sf::Vector2i(0,0));
	randomTriple->setOrigin(16,16);
	storedTriple = new rs::triple(sf::Vector2i(0,0));
	gstate= mode;
	setDifficulty(mode);
	seed = iseed;
	std::srand(seed);
	resetTripleType(randomTriple,getNewTriple());
	resetTripleType(storedTriple,0);
	storedTriple->setTexture(tm->getTexture(0));	
	m_score->setScore(0);	

	
	
	cursor.setTexture(tm->getTexture(t_cursor));
	storage.setTexture(tm->getTexture(t_storage));
	storage.setLocation(sf::Vector2i(0,0));
	m_menu = new rs::mainmenu(tm,&State);
	
	p_mypanel   =new rs::panel(8,8,sf::Vector2i(0,0),tm);
	p_extra     = new rs::panel(6,5,sf::Vector2i(8.5*Tilewidth,Tilewidth+Tilewidth +Tilewidth),tm);
}

test::~test()
{ 
	delete m_score;
	delete m_menu;
	delete m_go;
	delete p_extra;
	delete p_mypanel;
	delete m_entitymanager;
	delete storedTriple;
	delete randomTriple;
	delete m_triplemap;
	delete m_map;
}
void test::checkForHint()
{
		m_triplemap->emptySameNeighbours();
		
		
		std::vector<rs::triple*> temp ;
		temp.reserve(65* sizeof(rs::triple*));
		m_triplemap->getNeighboursGrave(&temp,normalCoords,randomTriple->getType());
		if(temp.size() > 2)
		{
			while(temp.size()>0)
			{
				sf::Vector2i reference = temp.back()->getLocation();
				sf::Vector2i moddable = reference;
				if(reference == normalCoords){temp.pop_back();
					
				}else{
					int dx = normalCoords.x - reference.x;
					int dy = normalCoords.y - reference.y;
					int nx=0;
					int ny=0;
					
					if (dx > 0){nx -= 4;}
					else if(dx < 0){nx += 4;}
					else{}
					
					if (dy > 0){ny -= 4;}
					else if(dy < 0){ny += 4;}
					else{}

					temp.back()->setSpriteLocation(nx,ny);
					temp.pop_back();
				
					}

			
			}m_triplemap->emptySameNeighbours();
		}
}
void test::newGame(uint8_t modeNumber,int seed){
	
	
	rs::gamestate g;
		switch (modeNumber)
	{
		case 1:
			g = rs::gamestate::zen;
			break;
		case 2:
			g = rs::gamestate::soft;
			break;
		case 3:
			g = rs::gamestate::hard;
			break;
		case 4:
			g = gstate;
			break;
		default:
			g = gstate;
			break;
			
	}
	smptr->newGame(g,seed);
}
void test::setDifficulty(rs::gamestate mode)
{
	switch (mode)
	{
		case zen:
			difficulty = 828;
			std::cout << "gamestate : zen \n";
			break;
		case soft:
			difficulty = 928;
			std::cout << "gamestate soft \n";
			break;
		case hard:
			difficulty = 1000;
			std::cout << "gamestate hard \n";
			break;
		default:
			difficulty = 1000;
			std::cout << "gamestate defaulted \n";
			break;
	}
}
bool test::queryGameOver()
{
	
// 	buildGameOverPanel();
// 	return true;
	if(m_triplemap->noFreeLocations())
		{
			if(storedTriple->getType()==robot)
			{
				///message player 
			}else{
			buildGameOverPanel();
			return true;
			}
		}
		
		return false;
}
void test::buildGameOverPanel()
{
	m_go = new rs::menugameover(tm,m_score->getScore(),m_score->getTurns());
}
uint16_t test::getNewTriple()
{
 	uint16_t n = 1 + std::rand()/((RAND_MAX + 1u)/difficulty);
 //	n = 1;
	
 	if(n < 601){return 1;}///grass///60%
 	else if(n > 600 && n < 751){return 2;}///bush///15%
 	else if(n > 750 && n< 771){return 3;}///tree///2
 	else if(n <770 && n< 778){return 4;}///house///0.6
 	else if(n <777 && n< 803){return  17;}///crystal///2.5
 	else if(n <802 && n< 828){return 16;}///robot///2.5
	else if(n > 827 && n < 928 ){return 19;}///bear///10
	else if(n >927 ){return 20;}///bear///7
	else{return 1;}
	return n;

}

void test::resetTriple()
{
	m_score->addTurn();
	
	
	if(queryGameOver())
	{
		State = gameover;
	}else{
		uint16_t temp = getNewTriple();
		resetTripleType(randomTriple,getNewTriple());
		
	}

}
void test::resetTripleType(rs::triple* t,uint16_t type)
{std::cout << "type"<< std::to_string(type) << std::endl;
	
		if(type == bearType || type == ninjaType)
	{
		t->setAnimated(true);
		t->setAnimSpeed(0.25f);
		t->setType(type);
		
		if(type == bearType	)
		{
			t->setFrames(tm->getFrames(215));
		}
		else
		{
			t->setFrames(tm->getFrames(167));	
		}
	}
	else
	{	t->setAnimated(false);
		t->setAnimSpeed(1.0f);
		t->setType(type);
		t->setFrames(tm->getFrames(m_triplemap->TypeToTextureNumber(type,false)));
	}	
}
uint16_t test::swapStored(rs::triple* t)
{
	uint16_t help = storedTriple->getType();
	uint16_t rTriple = t->getType();
	resetTripleType(storedTriple,rTriple);

	return help;
}
void  test::updateMap(int type)
{
		m_map->changeTextureOf(normalCoords,type);
		m_map->bitmaskit();
}
void  test::matchMap()
{
		for(int x = 0 ; x < mapHeight ; x++)
		{
			for(int y = 0 ; y <mapWidth ; y++)
			{
				int  index = x*mapWidth+y;
				sf::Vector2i loc = sf::Vector2i(x*Tilewidth,y*Tilewidth);
				uint16_t type = m_triplemap->getTriple(loc)->getType();
				
				if(x == 0  || y == 0 || x == mapWidth-1 || y == mapHeight-1 )
				{
					m_map->changeTextureOf(loc,0);	
				}
				else{
					if(type > 0)
					{
					m_map->changeTextureOf(loc,0);	
					}else
					{
					m_map->changeTextureOf(loc,1);	
					}
			}
		}
	}
	
		
		m_map->bitmaskit();
}
sf::Vector2i test::getN(sf::Vector2i loc){return sf::Vector2i(loc.x,loc.y-Tilewidth);}
sf::Vector2i test::getS(sf::Vector2i loc){return sf::Vector2i(loc.x,loc.y+Tilewidth);}
sf::Vector2i test::getE(sf::Vector2i loc){return sf::Vector2i(loc.x+Tilewidth,loc.y);}
sf::Vector2i test::getW(sf::Vector2i loc){return sf::Vector2i(loc.x-Tilewidth,loc.y);}

void test::checkBearAt(sf::Vector2i aLoction)
{
	if(m_entitymanager->isBear(aLoction))
	{	
		rs::triple* b = m_entitymanager->getBear(aLoction);
		m_entitymanager->emptySameNeighbours();
		m_entitymanager->addBearToCheckList(b);
		m_entitymanager->getNeighbours(aLoction);	
		if(m_entitymanager->areNeighboursTrapped(aLoction))
		{
			matchMap();
			resetTriple();
		}
		else
		{
		matchMap();
		resetTriple();
		}
		
	}	
}

void test::handleInput(sf::Event e)
{

	m_menu->handleInput(e,MouseCoords);
	
	m_score->handleInput(e);
	if(m_go != 0)
	{
		m_go->handleInput(e,MouseCoords	);
	}
	
	
	if(e.type == sf::Event::MouseMoved )
	{
		normalCoords.x = MouseCoords.x-(MouseCoords.x %Tilewidth);
		normalCoords.y = MouseCoords.y-(MouseCoords.y %Tilewidth);

		Tilespace.x = normalCoords.x/Tilewidth;
		Tilespace.y = normalCoords.y/Tilewidth;
		
	}

	if(e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left )
	{

		if(State == game){
			if(normalCoords.x == 0 && normalCoords.y ==0)
			{
				if(stored)
				{
					uint16_t type = swapStored(randomTriple);
					resetTripleType(randomTriple,type);
				}else
				{
					stored = true;
					uint16_t temp = randomTriple->getType();
					swapStored(randomTriple);	
					resetTriple();
				}
			}
			if(normalCoords.x != 0 && normalCoords.y !=0 && normalCoords.x/Tilewidth < mapWidth-1 && normalCoords.y/Tilewidth < mapHeight-1 )
			{
				if(m_triplemap->getTriple(normalCoords)->getType() == chest || m_triplemap->getTriple(normalCoords)->getType() == b_chest)
				{
					updateMap(1);
					if(m_triplemap->removeTriple(normalCoords))
					{
						matchMap();
						resetTriple();
						return;
					}	
				}
				
				
				uint16_t rtype = randomTriple->getType();
				
				//////BEAR////
				if(rtype == bearType || rtype ==  ninjaType)
				{
					if(m_triplemap->isEmpty(normalCoords)){
						if(m_entitymanager->isEmptyCheckNinja(normalCoords)){
							if(m_entitymanager->addBear(rtype,normalCoords))
							{
								m_entitymanager->moveEnemys();
								m_entitymanager->updateTrapped();
								matchMap();
								resetTriple();
							}
						}
					}
				}
				/////robot///
				else if(rtype == robot)
						{
							updateMap(1);
							
							if(m_triplemap->removeTriple(normalCoords))
							{
								m_entitymanager->moveEnemys();
								m_entitymanager->updateTrapped();
								matchMap();
								resetTriple();
							}
							else if(m_entitymanager->removeBear(normalCoords))
							{
									m_entitymanager->moveEnemys();
									m_entitymanager->updateTrapped();
									matchMap();
									resetTriple();
							}
								else{
									//do nothing
									std::cout << "robot found nothing \n";
									std::cout << std::to_string(normalCoords.x)<<","<<std::to_string(normalCoords.y)<< "\n";
								}
						}
				else if(rtype == crystal)
				{
					//crystal//
					if(m_triplemap->isEmpty(normalCoords))
						{
						for(uint16_t i = 15 ; i > 0 ;i--)
						{std::cout << std::to_string(i) << ",";
							m_triplemap->getTriple(normalCoords)->setType(i);
							if(m_triplemap->checkForPromotion(normalCoords))
							{ /////looking for combo////
								updateMap(0);
								
								m_triplemap->getTriple(normalCoords)->setType((uint16_t)0);
								m_triplemap->addTriple(normalCoords,(uint16_t)i);
								m_entitymanager->moveEnemys();
								m_entitymanager->updateTrapped();
								matchMap();
								resetTriple();
								return;
							}
						}
						if(m_triplemap->getTriple(normalCoords)->getType() == 1)
						{//////unable to find combination , placing rock ////
							m_triplemap->getTriple(normalCoords)->setType((uint16_t)0);
							if(m_triplemap->addTriple(normalCoords,(uint16_t)rock))
							{
								updateMap(0);
								m_entitymanager->moveEnemys();
								m_entitymanager->updateTrapped();
								matchMap();
								resetTriple();
								return;
							}
						}
					}
				}
				else{
							if(m_entitymanager->isEmptyCheckNinja(normalCoords))
							{
								if(m_triplemap->addTriple(normalCoords,rtype))
								{////normal placement////
									updateMap(0);
									m_entitymanager->moveEnemys();
									m_entitymanager->updateTrapped();
									sf::Vector2i aLoction = getN(normalCoords);
									checkBearAt(aLoction);
									aLoction = getS(normalCoords);
									checkBearAt(aLoction);
									aLoction = getE(normalCoords);
									checkBearAt(aLoction);
									aLoction = getW(normalCoords);
									checkBearAt(aLoction);
									matchMap();
									resetTriple();

									return;
								}
							}
						}
				}
		}

	}
			if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				if(m_entitymanager->removeBear(normalCoords)){
				
				m_map->changeTextureOf(normalCoords,0);
				m_map->bitmaskit();}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			{
				
			}  
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				resetTriple();
			} 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
			{
					resetTripleType(randomTriple,16);
			} 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
			{
					resetTripleType(randomTriple,19);
			} 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
			{
					resetTripleType(randomTriple,20);
			} 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F10))
			{
					smptr->newGame(rs::gamestate::hard,1);
			} 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
			{
					smptr->newGame(rs::gamestate::soft,1);
			} 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F12))
			{
					smptr->newGame(rs::gamestate::zen,1);
			} 

			if (e.type == sf::Event::Closed)
			{
				saveGame(m_triplemap->getAllTriples(),
						 m_entitymanager->getAllTriples(),
						 m_score->getScore(),
						 m_score->getTurns(),
						 storedTriple->getType(),
						 randomTriple->getType()
						);
			}		
			


}

void test::updateCursor(sf::Vector2i loc,float delta)
{
	if(loc.x > (mapWidth-1)*Tilewidth)
	{
		randomTriple->setLocation(randomTriple->getLocation());
	}else{
		cursor.setPosition(normalCoords.x,normalCoords.y);
		randomTriple->setLocation(sf::Vector2i(normalCoords.x+halfTilewidth ,normalCoords.y+halfTilewidth));
		randomTriple->setDestination(sf::Vector2i(normalCoords.x+halfTilewidth ,normalCoords.y+halfTilewidth));
		randomTriple->setScale(rt_scaleAcum,rt_scaleAcum);
		
		
		
		
	if(biggening){
	rt_scaleAcum+=delta;
	if(rt_scaleAcum > 1.1f)
	{
		biggening = false;
		
	}
	}else{
		rt_scaleAcum-=delta;
		if(rt_scaleAcum < 0.8f)
		{
			biggening = true;
			
		}
	}	
	}
}
void test::saveGame(std::vector<rs::triple*> myTriples,std::vector<rs::triple*> myBears,long score,int turns,uint16_t storedType,uint16_t randomType)
{
	
	
	////add game mode //
	//seed////
	  if( remove( "save/testmap" ) == 0 ){
  
	std::cout << "saving map" << std::endl;
    std::ofstream myoutfile("save/testmap");
    for(int i = 0 ; i < myTriples.size(); i++){
		sf::Vector2i loc = myTriples[i]->getLocation();
		uint16_t typ = myTriples[i]->getType();
		if(typ != 0)
		{
        myoutfile       << "t " <<
					myTriples[i]->getType() <<
					" " << loc.x/Tilewidth  <<
					" " << loc.y/Tilewidth  <<
					" " << myTriples[i]->getSuper()<<
					"\n";
		}
    }
	for(int i = 0 ; i < myBears.size(); i++){
		sf::Vector2i loc = myBears[i]->getLocation();
        myoutfile << "b " << myBears[i]->getType() <<" " << loc.x/Tilewidth<<" " << loc.y/Tilewidth << " " << 1 << "\n";
    }
    myoutfile << "s " << storedType << "\n";
    myoutfile << "r " << randomType << "\n";	
	myoutfile << "h " << score 		<< "\n";
	myoutfile << "c " << turns      << "\n";
	myoutfile << "e " << seed 		<< "\n";
	
	switch(gstate)
	{
		case zen:
		myoutfile << "m " << 1		<< "\n";	
		break;
		case soft:
		myoutfile << "m " << 2 		<< "\n";	
		break;
		case hard:
		myoutfile << "m " << 3 		<< "\n";	
		break;
		case setseed:
		myoutfile << "m " << 4		<< "\n";	
		break;		
	}
	
myoutfile.close();
	  }
	  else{
	std::cout << "UNABLE TO DELETE :"  << std::endl;	  
	}
}
bool test::loadGame()
{
	std::string line;
	std::ifstream fstr;
	std::vector<int> info;
	fstr.open("save/testmap");
	
	if(fstr.is_open())
	{
		while(fstr.good())
		{
			getline(fstr,line);
			const char* linetochar = line.c_str();
			int length,start,counter;
			switch (linetochar[0])
			{
				case 't':
					if(linetochar[1] == ' ')
				{ 
					  length = line.length();
					  start = 2;
					  counter= 2;
						
					while(counter <= length)
					{
					if(linetochar[counter] == ' ' || counter == length) 
					{
						info.push_back(std::stoi(line.substr(start,counter-1).c_str()))  ;
						counter++;
						start = counter;
					}else{ 
					counter++;}
					}
				}
					break;
				case 'b':
					if(linetochar[1] == ' ')
				{ 
					  length = line.length();
					  start = 2;
					  counter= 2;
						
					while(counter <= length)
					{
						if(linetochar[counter] == ' ' || counter == length) 
						{
							info.push_back(std::stoi(line.substr(start,counter-1).c_str()))  ;
							counter++;
							start = counter;
						} else{ 
						counter++;}
					}
				}
					break;
				case 's':	  length = line.length();
							  start = 2;
							  counter= 2;
							while(counter <= length)
							{
							if(linetochar[counter] == ' ' || counter == length) 
							{
								stored = true;
								resetTripleType(storedTriple,(uint16_t)std::stoi(line.substr(start,counter-1).c_str()));
								counter++;
								start = counter;
							}else{ 
							counter++;}
							}
						
					break;
				case 'r':     length = line.length();
							  start = 2;
							  counter= 2;
							while(counter <= length)
							{
							if(linetochar[counter] == ' ' || counter == length) 
							{
								resetTripleType(randomTriple,(uint16_t)std::stoi(line.substr(start,counter-1).c_str()));
								counter++;
								start = counter;
							}else{ 
							counter++;}
							}	
					break;
				case 'h':	  length = line.length();
							  start = 2;
							  counter= 2;
							while(counter <= length)
							{
							if(linetochar[counter] == ' ' || counter == length) 
							{
								m_score->setScore(std::stol(line.substr(start,counter-1).c_str()));
								counter++;
								start = counter;
							}else{ 
							counter++;}
							}		
					break;
				case 'c':	  length = line.length();
							  start = 2;
							  counter= 2;
							while(counter <= length)
							{
							if(linetochar[counter] == ' ' || counter == length) 
							{
								m_score->setTurns(std::stoi(line.substr(start,counter-1).c_str()));
								counter++;
								start = counter;
							}else{ 
							counter++;}
							}
					break;
				case 'e':	  length = line.length();
							  start = 2;
							  counter= 2;
							while(counter <= length)
							{
							if(linetochar[counter] == ' ' || counter == length) 
							{
								seed = std::stoi(line.substr(start,counter-1).c_str());
								std::srand(seed);
								std::cout << "seed:"<<std::to_string(seed) << std::endl;
// 								for(int seeder = 0 ;seeder <= m_score->getTurns();seeder++)
// 								{////run random seed back to where it was////
// 									int t = 1 + std::rand()/((RAND_MAX + 1u)/difficulty);
// 								}
								counter++;
								start = counter;
							}else{ 
							counter++;}
							}
					break;
				case 'm':	  length = line.length();
							  start = 2;
							  counter= 2;
							while(counter <= length)
							{
							if(linetochar[counter] == ' ' || counter == length) 
							{
								
								switch( std::stoi(line.substr(start,counter-1).c_str())){
									case 1:gstate = zen ;
										break;
									case 2:gstate = soft ;
										break;
									case 3:gstate = hard ;
										break;
									case 4:gstate = setseed ;
										break;
								}
								
								setDifficulty(gstate);
								
								
								counter++;
								start = counter;
							}else{ 
							counter++;}
							}
					break;
				}
					}
					
	               fstr.close(); 
				   
			for(int i = 0 ; i < info.size() ; i+=4)
			{
				int type = info[i];
				int x = info[i+1] * Tilewidth;
				int y = info[i+2] * Tilewidth;
				bool b = info[i+3];
				sf::Vector2i loc(x,y);
				if(info[i] <= 18)
				{
					m_triplemap->getTriple(loc)->setType(type);
					m_triplemap->getTriple(loc)->setSuper(b);
					m_triplemap->changeTextureOf(loc,m_triplemap->TypeToTextureNumber(type,b));
				}else{
					m_entitymanager->addBear((uint16_t)type,loc);
				}
			}
			matchMap();	   
				   
			}else{
				return false;
	   std::cout << "UNABLE TO LOAD :"  << std::endl;
				
			}
			return true;
}
void test::render(sf::RenderWindow* window,float delta){
	hintTimer += delta;
	if(hintTimer > 0.5f)
	{
		checkForHint();
		hintTimer = 0.0f;
	}
	
	m_score->render(window,delta);
	p_mypanel->render(window);
	p_extra->render(window);
    m_map->render(window);
	m_triplemap->render(window,delta);
	m_entitymanager->render(window,delta);
	storage.render(window);
	updateCursor(normalCoords,delta);
	//cursor.setPosition(normalCoords.x,normalCoords.y);
	

	
	

	
	if(State == gameover)
	{

	if(m_go->onClose())
	{
// 				if(m_menu->newGame() != 0){
// 	delete m_menu;}
		m_menu = new rs::mainmenu(tm,&State);
		State = menu;
		
	}
	m_go->render(window,delta);}
	
	
	
	randomTriple->render(window,delta);	
	storedTriple->render(window,delta);
	window->draw(cursor);
	
	
	if(m_menu->newGame() != 0){
		newGame(m_menu->newGame(),m_menu->getSeed());
		
	}
	m_menu ->render(window,delta);
	
	
	
	

	
}

