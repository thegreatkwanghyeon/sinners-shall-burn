#include "animation.h"
#include "stdio.h"

Animation::Animation() : currentTexture(0), currentTileX(0), currentTileY(0), tileNum(0), tmpElapsedTime(0){
	tileSet = new TileSet();
	endTileNum = -1;
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

void Animation::setInterval(sf::Vector3i _interval){
	interval = _interval;
	tileNum = (interval.x -1) + ((interval.y-1)*(texture.getSize().x/tileSize.x));
	endTileNum = tileNum + interval.z;
}

void Animation::play(sf::Sprite *sprite, bool tile, sf::Time deltaTime){

	tmpElapsedTime += deltaTime.asSeconds();

	if(tile == true){
		sprite->setTexture(texture);
		sprite->setTextureRect(tileSet->getTileSet(tileNum));

		if(tileNum == endTileNum || ((texture.getSize().x / tileSize.x) * (texture.getSize().y / tileSize.y)) == tileNum){
			tileNum = (interval.x -1) + ((interval.y-1)*(texture.getSize().x/tileSize.x));
		}

		if(tmpElapsedTime > _speed){
			tileNum++;
			printf("tileNum : %d\n", tileNum);
			tmpElapsedTime = 0;

		}
	}

	else{
		if((unsigned int)currentTexture == textures.size())
			currentTexture=0;

		sprite->setTexture(textures[currentTexture]);

		if(tmpElapsedTime > _speed){
			++currentTexture;
			tmpElapsedTime = 0;
		}
	}
}

void Animation::setSpeed (float speed){
	_speed = speed;
}

void Animation::update(sf::Sprite *sprite, bool tile){
	play(sprite, tile, deltaTime);
	deltaTime = eTime.restart();
}