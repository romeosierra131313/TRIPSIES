#include "tilemap.h"
#include <stdlib.h>  

namespace rs{
  
tilemap::tilemap(rs::texturemanager* texM)
{
    int onelesswidth = mapWidth-1;
	int onelesswheight = mapHeight-1;
    texMngr = texM;
    totalTiles = mapWidth*mapHeight;
    offsetX = 0;
    offsetY = 0;

	tiles.reserve(totalTiles* sizeof(rs::tile));
        for(int x = 0 ; x < mapHeight ; x++)
		{
			for(int y = 0 ; y <mapWidth ; y++)
			{
				int  index = x*mapWidth+y;
				rs::tile t;
				t.setLocation(sf::Vector2i((x*Tilewidth),(y*Tilewidth)));
				tiles.push_back(t);
				if(x == 0  || y == 0 || x == onelesswidth || y == onelesswheight )
				{
					changeTextureOf(sf::Vector2i(x*Tilewidth,y*Tilewidth),0);	
				}
					else
					{
						changeTextureOf(sf::Vector2i(x*Tilewidth,y*Tilewidth),1);
					}
				
				
			}
		}

	bitmaskit();
}
tilemap::~tilemap()
{
	//delete  tiles;
}
void tilemap::randomMap(){
    for(int y = 0 ; y <mapHeight ; y++){
        for(int x = 0 ; x <mapWidth ; x++){
           int  index = x*mapWidth+y;
            tiles[index].setLocation(sf::Vector2i((x*Tilewidth),(y*Tilewidth)));
            int prng = std::rand()%2;
            std::cout << prng << " , " ;
            if(x == 0 || x == mapWidth -1 || y == 0 || y == mapHeight -1){
                 tiles[index].setType(uint16_t(0)); 
            }else{
                tiles[index].setType(uint16_t(prng));  } 
      
            }
        }   
    
bitmaskit();    
}
void tilemap::applyPerlin()
{
  float seed[mapWidth*mapHeight];
  float fOutput[mapWidth*mapHeight];
  for(int s = 0; s < totalTiles ; s++){seed[s] = (float)std::rand()/(float)RAND_MAX;}
    
    

        for(int y = 0 ; y <mapHeight ; y++){
        for(int x = 0 ; x <mapWidth ; x++){
        	float fNoise = 0.0f;
				float fScaleAcc = 0.0f;
				float fScale = 1.0f;

				for (int o = 0; o < 4; o++)
				{
					int nPitch = mapWidth >> o;
					int nSampleX1 = (x / nPitch) * nPitch;
					int nSampleY1 = (y / nPitch) * nPitch;
					
					int nSampleX2 = (nSampleX1 + nPitch) % mapWidth;					
					int nSampleY2 = (nSampleY1 + nPitch) % mapWidth;

					float fBlendX = (float)(x - nSampleX1) / (float)nPitch;
					float fBlendY = (float)(y - nSampleY1) / (float)nPitch;

					float fSampleT = (1.0f - fBlendX) * seed[nSampleY1 * mapWidth + nSampleX1] + fBlendX * seed[nSampleY1 * mapWidth + nSampleX2];
					float fSampleB = (1.0f - fBlendX) * seed[nSampleY2 * mapWidth + nSampleX1] + fBlendX * seed[nSampleY2 * mapWidth + nSampleX2];

					fScaleAcc += fScale;
					fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
					fScale = fScale / 2.0f;
				
        }

				// Scale to seed range
				fOutput[y * mapWidth + x] = fNoise / fScaleAcc;
        }
        }      
            int index = 0;
        for(int y = 0 ; y <mapHeight ; y++){
        for(int x = 0 ; x <mapWidth ; x++){
            index = x*mapWidth+y;
            tiles[index].setLocation(sf::Vector2i((x*Tilewidth),(y*Tilewidth)));
            if(x == 0 || x == mapWidth -1 || y == 0 || y == mapHeight -1){
            tiles[index].setTexture(texMngr->getTexture(49));
            tiles[index].setType(uint16_t(0));               
                
            }else{
            if(seed[index] < 0.2f ){
            tiles[index].setTexture(texMngr->getTexture(49));
            tiles[index].setType(uint16_t(0));
            }else{
                tiles[index].setType(uint16_t(1));   
              }   
            }
        }
        }
}
void tilemap::doSmoothing()
{
     int    index = 0;
        for(int y = 0 ; y <mapHeight ; y++){
        for(int x = 0 ; x <mapWidth ; x++){
            index = x*mapWidth+y;
            int mask = getNeighbours(tiles[index].getLocation2i());

            if(mask == 0 || mask == 1  || mask == 4 || mask == 32 || mask == 33 ||
                mask == 36 || mask == 37 || mask == 128 || mask == 129|| mask ==132|| mask ==133|| mask ==160|| mask ==164|| mask ==165 ){
                        tiles[index].setTexture(texMngr->getTexture(1));
                        tiles[index].setType(uint16_t(1)); 

            }
            if(mask == 255){changeTextureOf(tiles[index].getLocation2i(),1);}
            
            else{
                         // changeTextureOf(sf::Vector2i(tiles[index].getLocation().x,tiles[index].getLocation().y),1);
                ;}

            }
            
        }   
    
}
rs::tile tilemap::getTile(sf::Vector2i location)
{
    int index = ((location.x/Tilewidth)*mapWidth)+location.y;
    if(index < totalTiles){
    return tiles[((location.x/Tilewidth)*mapWidth)+location.y] ;}
    rs::tile til;
    til.setType(-1);
    return til;
}
void tilemap::changeTextureOf(sf::Vector2i location,int textureNumber)
{
        int index = (location.x/Tilewidth)*mapWidth+(location.y/Tilewidth);
    if(index < totalTiles){ 
 
    if(textureNumber == 0 ){
                tiles[index].setTexture(texMngr->getTexture(49)) ;
                  tiles[index].setType(uint16_t(0)); 
                  return;
    }

    uint8_t fina = getNeighbours(location);
 
    switch(fina){
        case 2:    tiles[index].setTexture(texMngr->getTexture(2)) ;
                   break;
        case 3:    tiles[index].setTexture(texMngr->getTexture(3)) ;
                   break;  
        case 6:    tiles[index].setTexture(texMngr->getTexture(3)) ;
                   break;  
        case 8:    tiles[index].setTexture(texMngr->getTexture(3)) ;
                   break;      
        case 9:    tiles[index].setTexture(texMngr->getTexture(3)) ;
                   break;  
        case 10:    tiles[index].setTexture(texMngr->getTexture(4)) ;
                   break;  
        case 11:    tiles[index].setTexture(texMngr->getTexture(5)) ;
                   break;  
        case 16:    tiles[index].setTexture(texMngr->getTexture(6)) ;
                   break;  
        case 18:    tiles[index].setTexture(texMngr->getTexture(7)) ;
                   break;  
        case 22:    tiles[index].setTexture(texMngr->getTexture(8)) ;
                   break;  
        
        case 24:    tiles[index].setTexture(texMngr->getTexture(9)) ;
                   break;
        case 26:    tiles[index].setTexture(texMngr->getTexture(10)) ;
                   break;       
        case 27:    tiles[index].setTexture(texMngr->getTexture(11)) ;
                   break;  
        case 30:    tiles[index].setTexture(texMngr->getTexture(12)) ;
                   break;  
        case 31:    tiles[index].setTexture(texMngr->getTexture(13)) ;
                   break;  
        case 56:    tiles[index].setTexture(texMngr->getTexture(43)) ;
                   break;
        case 64:    tiles[index].setTexture(texMngr->getTexture(14)) ;
                   break;  
        case 66:    tiles[index].setTexture(texMngr->getTexture(15)) ;
                   break;    
        case 72:    tiles[index].setTexture(texMngr->getTexture(16)) ;
                   break;
                   
        case 74:    tiles[index].setTexture(texMngr->getTexture(17)) ;
                   break;       
        case 75:    tiles[index].setTexture(texMngr->getTexture(18)) ;
                   break;  
        case 80:    tiles[index].setTexture(texMngr->getTexture(19)) ;
                   break;  
        case 82:    tiles[index].setTexture(texMngr->getTexture(20)) ;
                   break;  
        case 86:    tiles[index].setTexture(texMngr->getTexture(21)) ;
                   break;  
        case 88:    tiles[index].setTexture(texMngr->getTexture(22)) ;
                   break; 
        case 90:    tiles[index].setTexture(texMngr->getTexture(23)) ;
                   break;
        case 91:    tiles[index].setTexture(texMngr->getTexture(24)) ;
                   break; 
                   
        case 94:    tiles[index].setTexture(texMngr->getTexture(25)) ;
                   break;  
        case 95:    tiles[index].setTexture(texMngr->getTexture(26)) ;
                   break;  
        case 104:    tiles[index].setTexture(texMngr->getTexture(27)) ;
                   break;  
        case 106:    tiles[index].setTexture(texMngr->getTexture(28)) ;
                   break;  
        case 107:    tiles[index].setTexture(texMngr->getTexture(29)) ;
                   break;                                       
        case 120:    tiles[index].setTexture(texMngr->getTexture(30)) ;
                   break;
        case 122:    tiles[index].setTexture(texMngr->getTexture(31)) ;
                   break;       
        case 123:    tiles[index].setTexture(texMngr->getTexture(32)) ;
                   break;
                   
        case 126:    tiles[index].setTexture(texMngr->getTexture(33)) ;
                   break;  
        case 127:    tiles[index].setTexture(texMngr->getTexture(34)) ;
                   break;  
        case 152:    tiles[index].setTexture(texMngr->getTexture(9)) ;
                   break;  
        case 194:    tiles[index].setTexture(texMngr->getTexture(15)) ;
                   break; 
        case 208:    tiles[index].setTexture(texMngr->getTexture(35)) ;
                   break;  
        case 210:    tiles[index].setTexture(texMngr->getTexture(36)) ;
                   break; 
        case 214:    tiles[index].setTexture(texMngr->getTexture(37)) ;
                   break;
        case 216:    tiles[index].setTexture(texMngr->getTexture(38)) ;
                   break;       
        case 218:    tiles[index].setTexture(texMngr->getTexture(39)) ;
                   break; 
        case 219:    tiles[index].setTexture(texMngr->getTexture(40)) ;
                   break;
                   
        case 222:    tiles[index].setTexture(texMngr->getTexture(41)) ;
                   break;  
        case 223:    tiles[index].setTexture(texMngr->getTexture(42)) ;
                   break;  
        case 248:    tiles[index].setTexture(texMngr->getTexture(43)) ;
                   break; 
        case 250:    tiles[index].setTexture(texMngr->getTexture(44)) ;
                   break;
        case 251:    tiles[index].setTexture(texMngr->getTexture(45)) ;
                   break;       
        case 254:    tiles[index].setTexture(texMngr->getTexture(46)) ;
                   break;  
        case 255:    tiles[index].setTexture(texMngr->getTexture(47)) ;
                   break;  
        case 0:    tiles[index].setTexture(texMngr->getTexture(48)) ;
                   break;  
        default:    std::cout <<"index ::"<< std::to_string(index)<< " : " <<std::to_string(fina)<< std::endl;
        tiles[index].setTexture(texMngr->getTexture(1)) ;
                 break;
    }

                
      tiles[index].setType(uint16_t(1));                

    }else{std::cout << "Out of Range";}
    
   
  //
}
bool tilemap::saveMap()
{std::cout << "saving map" << std::endl;
    std::ofstream myoutfile("testmap");
    for(int i = 0 ; i < totalTiles; i++){
        myoutfile << tiles[i].getType();
    }
    return true;
}
bool tilemap::getMapFile(std::string map)
{  
  for(int j = 0 ; j < totalTiles; j++){
      tiles[j].setTexture(texMngr->getTexture(49));
      tiles[j].setType(uint16_t(0));
      
      
}  
    
    
   bool done =false; 
   std::cout << "loading map " << map << std::endl;  
  std:: string line;
  std::ifstream myfile(map,std::ios::in);
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
std::cout <<line.size()<<std::endl;   
std::cout <<std::endl;   
for(int i = 0 ; i < line.size(); i++){
   // std::string g = line[i];
    uint16_t mine = uint8_t(line[i]);
    if(mine==49){
    tiles[i].setType(uint16_t(1));}
    else{tiles[i].setType(uint16_t(0));}
    std::cout <<mine<< "-";  
    
}

    
    }
bitmaskit();  
  }
 myfile.close();
  return false;
}
uint8_t tilemap::getNeighbours(sf::Vector2i position)
{
	sf::Vector2i normalCoords;
	position.x = position.x/Tilewidth;
	position.y = position.y/Tilewidth;
	uint8_t terrain = 0;
	
	
	if(position.x -1 >=0 && position.y -1 >=0 ){///////NW//////////
		if(tiles[(position.x -1)*mapWidth +(position.y -1)].getType()==1){
			if(tiles[(position.x -1)*mapWidth +(position.y)].getType()==1 && tiles[(position.x)*mapWidth +(position.y-1)].getType()==1 ){
			terrain +=1;
			}
		}
	}else{terrain +=1;}
	
	
	if(position.y -1 >=0 ){//////////N/////////
		if(tiles[(position.x )  *mapWidth +(position.y -1 )].getType() ==1){
		terrain +=2;  
		} 
		
	}else{terrain +=2;}
	
	if(position.x +1 <mapWidth && position.y -1 >=0 ){////////NE///////
		if(tiles[(position.x+1 )*mapWidth +(position.y -1)].getType() == 1){
					if(tiles[(position.x +1)*mapWidth +(position.y)].getType()==1 && tiles[(position.x)*mapWidth +(position.y-1)].getType()==1 ){
			terrain +=4;   
					}   
		} 
		
	}else{terrain +=4;}
	
	if(position.x -1 >=0 ){//////////W//////////
		if(tiles[(position.x-1 )*mapWidth +(position.y )].getType() ==1 ){
			terrain +=8;
		}
		
	}else{terrain +=8;}
	
	if(position.x +1 < mapWidth ){////////E//////////
		if(tiles[(position.x +1)*mapWidth +(position.y )].getType() == 1){
			terrain +=16;
			
		}
		
	}else{terrain +=16;}
	
	if(position.x -1 >=0 && position.y +1 <mapHeight ){/////////SW///////////
		if(tiles[(position.x -1)*mapWidth +(position.y +1 )].getType() == 1){
					if(tiles[(position.x -1)*mapWidth +(position.y)].getType()==1 && tiles[(position.x)*mapWidth +(position.y+1)].getType()==1 ){
			terrain +=32;  
					}
		}
		
	}else{terrain +=32;}
	
	
	if(position.y +1 <mapHeight ){  ///////S///////////
		if(tiles[(position.x )  *mapWidth +(position.y +1)].getType() == 1){
			terrain +=64;  
		}
		
	}else{terrain +=64;}
	
	
	if(position.x +1 <mapWidth  && position.y +1 <mapHeight ){ //////////SE/////////
		if(tiles[(position.x+1 )*mapWidth +(position.y +1)].getType() == 1){
					if(tiles[(position.x +1)*mapWidth +(position.y)].getType()==1 && tiles[(position.x)*mapWidth +(position.y+1)].getType()==1 ){
				terrain +=128;
					}
		}
		
	}else{terrain +=128;}

	return terrain;
}
void tilemap::bitmaskit()
{
    for(int j = 0 ; j < totalTiles ; j ++)
    {
       if(tiles[j].getType() == 1)
       {    
            changeTextureOf(tiles[j].getLocation2i(),1);
        }
    }
}
void tilemap::render(sf::RenderWindow* window){

    for(int i = 0 ; i < totalTiles ; i ++){
      tiles[i].render(window);
    }
 
}   

    
};
