#include "character.h"

Character::Character(float _x, float _y){
	sprite.setPosition(_x, _y);
	pSprite=&sprite;
	
	animation.addTile("img/number.jpg",100, 100);
	animation.setSpeed(500);
}

void Character::Draw(sf::RenderWindow &window){
	animation.Play(pSprite, true);
	
	window.draw(sprite);
}


