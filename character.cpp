#include "character.h"

Character::Character(float _x, float _y){
	sprite.setPosition(_x, _y);
	pSprite=&sprite;
	animation.addTile("img/number.jpg",100, 100);
	animation.setSpeed(100);
}

void Character::Move(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		sprite.move(-1,0);
	}

	 if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		sprite.move(1,0);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		sprite.move(0,-1);
	}

	 if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		sprite.move(0,1);
	}			
}

void Character::update(){
	Move();
}

void Character::draw(sf::RenderWindow &window){
	animation.update(pSprite, true);
	window.draw(sprite);
}


