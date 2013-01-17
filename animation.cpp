#include "animation.h"
#include "stdio.h"

Animation::Animation() : currentTexture(0), currentTileX(0), currentTileY(0), tileNum(0){
}

void Animation::addFrame(std::string path){
	texture.loadFromFile(path);
	textures.push_back(texture);
}

void Animation::addTile(std::string path, int _tileWidth, int _tileHeight){
	tileSize.x = _tileWidth;
	tileSize.y = _tileHeight;
	texture = tileSet.tileSet(path, tileSize);
}


/*
Play 멤버 함수를 update로 고쳐 
함수 끝에서 eTime.restart() 하는 방식을 사용하는게 나을것같음 

하여튼 Play 함수는 정지된 애니메이션을 시작하는 역할만 하고 (bool playFlag 를 true로 만든다던가)
실제 애니메이션 구현 부분은 update 함수로 이전해야한다.  
*/
void Animation::Play(sf::Sprite *sprite, bool tile){

	//if(tile == true){
		sprite->setTexture(texture);
		sprite->setTextureRect(tileSet.getTileSet(tileNum));

		if(((texture.getSize().x / tileSize.x) * (texture.getSize().y / tileSize.y)) == tileNum){
			tileNum = 0;
		}

		if(eTime.getElapsedTime().asMilliseconds() > _speed){
			tileNum++;
			eTime.restart();
		}
	//}
	/*
	else{
		if((unsigned int)currentTexture == textures.size())
			currentTexture=0;

		sprite->setTexture(textures[currentTexture]);

		if(eTime.getElapsedTime().asMilliseconds() > _speed){
			++currentTexture;
			eTime.restart();
		}
	}
	*/ //위 if 문은 굳이 없어도 될 것 같다 
}

void Animation::setSpeed (int speed){
	_speed = speed;
}