#include "tileputter.h"

void TilePutter::initialize(int num, int currentLayer){

	number = num;
	_currentLayer = currentLayer;

	saveTexture = texturePaths[currentLayer][number];

	able = true;
	contain = false;

	mapArea.left = 0;
	mapArea.width = MAPWIDTH;
	mapArea.top = 0;
	mapArea.height = MAPHEIGHT;

	for(unsigned int i = 0; i <= MAPHEIGHT/MAPTILEHEIGHT-1; i++){
		for(unsigned int j = 0; j <= MAPWIDTH/MAPTILEWIDTH-1; j++){
			tmpRect.left = j * MAPTILEWIDTH;
			tmpRect.top = i * MAPTILEHEIGHT;
			tmpRect.width = MAPTILEWIDTH;
			tmpRect.height = MAPTILEHEIGHT;
			rects.push_back(tmpRect);

			tmpContainRect.left = (j * MAPTILEWIDTH) + MAPTILEWIDTH/6;
			tmpContainRect.top = (i * MAPTILEHEIGHT) + MAPTILEHEIGHT/6;
			tmpContainRect.width = MAPTILEWIDTH/6*4;
			tmpContainRect.height = MAPTILEHEIGHT/6*4;
			containRects.push_back(tmpContainRect);			
		}
	}
}

void TilePutter::putTile(int x, int y, sf::IntRect textureRect){
	if(mapArea.contains(x, y)){
		for(i=0;i<containRects.size();i++){
			if(containRects[i].contains(x, y)){
				contain = true;
				break;
			}
			else contain = false;
		}
		if(contain){
			for(j=0;j<mapSprites.size();j++){
				if(mapSprites[j].sprite.getPosition().x == rects[i].left && mapSprites[j].sprite.getPosition().y == rects[i].top){
					able = false;break;
				}
				else able = true;
			}

			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				if(able){
					tmpSprite.sprite.setTexture(textures[_currentLayer][number]);				
					tmpSprite.sprite.setPosition(rects[i].left, rects[i].top);
					tmpSprite.sprite.setTextureRect(textureRect);
					tmpSprite.string = saveTexture;
					mapSprites.push_back(tmpSprite);
				}
				else{
					mapSprites[j].sprite.setTexture(textures[_currentLayer][number]);
					mapSprites[j].sprite.setTextureRect(textureRect);
					mapSprites[j].string = saveTexture;
				}
			}	
			if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && mapSprites.size()>0){
				if(!able && mapSprites[j].sprite.getPosition().x == rects[i].left && mapSprites[j].sprite.getPosition().y == rects[i].top){
					mapSprites.erase(mapSprites.begin()+j);
					able = true;
				}
			}
		}
	}
}

void TilePutter::draw(sf::RenderWindow &window){
	for(unsigned int i=0;i<mapSprites.size();i++){
		window.draw(mapSprites[i].sprite);
	}
}

std::vector< TILE > TilePutter::getMap(){
	return mapSprites;
}