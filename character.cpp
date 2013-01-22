#include "character.h"

Character::Character(float _x, float _y){
	animation = new Animation();
	sprite.setPosition(_x, _y);
	animation->addTile("img/male_walkcycle.png",64, 64);
	animation->setSpeed(100);
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
	animation->update(&sprite, true);
	window.draw(sprite);
}


