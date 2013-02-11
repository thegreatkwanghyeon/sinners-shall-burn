#include "tileputter.h"

void TilePutter::initialize(sf::Texture mainTexture){

	able = true;
	contain = false;

	tmpTexture = mainTexture;

	mapArea.left = 0;
	mapArea.width = MAPWIDTH;
	mapArea.top = 0;
	mapArea.height = MAPHEIGHT;

	for(unsigned int i = 0; i <= MAPHEIGHT/TILEHEIGHT-1; i++){
		for(unsigned int j = 0; j <= MAPWIDTH/TILEWIDTH-1; j++){
			tmpRect.left = j * TILEWIDTH;
			tmpRect.top = i * TILEHEIGHT;
			tmpRect.width = TILEWIDTH;
			tmpRect.height = TILEHEIGHT;
			rects.push_back(tmpRect);

			tmpContainRect.left = (j * TILEWIDTH) + TILEWIDTH/6;
			tmpContainRect.top = (i * TILEHEIGHT) + TILEHEIGHT/6;
			tmpContainRect.width = TILEWIDTH/6*4;
			tmpContainRect.height = TILEHEIGHT/6*4;
			containRects.push_back(tmpContainRect);			
		}
	}

	printf("containRects : %d\n", containRects.size());
	printf("rects : %d\n",rects.size());
	printf("mapSprites : %d\n---------------------",mapSprites.size());

}

void TilePutter::putTile(int x, int y, sf::IntRect textureRect){
	if(mapArea.contains(x, y)){
		for(i=0;i<containRects.size();i++){
			if(containRects[i].contains(x, y)){
				printf("containRect : %d\n", i);
				contain = true;
				break;
			}
			else contain = false;
		}
		if(contain){
			for(j=0;j<mapSprites.size();j++){
				if(mapSprites[j].getPosition().x == rects[i].left && mapSprites[j].getPosition().y == rects[i].top){
					able = false;break;
				}
				else able = true;
			}

			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				if(able){
					tmpSprite.setTexture(tmpTexture);				
					tmpSprite.setPosition(rects[i].left, rects[i].top);
					tmpSprite.setTextureRect(textureRect);
					mapSprites.push_back(tmpSprite);
					printf("push_back\n");
				}
				else{
					mapSprites[j].setTextureRect(textureRect);
					printf("switch\n");
				}
			}	
			if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && mapSprites.size()>0){
				if(!able && mapSprites[j].getPosition().x == rects[i].left && mapSprites[j].getPosition().y == rects[i].top){
					mapSprites.erase(mapSprites.begin()+j);
					able = true;
				}
			}
		}
	}

	printf("mapSprites : %d\n", mapSprites.size());
}

void TilePutter::draw(sf::RenderWindow &window){
	for(unsigned int i=0;i<mapSprites.size();i++){
		window.draw(mapSprites[i]);
	}
}