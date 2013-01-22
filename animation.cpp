#include "animation.h"
#include "stdio.h"

Animation::Animation() : currentTexture(0), currentTileX(0), currentTileY(0), tileNum(0){
	tileSet = new TileSet();
}

void Animation::addFrame(std::string path){
	texture.loadFromFile(path);
	textures.push_back(texture);
}

void Animation::addTile(std::string path, int _tileWidth, int _tileHeight){
	tileSize.x = _tileWidth;
	tileSize.y = _tileHeight;
	texture = tileSet->tileSet(path, tileSize);
}

void Animation::Play(sf::Sprite *sprite, bool tile){

	if(tile == true){
		sprite->setTexture(texture);
		sprite->setTextureRect(tileSet->getTileSet(tileNum));

		if(((texture.getSize().x / tileSize.x) * (texture.getSize().y / tileSize.y)) == tileNum){
			tileNum = 0;
		}

		if(eTime.getElapsedTime().asMilliseconds() > _speed){
			tileNum++;
			printf("tileNum : %d\n", tileNum);
			eTime.restart();
		}
	}

	else{
		if((unsigned int)currentTexture == textures.size())
			currentTexture=0;

		sprite->setTexture(textures[currentTexture]);

		if(eTime.getElapsedTime().asMilliseconds() > _speed){
			++currentTexture;
			eTime.restart();
		}
	}
}

void Animation::setSpeed (int speed){
	_speed = speed;
}