#include "animation.h"
#include "stdio.h"

Animation::Animation() : currentTexture(0), currentTileX(0), currentTileY(0), tileNum(0),  endTileNum(-1),tmpElapsedTime(0){
        tileSet = new TileSet();
        isPlay = true;
} //
void Animation::addFrame(std::string path){
        texture.loadFromFile(path);
        textures.push_back(texture);
}

void Animation::addTile(std::string path, int _tileWidth, int _tileHeight){
        tileSizeX = _tileWidth;
        tileSizeY = _tileHeight;
        texture = tileSet->tileSet(path, tileSizeX, tileSizeY);
}

void Animation::setTileRange(sf::Vector2i _intervalPosition, int _numberOfTile){
        interval = _intervalPosition;
        tileNum = (_intervalPosition.x -1) + ((_intervalPosition.y-1)*(texture.getSize().x/tileSizeX));
        endTileNum = tileNum + _numberOfTile - 1;
}

void Animation::play(sf::Sprite *sprite, bool tile, sf::Time deltaTime){

        tmpElapsedTime += deltaTime.asSeconds();

        if(tile == true){
                sprite->setTexture(texture);
                sprite->setTextureRect(tileSet->getTileSet(tileNum));

                        if(tileNum == endTileNum || ((texture.getSize().x / tileSizeX) * (texture.getSize().y / tileSizeY)) == tileNum){

                                tileNum = (interval.x -1) + ((interval.y-1)*(texture.getSize().x/tileSizeX));
                        }

                        if(isPlay){
                                if(tmpElapsedTime > _speed){
                                        tileNum++;
                                        //printf("tileNum : %d\n", tileNum);
                                        tmpElapsedTime = 0;
                                }
                }
        }

        else{
                if((unsigned int)currentTexture == textures.size())
                        currentTexture=0;

                sprite->setTexture(textures[currentTexture]);
                if(isPlay){
                        if(tmpElapsedTime > _speed){
                                ++currentTexture;
                                tmpElapsedTime = 0;
                        }
                }
        }
}

void Animation::setSpeed (float speed){
        _speed = speed;
}

void Animation::playAnimation(){
        isPlay = true;
}

void Animation::playAnimationAt(int number){
        tileNum = number;
        isPlay = true;
}

void Animation::stopAnimation(){
        isPlay = false;
}

void Animation::stopAnimationAt(int num){
        tileNum = num;
        isPlay = false;
}

void Animation::update(sf::Sprite *sprite, bool tile){
                play(sprite, tile, deltaTime);
        deltaTime = eTime.restart();
}
int Animation::getLocation(){
	return tileNum;//퍼즐에서 쓰려고 만듬.
}