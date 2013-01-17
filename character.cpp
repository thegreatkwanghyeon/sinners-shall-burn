#include "character.h"

Character::Character(){
}

void Character::loadContent(){
	pSprite=&sprite;
	sprite.setPosition(_x, _y);
	animation.addTile("img/number.jpg",100, 100);
	animation.setSpeed(500);

}

void Character::unloadContent(){

}

void Character::update(){
	animation.Play(pSprite, true);
}

void Character::draw(sf::RenderWindow &window){
	
	window.draw(sprite);
}

void Character::setPosition(float x, float y){
	_x = x;
	_y = y;
}


